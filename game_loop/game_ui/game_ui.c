#include "../../cube.h"

void    toggle_game_ui(t_parsed_data *pd)
{
    pd->minimap.img->enabled = true;
    puts("choosing player...");
    setup_character(pd);
    setup_health_ui(pd);
    init_game_ui(pd);
    pd->game_ui.gun.img->enabled = true;
}

void    init_game_ui(t_parsed_data *pd)
{
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
}
