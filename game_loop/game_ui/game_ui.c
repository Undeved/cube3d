#include "../../cube.h"

void    toggle_game_ui(t_parsed_data *pd)
{
    // enable mini map
    pd->minimap.img->enabled = true;
    pd->game_ui.gun.img->enabled = true;
    // make this load all ui and have actual structs for playable characters.
    puts("choosing player...");
    if (pd->chars_menu.select_index == JESSE)
        mlx_put_string(pd->mlx, "PlAYER: JESSE", 10, 20);
    else if (pd->chars_menu.select_index == CHORUS)
        mlx_put_string(pd->mlx, "PlAYER: CHORIS", 10, 20);
    else if (pd->chars_menu.select_index == OUSSMAC)
        mlx_put_string(pd->mlx, "PlAYER: OUSSMAC", 10, 20);
}
