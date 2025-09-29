#include "../cube.h"
void    update_enemies(t_parsed_data *pd);
void    game_render(void *param)
{
    t_parsed_data   *pd;

    pd = param;
    main_menu(pd);
    characters_menu(pd);
    if (!pd->level.game_started)
        return ;
    update_player_data(pd);
    update_enemies(pd);
    raycast_system(pd);
    raycast_render(pd);
    render_radar(pd);
    // draw_minimap(pd);
}
