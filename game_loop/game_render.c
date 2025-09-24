#include "../cube.h"

void    game_render(void *param)
{
    t_parsed_data   *pd;

    pd = param;
    main_menu(pd);
    characters_menu(pd);
    if (!pd->level.game_started)
        return ;
    update_player_data(pd);
    raycast_render(pd);
    draw_minimap(pd);
}