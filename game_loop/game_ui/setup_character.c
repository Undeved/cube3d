#include "../../cube.h"

static void load_gun_shoot_frame(t_parsed_data *pd, int i, char *path)
{
    pd->player.gun.shoot.frames[i].txtr = mlx_load_png(path);
    if (!pd->player.gun.shoot.frames[i].txtr)
        ui_error();
    pd->player.gun.shoot.frames[i].img = mlx_texture_to_image(pd->mlx, pd->player.gun.shoot.frames[i].txtr);
    if (!pd->player.gun.shoot.frames[i].img || mlx_image_to_window(pd->mlx, pd->player.gun.shoot.frames[i].img, GUN_AIM_X, GUN_AIM_Y) != 0)
        ui_error();
    pd->player.gun.shoot.frames[i].img->enabled = false;
}

static void load_gun_reload_frame(t_parsed_data *pd, int i, char *path)
{
    pd->player.gun.reload.frames[i].txtr = mlx_load_png(path);
    if (!pd->player.gun.reload.frames[i].txtr)
        ui_error();
    pd->player.gun.reload.frames[i].img = mlx_texture_to_image(pd->mlx, pd->player.gun.reload.frames[i].txtr);
    if (!pd->player.gun.reload.frames[i].img || mlx_image_to_window(pd->mlx, pd->player.gun.reload.frames[i].img, GUN_X, GUN_Y) != 0)
        ui_error();
    pd->player.gun.reload.frames[i].img->enabled = false;
}



// load gun shoot anim based on gun type in a while loop using macro  GUN_SHOOT_FRMS to load pngs
static void load_gun_shoot_anim(t_parsed_data *pd, t_character character)
{
    int i;

    pd->player.gun.shoot.frames = allocate_gc(malloc(sizeof(t_raw_img) * GUN_SHOOT_FRMS));
    if (!pd->player.gun.shoot.frames)
        ui_error();
    pd->player.gun.shoot.frame_count = GUN_SHOOT_FRMS;
    pd->player.gun.shoot.current = 0;
    pd->player.gun.shoot.active = false;
    pd->player.gun.shoot.last_frame_time = 0;
    pd->player.gun.shoot.frame_delay = 50; // 50 ms per frame
    i = 0;
    while (i < GUN_SHOOT_FRMS)
    {
        // for each frame load texture based on character helper function to load the 4 frames
        if (character == JESSE)
        {
            if (i == 0)
                load_gun_shoot_frame(pd, i, GUN_JESSE_SHOOT_1);
            else if (i == 1)
                load_gun_shoot_frame(pd, i, GUN_JESSE_SHOOT_2);
            else if (i == 2)
                load_gun_shoot_frame(pd, i, GUN_JESSE_SHOOT_3);
            else if (i == 3)
                load_gun_shoot_frame(pd, i, GUN_JESSE_SHOOT_4);
        }
        else if (character == CHORUS)
        {
            if (i == 0)
                load_gun_shoot_frame(pd, i, GUN_CHORUS_SHOOT_1);
            else if (i == 1)
                load_gun_shoot_frame(pd, i, GUN_CHORUS_SHOOT_2);
            else if (i == 2)
                load_gun_shoot_frame(pd, i, GUN_CHORUS_SHOOT_3);
            else if (i == 3)
                load_gun_shoot_frame(pd, i, GUN_CHORUS_SHOOT_4);
        }
        else if (character == OUSSMAC)
        {
            if (i == 0)
                load_gun_shoot_frame(pd, i, GUN_OUSSMAC_SHOOT_1);
            else if (i == 1)
                load_gun_shoot_frame(pd, i, GUN_OUSSMAC_SHOOT_2);
            else if (i == 2)
                load_gun_shoot_frame(pd, i, GUN_OUSSMAC_SHOOT_3);
            else if (i == 3)
                load_gun_shoot_frame(pd, i, GUN_OUSSMAC_SHOOT_4);
        }
        i++;
    }
}

