#include "../../cube.h"

static void render_ch_button_index(t_parsed_data *pd)
{
    pd->chars_menu.b_jesse.hoverd = false;
    pd->chars_menu.b_chorus.hoverd = false;
    pd->chars_menu.b_oussmac.hoverd = false;
    if (pd->chars_menu.button_index == 0)
        pd->chars_menu.b_jesse.hoverd = true;
    else if (pd->chars_menu.button_index == 1)
        pd->chars_menu.b_chorus.hoverd = true;
    else if (pd->chars_menu.button_index == 2)
        pd->chars_menu.b_oussmac.hoverd = true;
}

static void update_ch_button_state(t_parsed_data *pd)
{
    render_ch_button_index(pd);
    if (pd->chars_menu.b_jesse.hoverd)
    {
        pd->chars_menu.b_jesse_hv.img->enabled = true;
        pd->chars_menu.b_jesse.img->enabled = false;
    }
    else
    {
        pd->chars_menu.b_jesse.img->enabled = true;
        pd->chars_menu.b_jesse_hv.img->enabled = false;
    }

    if (pd->chars_menu.b_chorus.hoverd)
    {
        pd->chars_menu.b_chorus_hv.img->enabled = true;
        pd->chars_menu.b_chorus.img->enabled = false;
    }
    else
    {
        pd->chars_menu.b_chorus.img->enabled = true;
        pd->chars_menu.b_chorus_hv.img->enabled = false;
    }

    if (pd->chars_menu.b_oussmac.hoverd)
    {
        pd->chars_menu.b_oussmac_hv.img->enabled = true;
        pd->chars_menu.b_oussmac.img->enabled = false;
    }
    else
    {
        pd->chars_menu.b_oussmac.img->enabled = true;
        pd->chars_menu.b_oussmac_hv.img->enabled = false;
    }
}

void    characters_menu(t_parsed_data *pd)
{
    if (pd->ui_index != 1)
        return ;
    update_ch_button_state(pd);
}

