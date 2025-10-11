#include "../../cube.h"

static void load_health_background(t_parsed_data *pd)
{
    if (pd->player.character == JESSE)
    {
        pd->game_ui.health_bg.txtr = mlx_load_png(HP_JESSE);
        if (!pd->game_ui.health_bg.txtr)
            ui_error();
        pd->game_ui.health_bg.img = mlx_texture_to_image(pd->mlx, pd->game_ui.health_bg.txtr);
        if (!pd->game_ui.health_bg.img || mlx_image_to_window(pd->mlx, pd->game_ui.health_bg.img, HBAR_BG_X, HBAR_BG_Y) == -1)
            mind_free_all(EXIT_FAILURE);
    }
    else if (pd->player.character == CHORUS)
    {
        pd->game_ui.health_bg.txtr = mlx_load_png(HP_CHORUS);
        if (!pd->game_ui.health_bg.txtr)
            ui_error();
        pd->game_ui.health_bg.img = mlx_texture_to_image(pd->mlx, pd->game_ui.health_bg.txtr);
        if (!pd->game_ui.health_bg.img || mlx_image_to_window(pd->mlx, pd->game_ui.health_bg.img, HBAR_BG_X, HBAR_BG_Y) == -1)
            mind_free_all(EXIT_FAILURE);
    }
    else if (pd->player.character == OUSSMAC)
    {
        pd->game_ui.health_bg.txtr = mlx_load_png(HP_OUSSMAC);
        if (!pd->game_ui.health_bg.txtr)
            ui_error();
        pd->game_ui.health_bg.img = mlx_texture_to_image(pd->mlx, pd->game_ui.health_bg.txtr);
        if (!pd->game_ui.health_bg.img || mlx_image_to_window(pd->mlx, pd->game_ui.health_bg.img, HBAR_BG_X, HBAR_BG_Y) == -1)
            mind_free_all(EXIT_FAILURE);
    }
}

static void delete_health_textures(t_parsed_data *pd)
{
    if (pd->game_ui.health.txtr)
    {
        mlx_delete_texture(pd->game_ui.health.txtr);
        pd->game_ui.health.txtr = NULL;
    }
    if (pd->game_ui.health_bg.txtr)
    {
        mlx_delete_texture(pd->game_ui.health_bg.txtr);
        pd->game_ui.health_bg.txtr = NULL;
    }
}

// new health ui setup function
void setup_health_ui(t_parsed_data *pd)
{
    load_health_background(pd);
    pd->game_ui.health.txtr = mlx_load_png(HEALTH_BAR);
    if (!pd->game_ui.health.txtr)
        ui_error();
    pd->game_ui.health.img = mlx_texture_to_image(pd->mlx, pd->game_ui.health.txtr);
    if (!pd->game_ui.health.img || mlx_image_to_window(pd->mlx, pd->game_ui.health.img, HBAR_X, HBAR_Y) == -1)
        mind_free_all(EXIT_FAILURE);
    // load background based on character
    delete_health_textures(pd);
}
