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

static void jesse_shoot_frames(t_parsed_data *pd, int i)
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

static void chorus_shoot_frames(t_parsed_data *pd, int i)
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

static void oussmac_shoot_frames(t_parsed_data *pd, int i)
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

void load_gun_shoot_anim(t_parsed_data *pd, t_character character)
{
    int i;

    pd->player.gun.shoot.frames = allocate_gc(malloc(sizeof(t_raw_img) * GUN_SHOOT_FRMS));
    if (!pd->player.gun.shoot.frames)
        ui_error();
    pd->player.gun.shoot.frame_count = GUN_SHOOT_FRMS;
    pd->player.gun.shoot.current = 0;
    pd->player.gun.shoot.active = false;
    pd->player.gun.shoot.last_frame_time = 0;
    pd->player.gun.shoot.frame_delay = 50;
    i = 0;
    while (i < GUN_SHOOT_FRMS)
    {
        if (character == JESSE)
            jesse_shoot_frames(pd, i);
        else if (character == CHORUS)
            chorus_shoot_frames(pd, i);
        else if (character == OUSSMAC)
            oussmac_shoot_frames(pd, i);
        i++;
    }
}
