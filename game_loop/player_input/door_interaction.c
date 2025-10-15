#include "../../cube.h"

static void check_nearby_doors(t_parsed_data *pd, int px, int py)
{
    if (pd->map_grid[py][px + 1] == 'D')
        pd->map_grid[py][px + 1] = 'O';
    else if (pd->map_grid[py][px + 1] == 'O')
        pd->map_grid[py][px + 1] = 'D';

    if (pd->map_grid[py][px - 1] == 'D')
        pd->map_grid[py][px - 1] = 'O';
    else if (pd->map_grid[py][px - 1] == 'O')
        pd->map_grid[py][px - 1] = 'D';

    if (pd->map_grid[py + 1][px] == 'D')
        pd->map_grid[py + 1][px] = 'O';
    else if (pd->map_grid[py + 1][px] == 'O')
        pd->map_grid[py + 1][px] = 'D';

    if (pd->map_grid[py - 1][px] == 'D')
        pd->map_grid[py - 1][px] = 'O';
    else if (pd->map_grid[py - 1][px] == 'O')
        pd->map_grid[py - 1][px] = 'D';
}

void interact_with_door(t_parsed_data *pd)
{
    static bool e_was_pressed = false;
    int px = (int)pd->player.bpos.x;
    int py = (int)pd->player.bpos.y;
    bool e_pressed = pd->keys.pressed[MLX_KEY_E];
    if (e_pressed && !e_was_pressed)
        check_nearby_doors(pd, px, py);
    e_was_pressed = e_pressed;
}

void init_door_texture(t_parsed_data *pd)
{
    pd->door_txt.txtr = mlx_load_png(DOOR_TEXTURE);
    if (pd->door_txt.txtr == NULL)
    {
        print_error("Error\nDoor Texture Path Missing.\n");
        mind_free_all(EXIT_FAILURE);
    }
    pd->door_txt.img = mlx_texture_to_image(pd->mlx, pd->door_txt.txtr);
    if (pd->door_txt.img == NULL)
        mind_free_all(EXIT_FAILURE);
}