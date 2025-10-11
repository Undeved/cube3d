#include "../../cube.h"

// have to understand the logic of smooth step and how to apply it here
// function to smoothly update health bar width
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


typedef struct s_tint_color
{
    mlx_image_t	*img;
    uint32_t	*pixels;
    int			total;
    float		health;
    uint8_t		r;
    uint8_t		g;
    uint8_t		b;
    uint8_t		a;
    uint32_t	color;
    int			i;
}	t_tc;

void	tint_color(t_parsed_data *pd)
{
    t_tc	tc;

    tc.img = pd->game_ui.health.img;
    if (!tc.img || !tc.img->enabled)
        return ;
    tc.health = pd->player.health;
    if (tc.health < 0)
        tc.health = 0;
    if (tc.health > 100)
        tc.health = 100;
    tc.r = (uint8_t)(255 * (1.0f - tc.health / 100.0f));
    tc.g = (uint8_t)(255 * (tc.health / 100.0f));
    tc.b = 0;
    tc.color = (tc.b << 16) | (tc.g << 8) | tc.r;
    tc.total = tc.img->width * tc.img->height;
    tc.pixels = (uint32_t *)tc.img->pixels;
    tc.i = 0;
    while (tc.i < tc.total)
    {
        tc.a = (tc.pixels[tc.i] >> 24) & 0xFF;
        if (tc.a != 0)
            tc.pixels[tc.i] = (tc.a << 24) | tc.color;
        tc.i++;
    }
}




// function to update health bar ui based on player health
void	update_health_ui(t_parsed_data *pd)
{
    static int displayed_health = 100;
    int			health_width;
    int			full_width;
    int			height;
    int			x;
    int			y;
    uint32_t	*pixel;

    if (!pd->game_ui.health.img || !pd->game_ui.health.img->enabled)
        return ;
    displayed_health = smooth_step(displayed_health, pd->player.health, 20);
    full_width = pd->game_ui.health.img->width;
    height = pd->game_ui.health.img->height;
    health_width = (displayed_health * full_width) / 100;
    y = 0;
    tint_color(pd);
    while (y < height)
    {
        x = 0;
        while (x < full_width)
        {
            pixel = (uint32_t *)(pd->game_ui.health.img->pixels
                    + (y * full_width + x) * sizeof(uint32_t));
            if (x >= health_width)
            {
                *pixel = 0x00000000;
            }
            x++;
        }
        y++;
    }
}

void    toggle_game_ui(t_parsed_data *pd)
{
    // enable mini map
    pd->minimap.img->enabled = true;
    // setup character and gun equiped
    puts("choosing player...");
    setup_character(pd);
    setup_health_ui(pd);
    init_game_ui(pd);
    pd->game_ui.gun.img->enabled = true;
}
