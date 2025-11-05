#include "../../cube.h"

void toggle_menu(t_parsed_data *pd, bool trigger)
{
    pd->menu.b_start.img->enabled = trigger;
    pd->menu.b_chars.img->enabled = trigger;
    pd->menu.b_exit.img->enabled = trigger;

    pd->menu.b_start_hv.img->enabled = trigger;
    pd->menu.b_chars_hv.img->enabled = trigger;
    pd->menu.b_exit_hv.img->enabled = trigger;    
    
    pd->menu.bg.img->enabled = trigger;
    pd->menu.title.img->enabled = trigger;
}

void    toggle_characters_ui(t_parsed_data *pd, bool trigger)
{
    pd->chars_menu.b_jesse.img->enabled = trigger;
    pd->chars_menu.b_chorus.img->enabled = trigger;
    pd->chars_menu.b_oussmac.img->enabled = trigger;

    pd->chars_menu.b_jesse_hv.img->enabled = trigger;
    pd->chars_menu.b_chorus_hv.img->enabled = trigger;
    pd->chars_menu.b_oussmac_hv.img->enabled = trigger;  
    
    pd->chars_menu.bg.img->enabled = trigger;
    pd->chars_menu.selected.img->enabled = trigger;
}

void    handle_character_ui_input(mlx_key_data_t keydata, t_parsed_data *pd)
{
    if (pd->level.game_started || pd->ui_index != 1 || keydata.action != MLX_PRESS)
        return ;
    if (keydata.key == MLX_KEY_ESCAPE)
    {
        toggle_characters_ui(pd, false);
        toggle_menu(pd, true);
        pd->ui_index = 0;
        return ;
    }
    else if (keydata.key == MLX_KEY_RIGHT)
        pd->chars_menu.button_index++;
    else if (keydata.key == MLX_KEY_LEFT)
        pd->chars_menu.button_index--;
    else if (keydata.key == MLX_KEY_ENTER)
        characters_trigger_click(pd);
    if (pd->chars_menu.button_index > 2)
        pd->chars_menu.button_index = 0;
    else if (pd->chars_menu.button_index < 0)
        pd->chars_menu.button_index = 2;
}

void    menu_trigger_click(t_parsed_data *pd)
{
    if (pd->menu.button_index == 0)
    {
        pd->level.game_started = true;
        pd->screen->enabled = true;
        pd->ui_index = 2;
        toggle_menu(pd, false);
        mlx_set_cursor_mode(pd->mlx, MLX_MOUSE_HIDDEN); // hide cursor.
        // delete menu textures and images, will not be used anymore.
        toggle_game_ui(pd);
        return ;
    }
    else if (pd->menu.button_index == 1)
    {
        toggle_menu(pd, false);
        toggle_characters_ui(pd, true);
        pd->ui_index = 1;
        return ;
    }
    else if (pd->menu.button_index == 2)
    {
        print_comm("Exited Game\n");
        mlx_close_window(pd->mlx);
        return ;
    }
}

void    handle_ui_input(mlx_key_data_t keydata, t_parsed_data *pd)
{
    handle_character_ui_input(keydata, pd);
    if (pd->level.game_started || pd->ui_index != 0 || keydata.action != MLX_PRESS)
        return ;
    if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
        pd->menu.button_index++;
    else if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
        pd->menu.button_index--;
    else if (keydata.key == MLX_KEY_ENTER || pd->mouse_clicked)
    {
        // select button in menu logic.
        menu_trigger_click(pd);
    }
    if (pd->menu.button_index > 2)
        pd->menu.button_index = 0;
    else if (pd->menu.button_index < 0)
        pd->menu.button_index = 2;
}
