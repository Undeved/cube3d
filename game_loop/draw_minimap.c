#include "../cube.h"

void    put_pixel_block(mlx_image_t *screen, int start_x, int start_y, uint32_t color)
{
    int x;
    int y;

    y = 0;
    while (y < PIXEL_BLOCK)
    {
        x = 0;
        while (x < PIXEL_BLOCK)
        {
            if (x == 0 || y == 0 || x + 1 == PIXEL_BLOCK || y + 1 == PIXEL_BLOCK)
                mlx_put_pixel(screen, start_x + x, start_y + y, 0x000000FF);
            else
                mlx_put_pixel(screen, start_x + x, start_y + y, color);
            x++;
        }
        y++;
    }
}

void    put_circle_block(mlx_image_t *screen, double start_x, double start_y, uint32_t color)
{
    double  x;
    double  y;
    double  center_x;
    double  center_y;
    double  radious;
    double  dx;
    double  dy;

    center_x = PIXEL_BLOCK / 2;
    center_y = PIXEL_BLOCK / 2;
    y = 0;
    radious = PIXEL_BLOCK / 4;
    while (y < PIXEL_BLOCK)
    {
        x = 0;
        while (x < PIXEL_BLOCK)
        {
            dx = x - center_x;
            dy = y - center_y;
            if ((dx * dx + dy * dy) <= radious * radious)
                mlx_put_pixel(screen, start_x + x, start_y + y, color);
            x++;
        }
        y++;
    }
}

static bool is_player(char p)
{
    if (p == 'N' || p == 'S' 
        || p == 'E' || p == 'W' 
        || p == 'P')
        return (true);
    return (false);
}

static void draw_mini_player(t_parsed_data *pd)
{
    // int step;
    put_circle_block(pd->screen, pd->minimap.pos.x + pd->player.bpos.x * PIXEL_BLOCK, pd->minimap.pos.y + pd->player.bpos.y * PIXEL_BLOCK, MM_PLAYER_COLOR);
    // step = 0;
    // while (step <= 2)
    // {
    //     pd->player.bpos.x = pd->player.bpos.x + pd->player.bdir.x;
    //     pd->player.bpos.y = pd->player.bpos.y + pd->player.bdir.y;
    //     step++;
    // }
}

void draw_minimap(t_parsed_data *pd)
{
    int x;
    int y;

    pd->minimap.pos.x = MINI_MAP_X;
    pd->minimap.pos.y = MINI_MAP_Y;
    y = 0;
    while(pd->map_grid[y])
    {
        x = 0;
        while (pd->map_grid[y][x])
        {
            if (pd->map_grid[y][x] == '1')
                put_pixel_block(pd->screen, pd->minimap.pos.x + x * PIXEL_BLOCK, pd->minimap.pos.y + y * PIXEL_BLOCK, MM_WALL_COLOR);
            else if (pd->map_grid[y][x] == '0' || is_player(pd->map_grid[y][x]))
                put_pixel_block(pd->screen, pd->minimap.pos.x + x * PIXEL_BLOCK, pd->minimap.pos.y + y * PIXEL_BLOCK, MM_FLOOR_COLOR);
            draw_mini_player(pd);
            x++;
        }
        y++;
    }
}
