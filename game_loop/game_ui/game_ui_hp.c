# include "../../cube.h"

static int smooth_step(int current, int target, int step)
{
    if (current < target)
    {
        if (current + step > target)
            return target;
        else
            return current + step;
    }
    else if (current > target)
    {
        if (current - step < target)
            return target;
        else
            return current - step;
    }
    return current;
}

static uint32_t calculate_health_color(int displayed_health)
{
    uint8_t r;
    uint8_t g;

    r = (uint8_t)(255 * (1.0f - displayed_health / 100.0f));
    g = (uint8_t)(255 * (displayed_health / 100.0f));
    return (0xFF << 24) | (r) | (g << 8) | (0 << 16);
}

static int calculate_health_width(int displayed_health, int full_width)
{
    return ((displayed_health * full_width) / 100);
}

static void update_health_pixels(t_parsed_data *pd, int health_width, uint32_t color)
{
    t_pos pxl;
    uint32_t    *pixel;
    int         full_width;
    int         height;

    full_width = pd->game_ui.health.img->width;
    height = pd->game_ui.health.img->height;
    pxl.y = 0;
    while (pxl.y < height)
    {
        pxl.x = 0;
        while (pxl.x < full_width)
        {
            pixel = (uint32_t *)(pd->game_ui.health.img->pixels
                    + (pxl.y * full_width + pxl.x) * sizeof(uint32_t));
            if (pxl.x < health_width)
                *pixel = color;
            else
                *pixel = 0x00000000;
            pxl.x++;
        }
        pxl.y++;
    }
}

void update_health_ui(t_parsed_data *pd)
{
    static int displayed_health = 100;
    int health_width;
    uint32_t color;

    if (!pd->game_ui.health.img || !pd->game_ui.health.img->enabled)
        return;

    displayed_health = smooth_step(displayed_health, pd->player.health, 5);

    health_width = calculate_health_width(displayed_health, pd->game_ui.health.img->width);
    color = calculate_health_color(displayed_health);
    update_health_pixels(pd, health_width, color);
}