// reload anim
static void load_gun_reload_anim(t_parsed_data *pd, t_character character)
{
    int i;

    pd->player.gun.reload.frames = allocate_gc(malloc(sizeof(t_raw_img) * GUN_RELOAD_FRMS));
    if (!pd->player.gun.reload.frames)
        ui_error();
    pd->player.gun.reload.frame_count = GUN_RELOAD_FRMS;
    pd->player.gun.reload.current = 0;
    pd->player.gun.reload.active = false;
    pd->player.gun.reload.last_frame_time = 0;
    pd->player.gun.reload.frame_delay = 100; // 100 ms per frame
    i = 0;
    while (i < GUN_RELOAD_FRMS)
    {
        // for each frame load texture based on character helper function to load the 6 frames
        if (character == JESSE)
        {
            if (i == 0)
                load_gun_reload_frame(pd, i, GUN_JESSE_RELOAD_1);
            else if (i == 1)
                load_gun_reload_frame(pd, i, GUN_JESSE_RELOAD_2);
            else if (i == 2)
                load_gun_reload_frame(pd, i, GUN_JESSE_RELOAD_3);
            else if (i == 3)
                load_gun_reload_frame(pd, i, GUN_JESSE_RELOAD_4);
            else if (i == 4)
                load_gun_reload_frame(pd, i, GUN_JESSE_RELOAD_5);
            else if (i == 5)
                load_gun_reload_frame(pd, i, GUN_JESSE_RELOAD_6);
        }
        else if (character == CHORUS)
        {
            if (i == 0)
                load_gun_reload_frame(pd, i, GUN_CHORUS_RELOAD_1);
            else if (i == 1)
                load_gun_reload_frame(pd, i, GUN_CHORUS_RELOAD_2);
            else if (i == 2)
                load_gun_reload_frame(pd, i, GUN_CHORUS_RELOAD_3);
            else if (i == 3)
                load_gun_reload_frame(pd, i, GUN_CHORUS_RELOAD_4);
            else if (i == 4)
                load_gun_reload_frame(pd, i, GUN_CHORUS_RELOAD_5);
            else if (i == 5)
                load_gun_reload_frame(pd, i, GUN_CHORUS_RELOAD_6);
        }
        else if (character == OUSSMAC)
        {
            if (i == 0)
                load_gun_reload_frame(pd, i, GUN_OUSSMAC_RELOAD_1);
            else if (i == 1)
                load_gun_reload_frame(pd, i, GUN_OUSSMAC_RELOAD_2);
            else if (i == 2)
                load_gun_reload_frame(pd, i, GUN_OUSSMAC_RELOAD_3);
            else if (i == 3)
                load_gun_reload_frame(pd, i, GUN_OUSSMAC_RELOAD_4);
            else if (i == 4)
                load_gun_reload_frame(pd, i, GUN_OUSSMAC_RELOAD_5);
            else if (i == 5)
                load_gun_reload_frame(pd, i, GUN_OUSSMAC_RELOAD_6);
        }
        i++;
    }
}

// load idle and aim failure helper function
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

// use macros for gun stats later
static void set_gun_stats(t_parsed_data *pd)
{
    if (pd->player.gun.type == JESSE_SLINGER)
    {
        pd->player.gun.ammo = 30;
        pd->player.gun.damage = 10;
    }
    else if (pd->player.gun.type == CHORUS_MP42)
    {
        pd->player.gun.ammo = 40;
        pd->player.gun.damage = 8;
    }
    else if (pd->player.gun.type == OUSSMAC_37MM)
    {
        pd->player.gun.ammo = 20;
        pd->player.gun.damage = 15;
    }
}

// delete loaded png textures after loading into img using mlx_delete_texture
static void delete_gun_textures(t_parsed_data *pd)
{
    int i;

    // delete idle and aim textures
    if (pd->game_ui.gun.txtr)
        mlx_delete_texture(pd->game_ui.gun.txtr);
    if (pd->game_ui.gun_aim.txtr)
        mlx_delete_texture(pd->game_ui.gun_aim.txtr);
    if (pd->player.gun.shoot.frames)
    {
        i = 0;
        while (i < pd->player.gun.shoot.frame_count)
        {
            if (pd->player.gun.shoot.frames[i].txtr)
                mlx_delete_texture(pd->player.gun.shoot.frames[i].txtr);
            i++;
        }
    }
    if (pd->player.gun.reload.frames)
    {
        i = 0;
        while (i < pd->player.gun.reload.frame_count)
        {
            if (pd->player.gun.reload.frames[i].txtr)
                mlx_delete_texture(pd->player.gun.reload.frames[i].txtr);
            i++;
        }
    }
}

static void load_gun_ui_textures(t_parsed_data *pd)
{
    if (pd->chars_menu.select_index == JESSE)
    {
        load_gun_idle_png_failure(pd, GUN_JESSE_IDLE);
        load_gun_aim_png_failure(pd, GUN_JESSE_AIM);
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
    set_gun_stats(pd);
    delete_gun_textures(pd);
}


static void init_game_ui_to_null(t_parsed_data *pd)
{
    pd->game_ui.gun.txtr = NULL;
    pd->game_ui.gun.img = NULL;
    pd->game_ui.gun_aim.txtr = NULL;
    pd->game_ui.gun_aim.img = NULL;
    pd->game_ui.health.txtr = NULL;
    pd->game_ui.health.img = NULL;
    pd->player.gun.shoot.frames = NULL;
    pd->player.gun.reload.frames = NULL;
}

// setup character and gun equiped
// if select_index is JESSE, set gun type to jesse, and character to jesse
// no loading images will happen later on
void setup_character(t_parsed_data *pd)
{

    init_game_ui_to_null(pd);
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
}
 