#include "../cube.h"

void escape_handler(mlx_key_data_t keydata, void* param)
{
    mlx_t   *mlx;

    mlx = param;
    (void)mlx;
    if (keydata.key == MLX_KEY_ESCAPE)
        mind_free_all(EXIT_SUCCESS);
}

void basic_game_loop(void)
{
    mlx_t   *mlx;

    mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
    if (!mlx)
        mind_free_all(EXIT_FAILURE);
    mlx_key_hook(mlx, escape_handler, mlx);
    mlx_loop_hook(mlx, simple_raycast,mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);
}
