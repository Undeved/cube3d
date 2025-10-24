#include "../cube.h"

static bool	is_diagonal_gap(t_parsed_data *pd, t_bpos from, t_bpos to)
{
	int	from_x;
	int	from_y;
	int	to_x;
	int	to_y;

	from_x = (int)from.x;
	from_y = (int)from.y;
	to_x = (int)to.x;
	to_y = (int)to.y;
	if (from_x != to_x && from_y != to_y)
	{
		if (pd->map_grid[from_y][to_x] == '1' && pd->map_grid[to_y][from_x] == '1')
			return (true);
	}
	return (false);
}

bool try_alternative_directions(t_enemy *enemy, t_parsed_data *pd,
                t_bpos direction, double speed)
{
    t_bpos  alternatives[8];
    t_bpos  new_pos;
    int     i;

    set_alternative_directions(alternatives, direction);
    i = 0;
    while (i < 8)
    {
        new_pos.x = enemy->b_pos.x + alternatives[i].x * speed;
        new_pos.y = enemy->b_pos.y + alternatives[i].y * speed;
        if (is_valid_move_position_circle_global(pd, new_pos.x, new_pos.y)
                && !is_diagonal_gap(pd, enemy->b_pos, new_pos))
        {
            enemy->b_pos = new_pos;
            enemy->dir.x = alternatives[i].x;
            enemy->dir.y = alternatives[i].y;
            return (true);
        }
        i++;
    }
    return (false);
}

void smart_chase_player(t_enemy *enemy, t_bpos player_pos, double speed,
                t_parsed_data *pd)
{
    t_bpos  direction;
    t_bpos  new_pos;
    bool    moved;

    calculate_direction_to_player(enemy, player_pos, &direction);
    new_pos.x = enemy->b_pos.x + direction.x * speed;
    new_pos.y = enemy->b_pos.y + direction.y * speed;
    if (is_valid_move_position_circle_global(pd, new_pos.x, new_pos.y)
            && !is_diagonal_gap(pd, enemy->b_pos, new_pos))
    {
        enemy->b_pos = new_pos;
        enemy->dir.x = direction.x;
        enemy->dir.y = direction.y;
        return ;
    }
    moved = try_alternative_directions(enemy, pd, direction, speed);
    if (!moved)
        enemy->state = ENEMY_RETURN;
}

double	calculate_distance_to_player(t_enemy *enemy, t_parsed_data *pd)
{
	double	dx;
	double	dy;
	double	distance;

	dx = enemy->b_pos.x - pd->player.bpos.x;
	dy = enemy->b_pos.y - pd->player.bpos.y;
	distance = sqrt(dx * dx + dy * dy);
	return (distance);
}


static double dist2(t_bpos a, t_bpos b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return (dx * dx + dy * dy);
}

static bool choose_random_patrol_target(t_enemy *enemy, t_parsed_data *pd)
{
    int attempts;
    double rx;
    double ry;
    double frac;
    int r;

    if (!enemy || !pd)
        return (false);
    attempts = 0;
    while (attempts < 30)
    {
        r = ft_rand() % 1000;
        frac = (double)r / 1000.0;
        rx = enemy->patrol_origin.x + (frac * 2.0 - 1.0) * PATROL_TARGET_RADIUS;
        r = ft_rand() % 1000;
        frac = (double)r / 1000.0;
        ry = enemy->patrol_origin.y + (frac * 2.0 - 1.0) * PATROL_TARGET_RADIUS;
        if (rx < 0.0 || ry < 0.0
         || rx >= (double)pd->level.max_x || ry >= (double)pd->level.max_y)
        {
            attempts++;
            continue ;
        }
        if (!is_position_blocked_circle(pd, rx, ry, COLLISION_RADIUS))
        {
            enemy->patrol_target.x = rx;
            enemy->patrol_target.y = ry;
            enemy->patrol_target_timer = enemy->patrol_change_interval;
            return (true);
        }
        attempts++;
    }
    return (false);
}

static bool move_towards_target(t_enemy *enemy, t_parsed_data *pd,
        t_bpos target, double speed)
{
    t_bpos dir;
    double len;
    double step_x;
    double step_y;
    int steps;
    int s;
    double nx;
    double ny;
    bool moved;

    dir.x = target.x - enemy->b_pos.x;
    dir.y = target.y - enemy->b_pos.y;
    len = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len <= 1e-9)
        return (false);
    dir.x /= len;
    dir.y /= len;

    steps = 2;
    step_x = dir.x * speed / (double)steps;
    step_y = dir.y * speed / (double)steps;
    s = 0;
    moved = false;
    while (s < steps)
    {
        nx = enemy->b_pos.x + step_x;
        ny = enemy->b_pos.y + step_y;
        if (is_valid_move_position_circle_global(pd, nx, ny)
            && !is_diagonal_gap(pd, enemy->b_pos, (t_bpos){nx, ny}))
        {
            enemy->b_pos.x = nx;
            enemy->b_pos.y = ny;
            moved = true;
        }
        else
        {
            if (is_valid_move_position_circle_global(pd, nx, enemy->b_pos.y))
            {
                enemy->b_pos.x = nx;
                moved = true;
            }
            else if (is_valid_move_position_circle_global(pd, enemy->b_pos.x, ny))
            {
                enemy->b_pos.y = ny;
                moved = true;
            }
            else
            {
                if (try_alternative_directions(enemy, pd, dir, speed / (double)steps))
                    moved = true;
                break;
            }
        }
        s++;
    }
    if (moved)
    {
        dir.x = target.x - enemy->b_pos.x;
        dir.y = target.y - enemy->b_pos.y;
        len = sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len > 1e-9)
        {
            enemy->dir.x = dir.x / len;
            enemy->dir.y = dir.y / len;
        }
    }
    return (moved);
}

void perform_patrol_movement(t_enemy *enemy, t_parsed_data *pd)
{
    t_bpos target;
    double reached_dist2;

    if (!enemy || !pd)
        return ;

    /* if no target or timer expired, pick a new one */
    if (enemy->patrol_target_timer <= 0
        || dist2(enemy->b_pos, enemy->patrol_target) <= (PATROL_REACHED_EPS * PATROL_REACHED_EPS))
    {
        if (!choose_random_patrol_target(enemy, pd))
        {
            change_enemy_direction(enemy);
            enemy->patrol_target_timer = enemy->patrol_change_interval;
        }
    }

    target = enemy->patrol_target;

    if (!move_towards_target(enemy, pd, target, enemy->patrol_speed))
    {
        if (!try_alternative_directions(enemy, pd, (t_bpos){target.x - enemy->b_pos.x,
                    target.y - enemy->b_pos.y}, enemy->patrol_speed))
        {
            enemy->patrol_target_timer = 0;
        }
    }
    if (enemy->patrol_target_timer > 0)
        enemy->patrol_target_timer--;
}

void handle_patrol_state(t_enemy_ctx *ctx)
{
	if (ctx->distance <= CHASE_DISTANCE && ctx->visible)
		ctx->enemy->state = ENEMY_CHASE;
	else
		perform_patrol_movement(ctx->enemy, ctx->pd);
}
