#include "../../../cube.h"

static bool within_bounds(t_pos m_pos, t_pos img_pos, int width, int height)
{
    (void)width;
    (void)height;
    if (m_pos.x > img_pos.x && m_pos.y > img_pos.y)
        return (true);
    return (false);
}

static void main_menu_button(double xpos, double ypos, t_parsed_data *pd)
{
    if (within_bounds((t_pos){xpos, ypos},
        (t_pos){pd->menu.b_start.img->instances->x,
        pd->menu.b_start.img->instances->y}, pd->menu.b_start.img->width,
        pd->menu.b_start.img->height))
    {
        pd->menu.b_start.hoverd = true;
    }
}

static void button_events(double xpos, double ypos, t_parsed_data *pd)
{
    if (pd->ui_index == 0)
        main_menu_button(xpos, ypos, pd);
    // else if (pd->ui_index == 1)

}

void    handle_mouse_input(double xpos, double ypos, void *param)
{
    t_parsed_data   *pd;

    pd = param;
    button_events(xpos, ypos, pd);
}



