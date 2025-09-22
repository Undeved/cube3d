#include "../cube.h"

static void escape_key(mlx_key_data_t keydata, void *param)
{
    t_parsed_data *pd;

    pd = param;
    if (keydata.key == MLX_KEY_ESCAPE)
    {
        mlx_terminate(pd->mlx);
        mind_free_all(EXIT_SUCCESS);
    }
}

static void precise_direction(t_parsed_data *pd)
{
    if (pd->player.dir == 'N')
    {
        pd->player.bdir.x = 0;
        pd->player.bdir.y = 1;
    }
    else if (pd->player.dir == 'E')
    {
        pd->player.bdir.x = 1;
        pd->player.bdir.y = 0;
    }
    else if (pd->player.dir == 'S')
    {
        pd->player.bdir.x = 0;
        pd->player.bdir.y = -1;
    }
    else if (pd->player.dir == 'W')
    {
        pd->player.bdir.x = -1;
        pd->player.bdir.y = 0;
    }
}

static void init_precise_data(t_parsed_data *pd)
{
    pd->player.bpos.x = pd->player.pos.x;
    pd->player.bpos.y = pd->player.pos.y;
    precise_direction(pd);
}

void game_loop(t_parsed_data *pd)
{
    init_precise_data(pd);
    pd->mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
    if(!pd->mlx)
        mind_free_all(EXIT_FAILURE);
    pd->screen = mlx_new_image(pd->mlx, WIDTH, HEIGHT);
    if(!pd->mlx)
        mind_free_all(EXIT_FAILURE);
    if (mlx_image_to_window(pd->mlx, pd->screen, 0, 0) == -1)
        mind_free_all(EXIT_FAILURE);
    mlx_key_hook(pd->mlx, escape_key, pd);
    mlx_key_hook(pd->mlx, handle_player_input, pd);
    mlx_loop_hook(pd->mlx, game_render, pd);
    mlx_loop(pd->mlx);
    mlx_terminate(pd->mlx);
}
