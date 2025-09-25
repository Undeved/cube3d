#include "../cube.h"

static void precise_direction(t_parsed_data *pd)
{
    if (pd->player.dir == 'N')
    {
        pd->player.bdir.x = 0;
        pd->player.bdir.y = -1;
    }
    else if (pd->player.dir == 'E')
    {
        pd->player.bdir.x = 1;
        pd->player.bdir.y = 0;
    }
    else if (pd->player.dir == 'S')
    {
        pd->player.bdir.x = 0;
        pd->player.bdir.y = 1;
    }
    else if (pd->player.dir == 'W')
    {
        pd->player.bdir.x = -1;
        pd->player.bdir.y = 0;
    }
}

static void init_key_flags(t_parsed_data *pd)
{
    int i;

    i = 0;
    while (i < KEYS_NUMBER)
        pd->keys.pressed[i++] = false;
}

static void init_precise_data(t_parsed_data *pd)
{
    pd->player.bpos.x = pd->player.pos.x + NUDGE_FROM_WALL;
    pd->player.bpos.y = pd->player.pos.y + NUDGE_FROM_WALL;
    pd->level.game_started = false;
    precise_direction(pd);
    init_key_flags(pd);
}

static void init_mini_map(t_parsed_data *pd)
{
    pd->minimap.img = mlx_new_image(pd->mlx, MINI_MAP_SIZE, MINI_MAP_SIZE);
    if (!pd->minimap.img || mlx_image_to_window(pd->mlx, pd->minimap.img, 0, 0) == -1)
        mind_free_all(EXIT_FAILURE);
}

static void init_gameplay_screen(t_parsed_data *pd)
{
    pd->screen = mlx_new_image(pd->mlx, WIDTH, HEIGHT);
    if(!pd->screen || mlx_image_to_window(pd->mlx, pd->screen, 0, 0) == -1)
        mind_free_all(EXIT_FAILURE);
    pd->screen->enabled = false;
}

void game_loop(t_parsed_data *pd)
{
    init_precise_data(pd);
    pd->mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
    if(!pd->mlx)
        mind_free_all(EXIT_FAILURE);
    init_gameplay_screen(pd);
    init_mini_map(pd);
    init_main_menu(pd);
    init_characters_menu(pd);

    mlx_key_hook(pd->mlx, handle_player_input, pd);
    mlx_loop_hook(pd->mlx, game_render, pd);
    mlx_loop(pd->mlx);
    mlx_terminate(pd->mlx); // remove this and keep it in gc
}
