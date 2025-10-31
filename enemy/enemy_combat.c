#include "../cube.h"

void update_death_animation(t_parsed_data *pd, t_enemy *enemy)
{
    if (enemy->death_anim_frame <= 0)
        enemy->is_highlighted = true;
    enemy->highlight_timer = 0;
    enemy->death_anim_counter++;
    if (enemy->death_anim_counter >= 15)
    {
        enemy->death_anim_counter = 0;
        if (enemy->death_anim_frame < 2)
        {
            enemy->death_anim_frame++;
            if (enemy->death_anim_frame == 1)
            {
                enemy->anim_img = enemy->death2->img;
                enemy->is_highlighted = false;
            }
            else if (enemy->death_anim_frame == 2)
                enemy->anim_img = enemy->death2->img;
        }
    }
    if (enemy->death_anim_frame >= 2)
        enemy->death_timer--;
    if (enemy->death_timer <= 0 && !enemy->dead)
    {
        spawn_medkit(pd, enemy->b_pos, enemy->type);
        enemy->is_dying = false;
        enemy->dead = true;
    }
}

static int	is_valid_enemy(t_enemy_draw_data *data)
{
	if (data->enemy->is_dying)
		return (0);
	if (data->enemy->dead && !data->enemy->is_dying)
		return (0);
	return (1);
}

t_enemy_draw_data	*find_shot_target(t_enemy_draw_data *draw_data,
		int draw_count, double center_tolerance)
{
	int					i;
	double				closest_distance;
	double				diff;
	t_enemy_draw_data	*target_enemy;

	i = 0;
	target_enemy = NULL;
	closest_distance = 1e9;
	while (i < draw_count)
	{
		if (!is_valid_enemy(&draw_data[i]))
		{
			i++;
			continue ;
		}
		diff = fabs((double)draw_data[i].sprite_screen_x - (double)WIDTH / 2.0);
		if (diff < center_tolerance && draw_data[i].distance < closest_distance)
		{
			closest_distance = draw_data[i].distance;
			target_enemy = &draw_data[i];
		}
		i++;
	}
	return (target_enemy);
}

void apply_damage_to_enemy(t_parsed_data *pd, t_enemy *enemy)
{
    enemy->health -= pd->player.gun.damage;
    enemy->is_highlighted = true;
    enemy->highlight_timer = HIGHLIGHT_FRAMES;
    if (enemy->health <= 0)
    {
        enemy->is_dying = true;
        enemy->dead = false;
        enemy->death_anim_frame = 0;
        enemy->death_anim_counter = 0;
        enemy->death_timer = DEATH_ANIMATION_DURATION;
        enemy->anim_img = enemy->death1->img;
        enemy->is_highlighted = false;
        enemy->highlight_timer = 0;
    }
    else
        enemy->state = ENEMY_CHASE;
}

void handle_shooting_once(t_parsed_data *pd, t_enemy_draw_data *draw_data,
        int draw_count)
{
    t_enemy_draw_data   *target_enemy;
    double              center_tolerance;

    if (!pd->player.is_shooting)
        return ;
    center_tolerance = WIDTH * 0.05;
    target_enemy = find_shot_target(draw_data, draw_count, center_tolerance);
    if (target_enemy && !target_enemy->enemy->is_dying
            && !target_enemy->enemy->dead)
    {
        apply_damage_to_enemy(pd, target_enemy->enemy);
    }
    pd->player.is_shooting = false;
}

void update_all_death_animations(t_parsed_data *pd)
{
    int i;

    i = 0;
    while (i < pd->enemy_count)
    {
        if (pd->enemies[i].is_dying)
            update_death_animation(pd, &pd->enemies[i]);
        i++;
    }
}
