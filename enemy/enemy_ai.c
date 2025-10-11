#include "../cube.h"

void chase_player(t_enemy *enemy, t_bpos player_pos, double speed,
        t_parsed_data *pd)
{
    t_bpos  direction;
    t_bpos  new_pos;
    int     map_x;
    int     map_y;

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

void calculate_direction_to_origin(t_enemy *enemy, t_bpos *direction)
{
    double length;

    direction->x = enemy->patrol_origin.x - enemy->b_pos.x;
    direction->y = enemy->patrol_origin.y - enemy->b_pos.y;
    length = sqrt(direction->x * direction->x + direction->y * direction->y);
    if (length > 0)
    {
        direction->x /= length;
        direction->y /= length;
    }
}

bool return_to_patrol(t_enemy *enemy, t_parsed_data *pd)
{
    double  distance_to_origin;
    t_bpos  direction;
    t_bpos  new_pos;
    int     map_x;
    int     map_y;

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
        change_enemy_direction(enemy);
    return (false);
}

void set_alternative_directions(t_bpos alternatives[8], t_bpos direction)
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
