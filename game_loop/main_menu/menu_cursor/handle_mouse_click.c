#include "../../../cube.h"

static void game_mouse_input(mouse_key_t button, action_t action, modifier_key_t mods, t_parsed_data *pd)
{
    
    if (pd->ui_index != 2)
        return ;
    (void)mods;
    if (action == MLX_PRESS || action == MLX_REPEAT)
    {
        if (button == MLX_MOUSE_BUTTON_RIGHT)
        {
            pd->game_ui.gun.img->enabled = false;
            pd->game_ui.gun_aim.img->enabled = true;
        }
    }
    else
    {
        pd->game_ui.gun.img->enabled = true;
        pd->game_ui.gun_aim.img->enabled = false;
    }
}

void handle_mouse_click(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
    t_parsed_data *pd;

    pd = param;
    (void)mods; // could be used with shift and alt
    game_mouse_input(button, action, mods, pd);
    if (pd->level.game_started || pd->ui_index == 2)
        return ;
    if (action == MLX_PRESS)
    {
        if (button == MLX_MOUSE_BUTTON_LEFT)
        {
            pd->mouse_clicked = true;
            if (pd->ui_index == 0)
                menu_trigger_click(pd);
            else if (pd->ui_index == 1)
                characters_trigger_click(pd);
        }
    }
    else
    {
        if (button == MLX_MOUSE_BUTTON_LEFT)
            pd->mouse_clicked = false;
    }
}
