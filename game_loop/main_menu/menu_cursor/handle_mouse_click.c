#include "../../../cube.h"

void handle_mouse_click(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
    t_parsed_data *pd;

    pd = param;
    (void)mods; // could be used with shift and alt
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
