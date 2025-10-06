#include "../cube.h"

static bool	check_line_path(t_parsed_data *pd, t_bpos start, t_bpos step, double max_dist)
{
	t_bpos	current;
	double	dist;
	int		map_x;
	int		map_y;

	current = start;
	dist = 0.0;
	while (dist < max_dist)
	{
		current.x += step.x;
		current.y += step.y;
		dist += sqrt(step.x * step.x + step.y * step.y);
		if (dist >= max_dist)
			break ;
		map_x = (int)current.x;
		map_y = (int)current.y;
		if (map_y < 0 || map_y >= pd->level.max_y)
			return (false);
		if (map_x < 0 || map_x >= pd->level.max_x)
			return (false);
		if (pd->map_grid[map_y][map_x] == '1')
			return (false);
	}
	return (true);
}

static bool	has_line_of_sight(t_parsed_data *pd, t_bpos start, t_bpos end)
{
	t_bpos	delta;
	t_bpos	step;
	double	max_dist;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	max_dist = sqrt(delta.x * delta.x + delta.y * delta.y);
	step.x = delta.x / (max_dist * 4.0);
	step.y = delta.y / (max_dist * 4.0);
	return (check_line_path(pd, start, step, max_dist));
}

// Simple bubble sort for enemies by distance (farthest first)
static void sort_enemies_by_distance(t_enemy_draw_data *draw_data, int count)
{
    int         i;
    int         j;
    t_enemy_draw_data temp;

    i = 0;
    while (i < count - 1)
    {
        j = 0;
        while (j < count - i - 1)
        {
            if (draw_data[j].distance < draw_data[j + 1].distance)
            {
                temp = draw_data[j];
                draw_data[j] = draw_data[j + 1];
                draw_data[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

static bool	process_enemy_visibility(t_parsed_data *pd, int i, t_bpos *rel_pos, double *inv_det)
{
	double	distance;
	bool	visible;
	t_bpos	transform;

	rel_pos->x = pd->enemies[i].b_pos.x - pd->player.bpos.x;
	rel_pos->y = pd->enemies[i].b_pos.y - pd->player.bpos.y;
	distance = sqrt(rel_pos->x * rel_pos->x + rel_pos->y * rel_pos->y);
	visible = has_line_of_sight(pd, pd->player.bpos, pd->enemies[i].b_pos);
	if (distance > 24.0 || !visible)
		return (false);
	*inv_det = 1.0 / (pd->player.camera_plane.dir.x * pd->player.bdir.y
			- pd->player.bdir.x * pd->player.camera_plane.dir.y);
	transform.x = -(*inv_det) * (pd->player.bdir.y * rel_pos->x
			- pd->player.bdir.x * rel_pos->y);
	transform.y = (*inv_det) * (-pd->player.camera_plane.dir.y * rel_pos->x
			+ pd->player.camera_plane.dir.x * rel_pos->y);
	if (transform.y <= 0)
		return (false);
	return (true);
}

static void	store_enemy_data(t_parsed_data *pd, int i, t_bpos *rel_pos,
		double inv_det, t_enemy_draw_data *draw_data)
{
	t_bpos	transform;

	transform.x = -inv_det * (pd->player.bdir.y * rel_pos->x
			- pd->player.bdir.x * rel_pos->y);
	transform.y = inv_det * (-pd->player.camera_plane.dir.y * rel_pos->x
			+ pd->player.camera_plane.dir.x * rel_pos->y);
	draw_data->enemy = &pd->enemies[i];
	draw_data->distance = sqrt(rel_pos->x * rel_pos->x + rel_pos->y * rel_pos->y);
	draw_data->visible = true;
	draw_data->transform = transform;
	draw_data->sprite_screen_x = (int)((WIDTH / 2) * (1 + transform.x / transform.y));
	draw_data->sprite_height = abs((int)(HEIGHT / transform.y));
	draw_data->sprite_width = abs((int)(HEIGHT / transform.y));
}

static int	collect_visible_enemies(t_parsed_data *pd, t_enemy_draw_data *draw_data)
{
	int		i;
	int		draw_count;
	t_bpos	rel_pos;
	double	inv_det;

	draw_count = 0;
	i = 0;
	while (i < pd->enemy_count && draw_count < MAX_ENEMIES)
	{
		if (pd->enemies[i].dead)
		{
			i++;
			continue ;
		}
		if (process_enemy_visibility(pd, i, &rel_pos, &inv_det))
		{
			store_enemy_data(pd, i, &rel_pos, inv_det, &draw_data[draw_count]);
			draw_count++;
		}
		i++;
	}
	return (draw_count);
}


static void calculate_draw_bounds(t_enemy_draw_data *curr, int horizon,
        int *draw_start_y, int *draw_end_y, int *draw_start_x, int *draw_end_x,
        int *orig_draw_start_x, int *orig_draw_start_y)
{
    /* original (un-clamped) starts */
    *orig_draw_start_y = -curr->sprite_height / 2 + horizon;
    *orig_draw_start_x = -curr->sprite_width  / 2 + curr->sprite_screen_x;

    /* clamp Y */
    *draw_start_y = *orig_draw_start_y;
    if (*draw_start_y < 0)
        *draw_start_y = 0;
    *draw_end_y = curr->sprite_height / 2 + horizon;
    if (*draw_end_y >= HEIGHT)
        *draw_end_y = HEIGHT - 1;

    /* clamp X (IMPORTANT: don't set to sprite_width — clamp to 0) */
    *draw_start_x = *orig_draw_start_x;
    if (*draw_start_x < 0)
        *draw_start_x = 0;
    *draw_end_x = curr->sprite_width / 2 + curr->sprite_screen_x;
    if (*draw_end_x >= WIDTH)
        *draw_end_x = WIDTH - 1;
}
static void draw_enemy_pixel(t_parsed_data *pd, t_enemy_draw_data *curr,
        int stripe, int y, int orig_draw_start_x, int orig_draw_start_y)
{
    int             tex_x;
    int             tex_y;
    unsigned char   *p;
    int             idx;
    uint32_t        pixel_color;
    mlx_image_t     *frame_img;

    frame_img = curr->enemy->anim_img;
    if (frame_img == NULL)
        return ;

    if (curr->sprite_width == 0 || curr->sprite_height == 0)
        return;

    /* fractional mapping; keep integer math as before */
    tex_x = (int)((stripe - orig_draw_start_x) * (double)frame_img->width  / (double)curr->sprite_width);
    tex_y = (int)((y      - orig_draw_start_y) * (double)frame_img->height / (double)curr->sprite_height);

    /* safety: ensure tex coords inside texture */
    if (tex_x < 0 || tex_x >= frame_img->width || tex_y < 0 || tex_y >= frame_img->height)
        return;

    p = (unsigned char *)frame_img->pixels;
    idx = (tex_y * frame_img->width + tex_x) * 4;
    pixel_color = (p[idx + 0] << 24) | (p[idx + 1] << 16)
        | (p[idx + 2] << 8) | p[idx + 3];
    if (p[idx + 3] != 0)
        mlx_put_pixel(pd->screen, stripe, y,
            shade_color(pixel_color, curr->distance, 0.15));
}

static void draw_enemy_sprite(t_parsed_data *pd, t_enemy_draw_data *curr,
        int draw_start_y, int draw_end_y, int draw_start_x, int draw_end_x,
        int orig_draw_start_x, int orig_draw_start_y, uint32_t color)
{
    int stripe;
    int y;

    stripe = draw_start_x;
    while (stripe < draw_end_x)
    {
        y = draw_start_y;
        while (y < draw_end_y)
        {
            draw_enemy_pixel(pd, curr, stripe, y, orig_draw_start_x, orig_draw_start_y);
            y++;
        }
        stripe++;
    }
}

static void draw_single_enemy(t_parsed_data *pd, t_enemy_draw_data *curr, int horizon)
{
    int draw_start_y;
    int draw_end_y;
    int draw_start_x;
    int draw_end_x;
    int orig_draw_start_x;
    int orig_draw_start_y;
    uint32_t color;

    calculate_draw_bounds(curr, horizon, &draw_start_y, &draw_end_y,
        &draw_start_x, &draw_end_x, &orig_draw_start_x, &orig_draw_start_y);
    // color = get_enemy_color(curr->enemy->type, curr->distance, curr->visible);
    draw_enemy_sprite(pd, curr, draw_start_y, draw_end_y,
        draw_start_x, draw_end_x, orig_draw_start_x, orig_draw_start_y, color);
}



static void	draw_sorted_enemies(t_parsed_data *pd, t_enemy_draw_data *draw_data,
		int draw_count)
{
	int	i;
	int	horizon;

	i = 0;
	horizon = HEIGHT / 2 + (int)pd->player.pitch;
	while (i < draw_count)
	{
		draw_single_enemy(pd, &draw_data[i], horizon);
		i++;
	}
}

void	draw_enemies(t_parsed_data *pd)
{
	int					draw_count;
    t_enemy_draw_data	draw_data[MAX_ENEMIES];
    int					i;
    t_enemy_draw_data	*target_enemy;
    double				center_tolerance = WIDTH * 0.05; // 5% of screen width tolerance
    double				closest_distance = 1e9;

	if (!pd->enemies || pd->enemy_count == 0)
		return ;
	draw_count = collect_visible_enemies(pd, draw_data);
	if (draw_count > 1)
		sort_enemies_by_distance(draw_data, draw_count);
	if (pd->player.is_shooting)
    {
        target_enemy = NULL;
        i = 0;
        while (i < draw_count)
        {
            double diff = fabs(draw_data[i].sprite_screen_x - WIDTH / 2);

            if (diff < center_tolerance && draw_data[i].distance < closest_distance)
            {
                closest_distance = draw_data[i].distance;
                target_enemy = &draw_data[i];
            }
            i++;
        }
        if (target_enemy)
        {
            target_enemy->enemy->health -= pd->player.gun.damage;
            if (target_enemy->enemy->health <= 0)
            {
				// animation
                target_enemy->enemy->dead = true;
                printf("Enemy killed by player!\n");
            }
            else
            {
                printf("Enemy hit! Health: %d\n", target_enemy->enemy->health);
            }
        }

        // Reset shooting flag so it only registers once per shot
        pd->player.is_shooting = false;
    }

	draw_sorted_enemies(pd, draw_data, draw_count);
}

static int	find_current_direction(t_enemy *enemy, double directions[4][2])
{
	int	i;
	int	current_dir_index;

	i = 0;
	current_dir_index = -1;
	while (i < 4)
	{
		if (fabs(enemy->dir.x - directions[i][0]) < 0.1
			&& fabs(enemy->dir.y - directions[i][1]) < 0.1)
		{
			current_dir_index = i;
			break ;
		}
		i++;
	}
	return (current_dir_index);
}

static int	calculate_new_direction(int current_dir_index)
{
	int	turn_direction;
	int	new_dir_index;

	if (rand() % 2 == 0)
		turn_direction = -1;
	else
		turn_direction = 1;
	new_dir_index = (current_dir_index + turn_direction + 4) % 4;
	return (new_dir_index);
}

static void	change_enemy_direction(t_enemy *enemy)
{
	double	directions[4][2];
	int		current_dir_index;
	int		new_dir_index;

	directions[0][0] = 0;
	directions[0][1] = 1;
	directions[1][0] = 1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = -1;
	directions[3][0] = -1;
	directions[3][1] = 0;
	current_dir_index = find_current_direction(enemy, directions);
	if (current_dir_index != -1)
	{
		new_dir_index = calculate_new_direction(current_dir_index);
		enemy->dir.x = directions[new_dir_index][0];
		enemy->dir.y = directions[new_dir_index][1];
	}
	else
	{
		new_dir_index = rand() % 4;
		enemy->dir.x = directions[new_dir_index][0];
		enemy->dir.y = directions[new_dir_index][1];
	}
}

static void	calculate_direction_to_player(t_enemy *enemy, t_bpos player_pos,
		t_bpos *direction)
{
	double	length;

	direction->x = player_pos.x - enemy->b_pos.x;
	direction->y = player_pos.y - enemy->b_pos.y;
	length = sqrt(direction->x * direction->x + direction->y * direction->y);
	if (length > 0)
	{
		direction->x /= length;
		direction->y /= length;
	}
}

static bool	is_valid_move_position(t_parsed_data *pd, int map_x, int map_y)
{
	if (map_y < 0)
		return (false);
	if (map_y >= pd->level.max_y)
		return (false);
	if (map_x < 0)
		return (false);
	if (map_x >= pd->level.max_x)
		return (false);
	if (pd->map_grid[map_y][map_x] != '0')
		return (false);
	return (true);
}

static void	chase_player(t_enemy *enemy, t_bpos player_pos, double speed,
		t_parsed_data *pd)
{
	t_bpos	direction;
	t_bpos	new_pos;
	int		map_x;
	int		map_y;

	calculate_direction_to_player(enemy, player_pos, &direction);
	new_pos.x = enemy->b_pos.x + direction.x * speed;
	new_pos.y = enemy->b_pos.y + direction.y * speed;
	map_x = (int)new_pos.x;
	map_y = (int)new_pos.y;
	if (is_valid_move_position(pd, map_x, map_y))
	{
		enemy->b_pos = new_pos;
		enemy->dir.x = direction.x;
		enemy->dir.y = direction.y;
	}
}

static double	calculate_distance_to_origin(t_enemy *enemy)
{
	double	dx;
	double	dy;
	double	distance;

	dx = enemy->b_pos.x - enemy->patrol_origin.x;
	dy = enemy->b_pos.y - enemy->patrol_origin.y;
	distance = sqrt(dx * dx + dy * dy);
	return (distance);
}

static void	calculate_direction_to_origin(t_enemy *enemy, t_bpos *direction)
{
	double	length;

	direction->x = enemy->patrol_origin.x - enemy->b_pos.x;
	direction->y = enemy->patrol_origin.y - enemy->b_pos.y;
	length = sqrt(direction->x * direction->x + direction->y * direction->y);
	if (length > 0)
	{
		direction->x /= length;
		direction->y /= length;
	}
}

static bool	return_to_patrol(t_enemy *enemy, t_parsed_data *pd)
{
	double	distance_to_origin;
	t_bpos	direction;
	t_bpos	new_pos;
	int		map_x;
	int		map_y;

	distance_to_origin = calculate_distance_to_origin(enemy);
	if (distance_to_origin < 0.5)
		return (true);
	calculate_direction_to_origin(enemy, &direction);
	new_pos.x = enemy->b_pos.x + direction.x * enemy->patrol_speed;
	new_pos.y = enemy->b_pos.y + direction.y * enemy->patrol_speed;
	map_x = (int)new_pos.x;
	map_y = (int)new_pos.y;
	if (map_y >= 0 && map_y < pd->level.max_y
		&& map_x >= 0 && map_x < pd->level.max_x
		&& pd->map_grid[map_y][map_x] == '0')
	{
		enemy->b_pos = new_pos;
		enemy->dir.x = direction.x;
		enemy->dir.y = direction.y;
	}
	else
	{
		change_enemy_direction(enemy);
	}
	return (false);
}

static double heuristic(t_pos a, t_pos b)
{
    return (abs(a.x - b.x) + abs(a.y - b.y));
}



static void	set_alternative_directions(t_bpos alternatives[8], t_bpos direction)
{
	alternatives[0].x = direction.x;
	alternatives[0].y = direction.y;
	alternatives[1].x = direction.x * 0.7;
	alternatives[1].y = direction.y * 0.7;
	alternatives[2].x = direction.y;
	alternatives[2].y = -direction.x;
	alternatives[3].x = -direction.y;
	alternatives[3].y = direction.x;
	alternatives[4].x = direction.x * 0.7;
	alternatives[4].y = direction.y * 0.7;
	alternatives[5].x = direction.y * 0.7;
	alternatives[5].y = -direction.x * 0.7;
	alternatives[6].x = -direction.y * 0.7;
	alternatives[6].y = direction.x * 0.7;
	alternatives[7].x = -direction.x;
	alternatives[7].y = -direction.y;
}

static void	try_alternative_directions(t_enemy *enemy, t_parsed_data *pd,
		t_bpos direction, double speed)
{
	t_bpos	alternatives[8];
	t_bpos	new_pos;
	int		map_x;
	int		map_y;
	int		i;

	set_alternative_directions(alternatives, direction);
	i = 0;
	while (i < 8)
	{
		new_pos.x = enemy->b_pos.x + alternatives[i].x * speed;
		new_pos.y = enemy->b_pos.y + alternatives[i].y * speed;
		map_x = (int)new_pos.x;
		map_y = (int)new_pos.y;
		if (is_valid_move_position(pd, map_x, map_y))
		{
			enemy->b_pos = new_pos;
			enemy->dir.x = alternatives[i].x;
			enemy->dir.y = alternatives[i].y;
			return ;
		}
		i++;
	}
}


static void	smart_chase_player(t_enemy *enemy, t_bpos player_pos, double speed,
		t_parsed_data *pd)
{
	t_bpos	direction;
	t_bpos	new_pos;
	int		map_x;
	int		map_y;

	calculate_direction_to_player(enemy, player_pos, &direction);
	new_pos.x = enemy->b_pos.x + direction.x * speed;
	new_pos.y = enemy->b_pos.y + direction.y * speed;
	map_x = (int)new_pos.x;
	map_y = (int)new_pos.y;
	if (is_valid_move_position(pd, map_x, map_y))
	{
		enemy->b_pos = new_pos;
		enemy->dir.x = direction.x;
		enemy->dir.y = direction.y;
		return ;
	}
	try_alternative_directions(enemy, pd, direction, speed);
}

static double	calculate_distance_to_player(t_enemy *enemy, t_parsed_data *pd)
{
	double	dx;
	double	dy;
	double	distance;

	dx = enemy->b_pos.x - pd->player.bpos.x;
	dy = enemy->b_pos.y - pd->player.bpos.y;
	distance = sqrt(dx * dx + dy * dy);
	return (distance);
}

static void	perform_patrol_movement(t_enemy *enemy, t_parsed_data *pd)
{
	t_bpos	new_pos;
	int		map_x;
	int		map_y;

	new_pos.x = enemy->b_pos.x + enemy->dir.x * enemy->patrol_speed;
	new_pos.y = enemy->b_pos.y + enemy->dir.y * enemy->patrol_speed;
	map_x = (int)new_pos.x;
	map_y = (int)new_pos.y;
	if (map_y >= 0 && map_y < pd->level.max_y
		&& map_x >= 0 && map_x < pd->level.max_x
		&& pd->map_grid[map_y][map_x] == '0')
	{
		enemy->b_pos = new_pos;
	}
	else
	{
		change_enemy_direction(enemy);
	}
}

static void	handle_patrol_state(t_parsed_data *pd, t_enemy *enemy, int i,
		double distance, bool visible)
{
	if (distance <= CHASE_DISTANCE && visible)
	{
		enemy->state = ENEMY_CHASE;
		printf("Enemy %d started chasing!\n", i);
	}
	else
	{
		perform_patrol_movement(enemy, pd);
	}
}

static void	handle_chase_state(t_parsed_data *pd, t_enemy *enemy, int i,
		double distance)
{
	if (distance > LOSE_DISTANCE)
	{
		enemy->state = ENEMY_RETURN;
		printf("Enemy %d lost player, returning to patrol!\n", i);
	}
	else if (distance <= ATTACK_DISTANCE)
	{
		enemy->state = ENEMY_ATTACK;
		printf("Enemy %d is attacking!\n", i);
		pd->player.health -= enemy->damage;
		printf("Player health: %d\n", pd->player.health);
	}
	else
	{
		smart_chase_player(enemy, pd->player.bpos, enemy->chase_speed, pd);
	}
}

static void	handle_attack_state(t_parsed_data *pd, t_enemy *enemy, int i,
		double distance)
{
	if (distance > ATTACK_DISTANCE)
	{
		if (distance <= LOSE_DISTANCE)
		{
			enemy->state = ENEMY_CHASE;
			printf("Enemy %d resumed chasing!\n", i);
		}
		else
		{
			enemy->state = ENEMY_RETURN;
			printf("Enemy %d lost player after attack!\n", i);
		}
		enemy->attack_cooldown = 0;
		enemy->is_attacking = false; // Stop attack animation
	}
	else
	{
		// Enemy is still in attack range - handle repeated attacks
		if (enemy->attack_cooldown <= 0)
		{
			// Start attack animation
			enemy->is_attacking = true;
			enemy->anim_frame = 0; // Start from first attack frame
			enemy->attack_anim_counter = 0;
			
			// Perform attack
			pd->player.health -= enemy->damage;
			printf("Enemy %d is attacking! Player health: %d\n", i, pd->player.health);
			
			// Set cooldown
			enemy->attack_cooldown = 20;
		}
		else
		{
			// Decrement cooldown
			enemy->attack_cooldown--;
		}
	}
}

static void	handle_return_state(t_parsed_data *pd, t_enemy *enemy, int i)
{
	if (return_to_patrol(enemy, pd))
	{
		enemy->state = ENEMY_PATROL;
		printf("Enemy %d returned to patrol!\n", i);
	}
}

static void	handle_enemy_state(t_parsed_data *pd, t_enemy *enemy, int i,
		double distance, bool visible)
{
	if (enemy->state == ENEMY_PATROL)
		handle_patrol_state(pd, enemy, i, distance, visible);
	else if (enemy->state == ENEMY_CHASE)
		handle_chase_state(pd, enemy, i, distance);
	else if (enemy->state == ENEMY_ATTACK)
		handle_attack_state(pd, enemy, i, distance);
	else if (enemy->state == ENEMY_RETURN)
		handle_return_state(pd, enemy, i);
}

static void	update_single_enemy(t_parsed_data *pd, int i)
{
	t_enemy		*enemy;
	double		distance;
	bool		visible;

	enemy = &pd->enemies[i];
	if (enemy->dead)
		return ;
	distance = calculate_distance_to_player(enemy, pd);
	visible = has_line_of_sight(pd, enemy->b_pos, pd->player.bpos);
	handle_enemy_state(pd, enemy, i, distance, visible);

    /* Handle different animation states */
    if (enemy->state == ENEMY_ATTACK && enemy->is_attacking)
    {
        // Attack animation - faster animation for attacks
        enemy->attack_anim_counter++;
        if (enemy->attack_anim_counter >= ENEMY_ANIM_RATE / 2) // Attack anim is faster
        {
            enemy->attack_anim_counter = 0;
            enemy->anim_frame = (enemy->anim_frame + 1) % 3;
            
            // Play attack animation frames
            if (enemy->anim_frame == 0)
                enemy->anim_img = enemy->attack1.img;
            else if (enemy->anim_frame == 1)
                enemy->anim_img = enemy->attack2.img;
            else
            {
                enemy->anim_img = enemy->attack3.img;
                // On the last frame, check if we should stop attacking
                if (enemy->attack_cooldown <= 0)
                {
                    enemy->is_attacking = false;
                }
            }
        }
    }
    else if (enemy->state == ENEMY_PATROL || enemy->state == ENEMY_CHASE)
    {
        /* walking animation */
        enemy->anim_counter++;
        if (enemy->anim_counter >= ENEMY_ANIM_RATE)
        {
            enemy->anim_counter = 0;
            enemy->anim_frame = (enemy->anim_frame + 1) % 3;
            if (enemy->anim_frame == 0)
                enemy->anim_img = enemy->walk1.img;
            else if (enemy->anim_frame == 1)
                enemy->anim_img = enemy->walk2.img;
            else
                enemy->anim_img = enemy->walk3.img;
        }
    }
    else
    {
        /* not walking or attacking: show base skin image */
        enemy->anim_img = enemy->skin.img;
        enemy->anim_frame = 0;
        enemy->anim_counter = 0;
        enemy->is_attacking = false;
        enemy->attack_anim_counter = 0;
    }
}

void	update_enemies(t_parsed_data *pd)
{
	int	i;

	if (!pd->enemies || pd->enemy_count == 0)
		return ;
	i = 0;
	while (i < pd->enemy_count)
	{
		update_single_enemy(pd, i);
		i++;
	}
}
