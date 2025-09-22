#include "../cube.h"

void handle_player_input(mlx_key_data_t keydata, void *param)
{
    t_parsed_data *pd;

    pd = param;
    if (keydata.key == MLX_KEY_W)
        pd->player.bpos.y -= SPEED;
    if (keydata.key == MLX_KEY_S)
        pd->player.bpos.y += SPEED;
    if (keydata.key == MLX_KEY_A)
        pd->player.bpos.x -= SPEED;
    if (keydata.key == MLX_KEY_D)
        pd->player.bpos.x += SPEED;
}
