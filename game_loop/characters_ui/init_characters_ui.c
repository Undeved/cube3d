#include "../../cube.h"

static void init_hovered_char(t_parsed_data *pd)
{
    pd->chars_menu.b_jesse_hv.txtr = mlx_load_png(JESSE_BUTTON_HV);
    pd->chars_menu.b_chorus_hv.txtr = mlx_load_png(CHORUS_BUTTON_HV);
    pd->chars_menu.b_oussmac_hv.txtr = mlx_load_png(OUSSMAC_BUTTON_HV);
    if (!pd->chars_menu.b_jesse_hv.txtr || !pd->chars_menu.b_chorus_hv.txtr || !pd->chars_menu.b_oussmac_hv.txtr)
        ui_error();

    pd->chars_menu.b_jesse_hv.img = mlx_texture_to_image(pd->mlx, pd->chars_menu.b_jesse_hv.txtr);
    if (!pd->chars_menu.b_jesse_hv.img || mlx_image_to_window(pd->mlx, pd->chars_menu.b_jesse_hv.img,
            JESSE_X, JESSE_Y))
        mind_free_all(EXIT_FAILURE);
    
    pd->chars_menu.b_chorus_hv.img = mlx_texture_to_image(pd->mlx, pd->chars_menu.b_chorus_hv.txtr);
    if (!pd->chars_menu.b_chorus_hv.img || mlx_image_to_window(pd->mlx, pd->chars_menu.b_chorus_hv.img,
            CHORUS_X, CHORUS_Y))
        mind_free_all(EXIT_FAILURE);

    pd->chars_menu.b_oussmac_hv.img = mlx_texture_to_image(pd->mlx, pd->chars_menu.b_oussmac_hv.txtr);
    if (!pd->chars_menu.b_oussmac_hv.img || mlx_image_to_window(pd->mlx, pd->chars_menu.b_oussmac_hv.img,
            OUSSMAC_X, OUSSMAC_Y))
        mind_free_all(EXIT_FAILURE);
}

static void init_char_flags(t_parsed_data *pd)
{
    pd->chars_menu.b_jesse.hoverd = true;
    pd->chars_menu.b_chorus.hoverd = false;
    pd->chars_menu.b_oussmac.hoverd = false;

    // make it false but in code it is technacly hovered by default.
    pd->chars_menu.b_jesse_hv.img->enabled = false;
    pd->chars_menu.b_chorus_hv.img->enabled = false;
    pd->chars_menu.b_oussmac_hv.img->enabled = false;
}

static void init_char_buttons(t_parsed_data *pd)
{
    pd->chars_menu.b_jesse.txtr = mlx_load_png(JESSE_BUTTON);
    pd->chars_menu.b_chorus.txtr = mlx_load_png(CHORUS_BUTTON);
    pd->chars_menu.b_oussmac.txtr = mlx_load_png(OUSSMAC_BUTTON);
    if (!pd->chars_menu.b_jesse.txtr || !pd->chars_menu.b_chorus.txtr || !pd->chars_menu.b_oussmac.txtr)
        ui_error();

    pd->chars_menu.b_jesse.img = mlx_texture_to_image(pd->mlx, pd->chars_menu.b_jesse.txtr);
    if (!pd->chars_menu.b_jesse.img || mlx_image_to_window(pd->mlx, pd->chars_menu.b_jesse.img,
            JESSE_X, JESSE_Y - BTN_POP))
        mind_free_all(EXIT_FAILURE);
    pd->chars_menu.b_jesse.img->enabled = false;

    pd->chars_menu.b_chorus.img = mlx_texture_to_image(pd->mlx, pd->chars_menu.b_chorus.txtr);
    if (!pd->chars_menu.b_chorus.img || mlx_image_to_window(pd->mlx, pd->chars_menu.b_chorus.img,
            CHORUS_X, CHORUS_Y - BTN_POP))
        mind_free_all(EXIT_FAILURE);
    pd->chars_menu.b_chorus.img->enabled = false;

    pd->chars_menu.b_oussmac.img = mlx_texture_to_image(pd->mlx, pd->chars_menu.b_oussmac.txtr);
    if (!pd->chars_menu.b_oussmac.img || mlx_image_to_window(pd->mlx, pd->chars_menu.b_oussmac.img,
            OUSSMAC_X, OUSSMAC_Y - BTN_POP))
        mind_free_all(EXIT_FAILURE);
    pd->chars_menu.b_oussmac.img->enabled = false;
    init_hovered_char(pd);
    init_char_flags(pd);
}

static void init_selected_button(t_parsed_data *pd)
{
    pd->chars_menu.selected.txtr = mlx_load_png(SELECTED_BUTTON);
    if (!pd->chars_menu.selected.txtr)
        ui_error();
    pd->chars_menu.selected.img = mlx_texture_to_image(pd->mlx, pd->chars_menu.selected.txtr);
    if (!pd->chars_menu.selected.img || mlx_image_to_window(pd->mlx, pd->chars_menu.selected.img, SELECT_JESSE_X, SELECT_Y) == -1)
        mind_free_all(EXIT_FAILURE);
    pd->chars_menu.selected.img->enabled = false;
    pd->chars_menu.select_index = JESSE;
}

void    init_characters_menu(t_parsed_data *pd)
{
    pd->chars_menu.bg.txtr = mlx_load_png(CHARS_BG);
    if (!pd->chars_menu.bg.txtr)
        ui_error();
    pd->chars_menu.bg.img = mlx_texture_to_image(pd->mlx, pd->chars_menu.bg.txtr);
    if (!pd->chars_menu.bg.img || mlx_image_to_window(pd->mlx, pd->chars_menu.bg.img, 0, 0) == -1)
        mind_free_all(EXIT_FAILURE);
    init_selected_button(pd);
    init_char_buttons(pd);
    pd->chars_menu.bg.img->enabled = false;
    pd->chars_menu.button_index = 0; // index_0 is default character jesse
}
