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

// function to update health bar ui based on player health
void	update_health_ui(t_parsed_data *pd)
{
    static int displayed_health = 100;
    int			health_width;
    int			full_width;
    int			height;
    int			x, y;
    uint32_t	*pixel;
    uint32_t	color;

    if (!pd->game_ui.health.img || !pd->game_ui.health.img->enabled)
        return ;

    displayed_health = smooth_step(displayed_health, pd->player.health, 5);

    full_width = pd->game_ui.health.img->width;
    height = pd->game_ui.health.img->height;
    health_width = (displayed_health * full_width) / 100;

    // calculate the color gradient based on displayed health
    uint8_t r = (uint8_t)(255 * (1.0f - displayed_health / 100.0f));
    uint8_t g = (uint8_t)(255 * (displayed_health / 100.0f));
    color = (0xFF << 24) | (r) | (g << 8) | (0 << 16); // solid color with alpha

    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < full_width)
        {
            pixel = (uint32_t *)(pd->game_ui.health.img->pixels
                    + (y * full_width + x) * sizeof(uint32_t));

            if (x < health_width)
                *pixel = color;         // paint visible health
            else
                *pixel = 0x00000000;    // clear empty space
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
