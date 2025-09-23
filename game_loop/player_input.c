#include "../cube.h"

void handle_player_input(mlx_key_data_t keydata, void *param)
{
    t_parsed_data *pd;

    pd = param;
    if (keydata.key == MLX_KEY_ESCAPE)
    {
        mlx_terminate(pd->mlx);
        mind_free_all(EXIT_SUCCESS);
    }
    if (keydata.key == MLX_KEY_W)
    {
        pd->player.bpos.x += pd->player.bdir.x * SPEED;
        pd->player.bpos.y += pd->player.bdir.y * SPEED;
    }
    if (keydata.key == MLX_KEY_S)
    {
        pd->player.bpos.x -= pd->player.bdir.x * SPEED;
        pd->player.bpos.y -= pd->player.bdir.y * SPEED;
    }


    if (keydata.key == MLX_KEY_A)
    {
        pd->player.bpos.x += pd->player.bdir.y * SPEED;
        pd->player.bpos.y += -pd->player.bdir.x * SPEED;
    }
    if (keydata.key == MLX_KEY_D)
    {
        pd->player.bpos.x += -pd->player.bdir.y * SPEED;
        pd->player.bpos.y += pd->player.bdir.x * SPEED;
    }
    if (keydata.key == MLX_KEY_RIGHT)
    {
        double old_x = pd->player.bdir.x;
        double old_y = pd->player.bdir.y;
        pd->player.bdir.x = old_x * cos(ROT_SPEED) - old_y * sin(ROT_SPEED);
        pd->player.bdir.y = old_x * sin(ROT_SPEED) + old_y * cos(ROT_SPEED);
    }
    if (keydata.key == MLX_KEY_LEFT)
    {
        double old_x = pd->player.bdir.x;
        double old_y = pd->player.bdir.y;
        pd->player.bdir.x = old_x * cos(-ROT_SPEED) - old_y * sin(-ROT_SPEED);
        pd->player.bdir.y = old_x * sin(-ROT_SPEED) + old_y * cos(-ROT_SPEED);

    }
}
