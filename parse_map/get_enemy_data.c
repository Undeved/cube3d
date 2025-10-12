#include "../cube.h"

static bool is_enemy(char c)
{
    if (c == 'X' || c == 'Z' || c == 'Y')
        return (true);
    return (false);
}


static void scrap_enemy_data(int x, int y, char c, t_enemy *curr_enemy)
{
    double  directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int     dir_index;
    
    // Convert int position to double for smoother movement
    curr_enemy->b_pos.x = (double)x + 0.5;
    curr_enemy->b_pos.y = (double)y + 0.5;
    curr_enemy->patrol_origin = curr_enemy->b_pos; // Store original position
    
    // Set random initial direction
    dir_index = rand() % 4;
    curr_enemy->dir.x = directions[dir_index][0];
    curr_enemy->dir.y = directions[dir_index][1];
    
    // Initialize state and speeds based on type
    curr_enemy->state = ENEMY_PATROL;
    
    if (c == 'X')
    {
        curr_enemy->type = FT_SKIN_WALKER;
        curr_enemy->patrol_speed = SKIN_WALKER_PATROL_SPEED;
        curr_enemy->chase_speed = SKIN_WALKER_CHASE_SPEED;
        curr_enemy->pos.x = x;
        curr_enemy->pos.y = y;
        curr_enemy->skin.img = NULL;
        curr_enemy->dead = false;
        curr_enemy->damage = SKIN_WALKER_DAMAGE;
        curr_enemy->health = SKIN_WALKER_HEALTH;
    }
    else if (c == 'Z')
    {
        curr_enemy->type = MEMORY_LEAK;
        curr_enemy->patrol_speed = MEMORY_LEAK_PATROL_SPEED;
        curr_enemy->chase_speed = MEMORY_LEAK_CHASE_SPEED;
        curr_enemy->pos.x = x;
        curr_enemy->pos.y = y;
        curr_enemy->skin.img = NULL;
        curr_enemy->dead = false;
        curr_enemy->damage = MEMORY_LEAK_DAMAGE;
        curr_enemy->health = MEMORY_LEAK_HEALTH;
    }
    else if (c == 'Y')
    {
        curr_enemy->type = SEGV;
        curr_enemy->patrol_speed = SEGV_PATROL_SPEED;
        curr_enemy->chase_speed = SEGV_CHASE_SPEED;
        curr_enemy->pos.x = x;
        curr_enemy->pos.y = y;
        curr_enemy->skin.img = NULL;
        curr_enemy->dead = false;
        curr_enemy->damage = SEGV_DAMAGE;
        curr_enemy->health = SEGV_HEALTH;
    }
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
