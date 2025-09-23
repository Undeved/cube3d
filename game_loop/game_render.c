#include "../cube.h"

void    game_render(void *param)
{
    t_parsed_data   *pd;

    pd = param;
    update_player_data(pd);
    draw_minimap(pd);
}