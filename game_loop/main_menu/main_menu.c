#include "../../cube.h"

// static void vertical_line(t_parsed_data *pd)
// {
//     int x;
//     int y;

//     y = 0;
//     while (y < HEIGHT)
//     {
//         x = 0;
//         while (x < WIDTH)
//         {
//             if (x == WIDTH / 2)
//                 mlx_put_pixel(pd->menu.bg.img, x , y, 0x000000FF);
//             x++;
//         }
        
//         y++;
//     }
// }

static void render_button_index(t_parsed_data *pd)
{
    pd->menu.b_start.hoverd = false;
    pd->menu.b_chars.hoverd = false;
    pd->menu.b_exit.hoverd = false;
    if (pd->menu.button_index == 0)
        pd->menu.b_start.hoverd = true;
    else if (pd->menu.button_index == 1)
        pd->menu.b_chars.hoverd = true;
    else if (pd->menu.button_index == 2)
        pd->menu.b_exit.hoverd = true;
}

static void update_button_state(t_parsed_data *pd)
{
    render_button_index(pd);
    // toggle hovered based on flag.
    if (pd->menu.b_start.hoverd)
    {
        pd->menu.b_start_hv.img->enabled = true;
        pd->menu.b_start.img->enabled = false;
    }
    else
    {
        pd->menu.b_start.img->enabled = true;
        pd->menu.b_start_hv.img->enabled = false;
    }

    if (pd->menu.b_chars.hoverd)
    {
        pd->menu.b_chars_hv.img->enabled = true;
        pd->menu.b_chars.img->enabled = false;
    }
    else
    {
        pd->menu.b_chars.img->enabled = true;
        pd->menu.b_chars_hv.img->enabled = false;
    }

    if (pd->menu.b_exit.hoverd)
    {
        pd->menu.b_exit_hv.img->enabled = true;
        pd->menu.b_exit.img->enabled = false;
    }
    else
    {
        pd->menu.b_exit.img->enabled = true;
        pd->menu.b_exit_hv.img->enabled = false;
    }
}

void    main_menu(t_parsed_data *pd)
{
    if (pd->level.game_started || pd->ui_index != 0)
        return ;
    // vertical_line(pd);
    update_button_state(pd);
    // logic for menu
}
