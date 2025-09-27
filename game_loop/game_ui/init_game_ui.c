#include "../../cube.h"

static void init_gun(t_parsed_data *pd)
{
    pd->game_ui.gun.txtr = mlx_load_png(GUN_IDLE);
    if (!pd->game_ui.gun.txtr)
        ui_error();
    pd->game_ui.gun.img = mlx_texture_to_image(pd->mlx, pd->game_ui.gun.txtr);
    if(!pd->game_ui.gun.img|| mlx_image_to_window(pd->mlx, pd->game_ui.gun.img, GUN_X, GUN_Y) == -1)
        mind_free_all(EXIT_FAILURE);
    pd->game_ui.gun_aim.txtr = mlx_load_png(GUN_AIM);
    if (!pd->game_ui.gun_aim.txtr)
        ui_error();
    pd->game_ui.gun_aim.img = mlx_texture_to_image(pd->mlx, pd->game_ui.gun_aim.txtr);
    if(!pd->game_ui.gun_aim.img|| mlx_image_to_window(pd->mlx, pd->game_ui.gun_aim.img, GUN_AIM_X, GUN_AIM_Y) == -1)
        mind_free_all(EXIT_FAILURE);
    pd->game_ui.gun_aim.img->enabled = false;
    pd->game_ui.gun.img->enabled = false;

}

void    init_game_ui(t_parsed_data *pd)
{
    init_gun(pd);
    pd->game_ui.vignette.txtr = mlx_load_png(VIGNETTE);
    if (!pd->game_ui.vignette.txtr)
        ui_error();
    pd->game_ui.vignette.img = mlx_texture_to_image(pd->mlx, pd->game_ui.vignette.txtr);
    if(!pd->game_ui.vignette.img|| mlx_image_to_window(pd->mlx, pd->game_ui.vignette.img, 0, 0) == -1)
        mind_free_all(EXIT_FAILURE);
}
