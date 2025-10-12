#include "../../cube.h"

void    init_game_ui(t_parsed_data *pd)
{
    pd->game_ui.vignette.txtr = mlx_load_png(VIGNETTE);
    if (!pd->game_ui.vignette.txtr)
        ui_error();
    pd->game_ui.vignette.img = mlx_texture_to_image(pd->mlx, pd->game_ui.vignette.txtr);
    if(!pd->game_ui.vignette.img|| mlx_image_to_window(pd->mlx, pd->game_ui.vignette.img, 0, 0) == -1)
        mind_free_all(EXIT_FAILURE);
    // init gameover screen
    pd->game_ui.game_over.txtr = mlx_load_png(GAME_OVER);
    if (!pd->game_ui.game_over.txtr)
        ui_error();
    pd->game_ui.game_over.img = mlx_texture_to_image(pd->mlx, pd->game_ui.game_over.txtr);
    if(!pd->game_ui.game_over.img|| mlx_image_to_window(pd->mlx, pd->game_ui.game_over.img, 0, 0) == -1)
        mind_free_all(EXIT_FAILURE);
    pd->game_ui.game_over.img->enabled = false;
    pd->player.is_dead = false;
    mlx_delete_texture(pd->game_ui.game_over.txtr);
    pd->game_ui.game_over.txtr = NULL;
    pd->game_ui.vignette.img->enabled = false; // disable it for now
    // maybe delete vignette texture as well if not deleted elsewhere
}
