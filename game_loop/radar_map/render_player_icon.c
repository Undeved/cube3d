#include "../../cube.h"

void    render_player_icon(t_parsed_data *pd)
{
    t_pos   pixel;
    t_pos   diff;
    t_pos   center;
    int     radious;

    center.x = MINI_MAP_SIZE / 2;
    center.y = MINI_MAP_SIZE  / 2;
    radious = 5;
    pixel.y = 0;
    while (pixel.y < MINI_MAP_SIZE )
    {
        pixel.x = 0;
        while (pixel.x < MINI_MAP_SIZE )
        {
            diff.x = pixel.x - center.x;
            diff.y = pixel.y - center.y;
            if (sqr(diff.x) + sqr(diff.y) <= sqr(radious))
                mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y, PLAYER_ICON);
            pixel.x++;
        }
        pixel.y++;
    }
}
