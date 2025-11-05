#include "../../cube.h"

static void load_gun_idle_png_failure(t_parsed_data *pd, char *path)
{
    pd->game_ui.gun.txtr = mlx_load_png(path);
    if (!pd->game_ui.gun.txtr)
        ui_error();
    pd->game_ui.gun.img = mlx_texture_to_image(pd->mlx, pd->game_ui.gun.txtr);
    if (!pd->game_ui.gun.img || mlx_image_to_window(pd->mlx, pd->game_ui.gun.img, GUN_X, GUN_Y) != 0)
        ui_error();
}

static void load_gun_aim_png_failure(t_parsed_data *pd , char *path)
{
    pd->game_ui.gun_aim.txtr = mlx_load_png(path);
    if (!pd->game_ui.gun_aim.txtr)
        ui_error();
    pd->game_ui.gun_aim.img = mlx_texture_to_image(pd->mlx, pd->game_ui.gun_aim.txtr);
    if (!pd->game_ui.gun_aim.img || mlx_image_to_window(pd->mlx, pd->game_ui.gun_aim.img, GUN_AIM_X, GUN_AIM_Y) != 0)
        ui_error();
    pd->game_ui.gun_aim.img->enabled = false;
    pd->player.gun.aiming = false;
}

static void load_gun_no_ammo_png_failure(t_parsed_data *pd , char *path)
{
    pd->game_ui.no_ammo.txtr = mlx_load_png(path);
    if (!pd->game_ui.no_ammo.txtr)
        ui_error();
    pd->game_ui.no_ammo.img = mlx_texture_to_image(pd->mlx, pd->game_ui.no_ammo.txtr);
    if (!pd->game_ui.no_ammo.img || mlx_image_to_window(pd->mlx, pd->game_ui.no_ammo.img, GUN_X, GUN_Y) != 0)
        ui_error();
    pd->game_ui.no_ammo.img->enabled = false;
}

static void load_gun_ui_textures(t_parsed_data *pd)
{
    if (pd->chars_menu.select_index == JESSE)
    {
        load_gun_idle_png_failure(pd, GUN_JESSE_IDLE);
        load_gun_aim_png_failure(pd, GUN_JESSE_AIM);
        load_gun_no_ammo_png_failure(pd, GUN_JESSE_NOAMMO);
        pd->player.gun.type = JESSE_SLINGER;
        load_gun_shoot_anim(pd, JESSE);
        load_gun_reload_anim(pd, JESSE);
    }
    else if (pd->chars_menu.select_index == CHORUS)
    {
        load_gun_aim_png_failure(pd, GUN_CHORUS_AIM);
        load_gun_idle_png_failure(pd, GUN_CHORUS_IDLE);
        pd->player.gun.type = CHORUS_MP42;
        load_gun_shoot_anim(pd, CHORUS);
        load_gun_reload_anim(pd, CHORUS);
    }
    else if (pd->chars_menu.select_index == OUSSMAC)
    {
        load_gun_aim_png_failure(pd, GUN_OUSSMAC_AIM);
        load_gun_idle_png_failure(pd, GUN_OUSSMAC_IDLE);
        pd->player.gun.type = OUSSMAC_37MM;
        load_gun_shoot_anim(pd, OUSSMAC);
        load_gun_reload_anim(pd, OUSSMAC);
    }
}

void setup_character(t_parsed_data *pd)
{
    if (pd->chars_menu.select_index == JESSE)
    {
        pd->player.character = JESSE;
        pd->player.gun.type = JESSE_SLINGER;
    }
    else if (pd->chars_menu.select_index == CHORUS)
    {
        pd->player.character = CHORUS;
        pd->player.gun.type = CHORUS_MP42;
    }
    else if (pd->chars_menu.select_index == OUSSMAC)
    {
        pd->player.character = OUSSMAC;
        pd->player.gun.type = OUSSMAC_37MM;
    }
    // load gun ui textures based on gun type
    load_gun_ui_textures(pd);
    set_gun_stats(pd);
    delete_gun_textures(pd);
}
 