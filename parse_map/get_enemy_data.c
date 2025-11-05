#include "../cube.h"

static bool is_enemy(char c)
{
    if (c == 'X' || c == 'Z' || c == 'Y')
        return (true);
    return (false);
}

static uint8_t count_enemies(char **map_grid)
{
    int     y;
    int     x;
    uint8_t count;

    y = 0;
    count = 0;
    while (map_grid[y])
    {
        x = 0;
        while (map_grid[y][x])
        {
            if (map_grid[y][x] == 'X' 
                || map_grid[y][x] == 'Z' || map_grid[y][x] == 'Y')
                count++;
            x++;
        }
        y++;
    }
    return (count);
}

static t_enemy *allocate_enemy_array(char **map_grid, uint8_t *enemy_count)
{
    t_enemy *enemies;

    *enemy_count = count_enemies(map_grid);
    if (*enemy_count > MAX_ENEMIES)
    {
        print_error("Error\nToo Many Monsters.\n");
        mind_free_all(EXIT_FAILURE);
    }
    if (*enemy_count == 0)
        return (NULL);
    enemies = allocate_gc(malloc(sizeof(t_enemy) * (*enemy_count)));
    return(enemies);
}

void    get_enemies(t_cube *cube)
{
    int y;
    int x;
    int enemy_index;

    cube->pd.enemies =  allocate_enemy_array(cube->pd.map_grid, &cube->pd.enemy_count);
    if (!cube->pd.enemies)
        return ;
    enemy_index = 0;
    y = 0;
    while (cube->pd.map_grid[y])
    {
        x = 0;
        while (cube->pd.map_grid[y][x])
        {
            if (is_enemy(cube->pd.map_grid[y][x]))
            {
                scrap_enemy_data(x, y, cube->pd.map_grid[y][x], &cube->pd.enemies[enemy_index++]);
                cube->pd.map_grid[y][x] = '0';
            }
            else if (is_door(cube->pd.map_grid[y][x]))
            {
                if (!validate_door(&cube->pd, x, y))
                {
                    print_error("Error\nInvalid Door Placement.\n");
                    mind_free_all(EXIT_FAILURE);
                }
            }
            x++;
        }
        y++;
    }
}
