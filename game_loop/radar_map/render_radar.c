#include "../../cube.h"

// rotate a point by angle (in radians)
static void rotate_point(double *x, double *y, double angle)
{
    double old_x = *x;
    double old_y = *y;
    *x = old_x * cos(angle) - old_y * sin(angle);
    *y = old_x * sin(angle) + old_y * cos(angle);
}


static void draw_minimap_grid(t_parsed_data *pd)
{
    t_pos center;
    int radius;
    t_pos pixel;
    t_pos diff;

    center.x = MINI_MAP_SIZE / 2;
    center.y = MINI_MAP_SIZE / 2;
    radius = MINI_MAP_SIZE / 2 - RADIOUS_MARGIN;

    double angle = atan2(pd->player.bdir.y, pd->player.bdir.x);
    // angle of player direction (so minimap rotates with player)

    pixel.y = 0;
    while (pixel.y < MINI_MAP_SIZE)
    {
        pixel.x = 0;
        while (pixel.x < MINI_MAP_SIZE)
        {
            diff.x = pixel.x - center.x;
            diff.y = pixel.y - center.y;

            // only draw inside the minimap circle
            if (sqr(diff.x) + sqr(diff.y) <= sqr(radius - BORDER_WIDTH))
            {
                // scale pixel distance into "world units"
                double scale = 0.1; // tuning factor: how many pixels per tile
                double wx = diff.x * scale;
                double wy = diff.y * scale;

                // rotate relative to player dir
                rotate_point(&wx, &wy, -angle);

                // translate relative to player world position
                int map_x = (int)(pd->player.bpos.x + wx);
                int map_y = (int)(pd->player.bpos.y + wy);

                if (map_x >= 0 && map_x < pd->level.max_x &&
                    map_y >= 0 && map_y < pd->level.max_y)
                {
                    char cell = pd->map_grid[map_y][map_x];
                    if (cell == '1')
                        mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y, 0x444444FF); // wall
                    else
                        mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y, 0xAAAAAAFF); // floor
                }
                else
                    mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y, 0x444444FF);
            }
            pixel.x++;
        }
        pixel.y++;
    }
}


void    render_radar(t_parsed_data *pd)
{
    (void)pd;
    draw_minimap_grid(pd);
    render_player_icon(pd);
}
