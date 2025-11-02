#include "../cube.h"

bool try_alternative_directions(t_enemy *enemy, t_parsed_data *pd,
                t_bpos direction, double speed)
{
    t_bpos  alternatives[8];
    t_bpos  new_pos;
    int     i;

    set_alternative_directions(alternatives, direction);
    i = 0;
    while (i < 4)
    {
        new_pos.x = enemy->b_pos.x + alternatives[i].x * speed;
        new_pos.y = enemy->b_pos.y + alternatives[i].y * speed;
        if (!isfinite(new_pos.x) || !isfinite(new_pos.y))
        {
            i++;
            continue;
        }
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


void random_point_around_enemy(t_enemy *enemy, double *out_rx, double *out_ry)
{
    int   r;
    double frac;

    if (!enemy || !out_rx || !out_ry)
        return ;
    r = ft_rand() % 1000;
    frac = (double)r / 1000.0;
    *out_rx = enemy->b_pos.x + (frac * 2.0 - 1.0) * PATROL_TARGET_RADIUS;
    r = ft_rand() % 1000;
    frac = (double)r / 1000.0;
    *out_ry = enemy->b_pos.y + (frac * 2.0 - 1.0) * PATROL_TARGET_RADIUS;
}

bool choose_random_patrol_target(t_enemy *enemy, t_parsed_data *pd)
{
    int attempts;
    double rx;
    double ry;

    if (!enemy || !pd)
        return (false);
    attempts = 0;
    while (attempts < 50)
    {
        random_point_around_enemy(enemy, &rx, &ry);
        if (rx < 1.0 || ry < 1.0
            || rx >= (double)pd->level.max_x - 1.0
            || ry >= (double)pd->level.max_y - 1.0)
        {
            attempts++;
            continue ;
        }
        if (!is_position_blocked_circle(pd, rx, ry, COLLISION_RADIUS)
            && has_line_of_sight(pd, enemy->b_pos, (t_bpos){rx, ry}))
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
