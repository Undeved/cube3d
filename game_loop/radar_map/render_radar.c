#include "../../cube.h"

// rotate a point by angle (in radians)
static void rotate_point(double *x, double *y, double angle)
{
    double old_x = *x;
    double old_y = *y;
    *x = old_x * cos(angle) - old_y * sin(angle);
    *y = old_x * sin(angle) + old_y * cos(angle);
}

// draw enemies pixels if within range of x and y
static bool enemy_icon(double x, double y, t_parsed_data *pd)
{
    int i;
    double ex;
    double ey;

    i = 0;
    while (i < pd->enemy_count)
    {
        if (pd->enemies[i].dead)
        {
            i++;
            continue;
        }
        ex = pd->enemies[i].b_pos.x;
        ey = pd->enemies[i].b_pos.y;
        if (fabs(ex - x) < 0.5 && fabs(ey - y) < 0.5)
            return (true);
        i++;
    }
    return (false);
}

static void draw_minimap_grid(t_parsed_data *pd)
{
    t_pos center;
    int radius;
    t_pos pixel;
    t_pos diff;
    t_bpos  w;
    t_pos   map;
    char    cell;
    int     pixel_dist; // for shading.

    center.x = MINI_MAP_SIZE / 2;
    center.y = MINI_MAP_SIZE / 2;
    radius = MINI_MAP_SIZE / 2 - RADIOUS_MARGIN;

    // devided to pi / 2 to rotate cuz it wasnt rotated correctly.
    double angle = atan2(-pd->player.bdir.y, pd->player.bdir.x) - (PI / 2);
    // angle of player direction (so minimap rotates with player)

    pixel.y = 0;
    while (pixel.y < MINI_MAP_SIZE)
    {
        pixel.x = 0;
        while (pixel.x < MINI_MAP_SIZE)
        {
            diff.x = pixel.x - center.x;
            diff.y = pixel.y - center.y;
            pixel_dist = sqrt(sqr(diff.x) + sqr(diff.y));
            // only draw inside the minimap circle
            if (sqr(diff.x) + sqr(diff.y) <= sqr(radius - BORDER_WIDTH))
            {
                // scale pixel distance into "world units"
                double scale = 0.1; // tuning factor: how many pixels per tile
                w.x = diff.x * scale;
                w.y = diff.y * scale;

                // rotate relative to player dir
                rotate_point(&w.x, &w.y, -angle);

                // translate relative to player world position
                map.x = (int)(pd->player.bpos.x + w.x);
                map.y = (int)(pd->player.bpos.y + w.y);

                if (map.x >= 0 && map.x < pd->level.max_x &&
                    map.y >= 0 && map.y < pd->level.max_y)
                {
                    cell = pd->map_grid[map.y][map.x];
                    if (cell == '1' || cell == ' ')
                        mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y, shade_color(WALL_ICON, pixel_dist, 0.015));
                    else if (cell == '0')
                        mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y, shade_color(FLOOR_ICON, pixel_dist, 0.015));
                    if (enemy_icon(pd->player.bpos.x + w.x, pd->player.bpos.y + w.y, pd))
                        mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y, shade_color(0xFF0000FF, pixel_dist, 0.015));
                }
                else
                    mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y, shade_color(WALL_ICON, pixel_dist, 0.015));
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
