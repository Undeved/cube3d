#include "../../cube.h"

// static void init_gun(t_parsed_data *pd)
// {

// }

void    init_game_ui(t_parsed_data *pd)
{
    // init_gun(pd);
    pd->game_ui.vignette.txtr = mlx_load_png(VIGNETTE);
    if (!pd->game_ui.vignette.txtr)
        ui_error();
    pd->game_ui.vignette.img = mlx_texture_to_image(pd->mlx, pd->game_ui.vignette.txtr);
    if(!pd->game_ui.vignette.img|| mlx_image_to_window(pd->mlx, pd->game_ui.vignette.img, 0, 0) == -1)
        mind_free_all(EXIT_FAILURE);
}
