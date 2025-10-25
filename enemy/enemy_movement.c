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
        new_dir_index = ft_rand() % 4;
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

static double clamp_d(double v, double a, double b)
{
    if (v < a) return (a);
    if (v > b) return (b);
    return (v);
}

static bool circle_intersects_tile(double cx, double cy, double r,
        int tx, int ty)
{
    double nx = clamp_d(cx, (double)tx, (double)tx + 1.0);
    double ny = clamp_d(cy, (double)ty, (double)ty + 1.0);
    double dx = cx - nx;
    double dy = cy - ny;
    return (dx * dx + dy * dy < r * r);
}

bool is_position_blocked_circle(t_parsed_data *pd, double cx, double cy,
        double radius)
{
    int tx_min = (int)floor(cx - radius);
    int tx_max = (int)floor(cx + radius);
    int ty_min = (int)floor(cy - radius);
    int ty_max = (int)floor(cy + radius);
    int tx;
    int ty;

    if (!pd)
        return (true);
    if (tx_min < 0 || ty_min < 0 || tx_max >= pd->level.max_x
        || ty_max >= pd->level.max_y)
        return (true);

    tx = tx_min;
    while (tx <= tx_max)
    {
        ty = ty_min;
        while (ty <= ty_max)
        {
            if (pd->map_grid[ty][tx] == '1' || pd->map_grid[ty][tx] == 'D')
            {
                if (circle_intersects_tile(cx, cy, radius, tx, ty))
                    return (true);
            }
            ty++;
        }
        tx++;
    }
    return (false);
}


bool is_valid_move_position_circle_global(t_parsed_data *pd, double x, double y)
{
    return (!is_position_blocked_circle(pd, x, y, COLLISION_RADIUS));
}


