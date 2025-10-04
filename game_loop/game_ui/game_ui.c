#include "../../cube.h"

// color textured string
static void color_textured_string(mlx_image_t *img, uint32_t color)
{
    int x, y;
    uint32_t *pixel;
    uint32_t alpha;
    uint32_t new_rgb = color & 0x00FFFFFF; // only RGB

    for (y = 0; y < (int)img->height; y++)
    {
        for (x = 0; x < (int)img->width; x++)
        {
            pixel = (uint32_t *)(img->pixels + (y * img->width + x) * sizeof(uint32_t));

            alpha = *pixel & 0xFF000000; // preserve alpha
            if (alpha != 0)
                *pixel = alpha | new_rgb;
        }
    }
}

// join_string and number and convert them to string using ft_itoa
// no freeing use gc allocate_gc and ft_strjoin
static char *join_convert(char *str, int num)
{
    char *num_str;
    char *joined;

    num_str = allocate_gc(ft_itoa(num));
    joined = allocate_gc(gnl_ft_strjoin(str, num_str));
    return (joined);
}

// health integer value is in pd->player.health
// image to be displayed is in pd->game_ui.health.img
static void enable_health_ui(t_parsed_data *pd)
{
    if (pd->player.health >= 75)
    {
        pd->game_ui.health.img = mlx_put_string(pd->mlx, join_convert("HEALTH: ", pd->player.health), 10, 40);
        color_textured_string(pd->game_ui.health.img, 0xFF00FF00);
    }
    else if (pd->player.health >= 50)
    {
        pd->game_ui.health.img = mlx_put_string(pd->mlx, join_convert("HEALTH: ", pd->player.health), 10, 40);
        color_textured_string(pd->game_ui.health.img, 0xFFFFFF00);
    }
    else if (pd->player.health >= 25)
    {
        pd->game_ui.health.img = mlx_put_string(pd->mlx, join_convert("HEALTH: ", pd->player.health), 10, 40);
        color_textured_string(pd->game_ui.health.img, 0xFFFFA500);
    }
    else
    {
        pd->game_ui.health.img = mlx_put_string(pd->mlx, join_convert("HEALTH: ", pd->player.health), 10, 40);
        color_textured_string(pd->game_ui.health.img, 0xFF0000FF);
    }
    if (!pd->game_ui.health.img)
        mind_free_all(EXIT_FAILURE);
    pd->game_ui.health.img->enabled = true;
}

void update_health_ui(t_parsed_data *pd)
{
    pd->game_ui.health.img->enabled = false;
    if (pd->game_ui.health.img)
        mlx_delete_image(pd->mlx, pd->game_ui.health.img);
    //clear old img
    pd->game_ui.health.img = NULL;
    enable_health_ui(pd);
}

void    toggle_game_ui(t_parsed_data *pd)
{
    // enable mini map
    pd->minimap.img->enabled = true;
    pd->game_ui.gun.img->enabled = true;
    // make this load all ui and have actual structs for playable characters.
    puts("choosing player...");
    if (pd->chars_menu.select_index == JESSE)
        pd->game_ui.character.img = mlx_put_string(pd->mlx, "PlAYER: JESSE", 10, 20);
    else if (pd->chars_menu.select_index == CHORUS)
        pd->game_ui.character.img = mlx_put_string(pd->mlx, "PlAYER: CHORIS", 10, 20);
    else if (pd->chars_menu.select_index == OUSSMAC)
        pd->game_ui.character.img = mlx_put_string(pd->mlx, "PlAYER: OUSSMAC", 10, 20);
    if (!pd->game_ui.character.img)
        mind_free_all(EXIT_FAILURE);
    // load health
    enable_health_ui(pd);
}
