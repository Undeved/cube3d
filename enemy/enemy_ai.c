#include "../cube.h"

void chase_player(t_enemy *enemy, t_bpos player_pos, double speed,
        t_parsed_data *pd)
{
    t_bpos  direction;
    t_bpos  new_pos;

    calculate_direction_to_player(enemy, player_pos, &direction);
    new_pos.x = enemy->b_pos.x + direction.x * speed;
    new_pos.y = enemy->b_pos.y + direction.y * speed;
    if (is_valid_move_position_circle_global(pd, new_pos.x, new_pos.y))
    {
        enemy->b_pos = new_pos;
        enemy->dir.x = direction.x;
        enemy->dir.y = direction.y;
    }
}

double calculate_distance_to_origin(t_enemy *enemy)
{
    double dx;
    double dy;
    double distance;

    dx = enemy->b_pos.x - enemy->patrol_origin.x;
    dy = enemy->b_pos.y - enemy->patrol_origin.y;
    distance = sqrt(dx * dx + dy * dy);
    return (distance);
}


static t_bpos find_nearest_valid_position(t_enemy *enemy, t_parsed_data *pd)
{
    t_bpos positions[8];
    int i;
    double radius = 1.0;

    for (i = 0; i < 8; i++)
    {
        double angle = (i * M_PI) / 4.0;
        positions[i].x = enemy->b_pos.x + cos(angle) * radius;
        positions[i].y = enemy->b_pos.y + sin(angle) * radius;
        
        if (positions[i].x >= 1.0 && positions[i].x < pd->level.max_x - 1.0 &&
            positions[i].y >= 1.0 && positions[i].y < pd->level.max_y - 1.0 &&
            !is_position_blocked_circle(pd, positions[i].x, positions[i].y, COLLISION_RADIUS))
        {
            return positions[i];
        }
    }
    return enemy->b_pos;
}

bool return_to_patrol(t_enemy *enemy, t_parsed_data *pd)
{
    double  distance_to_origin;
    
    distance_to_origin = calculate_distance_to_origin(enemy);
    if (distance_to_origin < 0.5)
        return (true);
    t_bpos target = enemy->patrol_origin;
    
    if (!move_towards_target(enemy, pd, target, enemy->patrol_speed))
    {
        enemy->patrol_origin = find_nearest_valid_position(enemy, pd);
        return (true);
    }
    
    return (false);
}

void set_alternative_directions(t_bpos alternatives[8], t_bpos direction)
{
    alternatives[0].x = direction.x;
    alternatives[1].x = direction.x * 0.7;
    alternatives[2].x = direction.y;
    alternatives[3].x = -direction.y;
    alternatives[4].x = direction.x * 0.7;
    alternatives[5].y = -direction.x * 0.7;
    alternatives[6].y = direction.x * 0.7;
    alternatives[7].y = -direction.y;
}
