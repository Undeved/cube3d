#include "../cube.h"

int find_current_direction(t_enemy *enemy, double directions[4][2])
{
    int i;
    int current_dir_index;

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

int calculate_new_direction(int current_dir_index)
{
    int turn_direction;
    int new_dir_index;

    if (ft_rand() % 2 == 0)
        turn_direction = -1;
    else
        turn_direction = 1;
    new_dir_index = (current_dir_index + turn_direction + 4) % 4;
    return (new_dir_index);
}

void change_enemy_direction(t_enemy *enemy)
{
    double directions[4][2];
    int    current_dir_index;
    int    new_dir_index;

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

void calculate_direction_to_player(t_enemy *enemy, t_bpos player_pos,
        t_bpos *direction)
{
    double length;

    direction->x = player_pos.x - enemy->b_pos.x;
    direction->y = player_pos.y - enemy->b_pos.y;
    length = sqrt(direction->x * direction->x + direction->y * direction->y);
    if (length > 0)
    {
        direction->x /= length;
        direction->y /= length;
    }
}

bool is_valid_move_position(t_parsed_data *pd, int map_x, int map_y)
{
    char tile;

    if (!pd)
        return (false);
    if (map_y < 0 || map_y >= pd->level.max_y
     || map_x < 0 || map_x >= pd->level.max_x)
        return (false);

    tile = pd->map_grid[map_y][map_x];
    if (tile == '0' || tile == 'O')
        return (true);

    return (false);
}
