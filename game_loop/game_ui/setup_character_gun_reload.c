#include "../../cube.h"

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

static void jesse_reload_frames(t_parsed_data *pd, int i)
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

static void chorus_reload_frames(t_parsed_data *pd, int i)
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

static void oussmac_reload_frames(t_parsed_data *pd, int i)
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

// reload anim
void load_gun_reload_anim(t_parsed_data *pd, t_character character)
{
    int i;

    pd->player.gun.reload.frames = allocate_gc(malloc(sizeof(t_raw_img) * GUN_RELOAD_FRMS));
    if (!pd->player.gun.reload.frames)
        ui_error();
    pd->player.gun.reload.frame_count = GUN_RELOAD_FRMS;
    pd->player.gun.reload.current = 0;
    pd->player.gun.reload.active = false;
    pd->player.gun.reload.last_frame_time = 0;
    pd->player.gun.reload.frame_delay = 200;
    i = 0;
    while (i < GUN_RELOAD_FRMS)
    {
        if (character == JESSE)
            jesse_reload_frames(pd, i);
        else if (character == CHORUS)
            chorus_reload_frames(pd, i);
        else if (character == OUSSMAC)
            oussmac_reload_frames(pd, i);
        i++;
    }
}
