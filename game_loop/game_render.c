#include "../cube.h"

void    game_render(void *param)
{
    t_parsed_data   *pd;
    // int             pixels_y;
    // int             pixels_x;

    pd = param;
    draw_minimap(pd);
    // pixels_y = 0;
    // while (pixels_y < HEIGHT)
    // {
    //     pixels_x = 0;
    //     while (pixels_x < WIDTH)
    //     {
    //         mlx_put_pixel(pd->screen, pixels_x, pixels_y, 0xFFFFFFFF);
    //         pixels_x++;
    //     }
    //     pixels_y++;
    // }
}