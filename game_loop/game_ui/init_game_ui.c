#include "../../cube.h"

static void init_gun(t_parsed_data *pd)
{
    pd->game_ui.gun.txtr = mlx_load_png(GUN_IDLE);
    if (!pd->game_ui.gun.txtr)
        ui_error();
    pd->game_ui.gun.img = mlx_texture_to_image(pd->mlx, pd->game_ui.gun.txtr);
    if(!pd->game_ui.gun.img|| mlx_image_to_window(pd->mlx, pd->game_ui.gun.img, GUN_X, GUN_Y) == -1)
        mind_free_all(EXIT_FAILURE);
    pd->game_ui.gun_aim.txtr = mlx_load_png(GUN_AIM);
    if (!pd->game_ui.gun_aim.txtr)
        ui_error();
    pd->game_ui.gun_aim.img = mlx_texture_to_image(pd->mlx, pd->game_ui.gun_aim.txtr);
    if(!pd->game_ui.gun_aim.img|| mlx_image_to_window(pd->mlx, pd->game_ui.gun_aim.img, GUN_AIM_X, GUN_AIM_Y) == -1)
        mind_free_all(EXIT_FAILURE);
    pd->game_ui.gun_aim.img->enabled = false;
    pd->game_ui.gun.img->enabled = false;

}

static void delete_textures_gun_shoot_anim(t_parsed_data *pd)
{
    int i;

    i = 0;
    while (i < pd->player.gun.shoot.frame_count)
    {
        if (pd->player.gun.shoot.frames[i].txtr)
        {
            mlx_delete_texture(pd->player.gun.shoot.frames[i].txtr);
            pd->player.gun.shoot.frames[i].txtr = NULL;
        }
        i++;
    }
}

// init gun shoot animation and disable them until used 
// in pd->player.gun.shoot.frames array
void init_gun_shoot_anim(t_parsed_data *pd)
{
	int i;

	pd->player.gun.aiming = false;
	pd->player.gun.shoot.active = false;
	pd->player.gun.shoot.current = 0;
	pd->player.gun.shoot.frame_count = GUN_SHOOT_FRMS;
	pd->player.gun.shoot.frames = allocate_gc(malloc(sizeof(t_raw_img) * pd->player.gun.shoot.frame_count));
	if (!pd->player.gun.shoot.frames)
		mind_free_all(EXIT_FAILURE);
	pd->player.gun.shoot.frames[0].txtr = mlx_load_png(GUN_SHOOT_1);
	pd->player.gun.shoot.frames[1].txtr = mlx_load_png(GUN_SHOOT_2);
	pd->player.gun.shoot.frames[2].txtr = mlx_load_png(GUN_SHOOT_3);
	pd->player.gun.shoot.frames[3].txtr = mlx_load_png(GUN_SHOOT_4);
	i = 0;
	while (i < pd->player.gun.shoot.frame_count)
	{
		if (!pd->player.gun.shoot.frames[i].txtr)
			ui_error();
		pd->player.gun.shoot.frames[i].img = mlx_texture_to_image(pd->mlx, pd->player.gun.shoot.frames[i].txtr);
		if (!pd->player.gun.shoot.frames[i].img ||
			mlx_image_to_window(pd->mlx, pd->player.gun.shoot.frames[i].img, GUN_AIM_X, GUN_AIM_Y) == -1)
			mind_free_all(EXIT_FAILURE);
		pd->player.gun.shoot.frames[i].img->enabled = false;
		i++;
	}
	delete_textures_gun_shoot_anim(pd);
}

static void delete_textures_gun_reload_anim(t_parsed_data *pd)
{
    int i;

    i = 0;
    while (i < pd->player.gun.reload.frame_count)
    {
        if (pd->player.gun.reload.frames[i].txtr)
        {
            mlx_delete_texture(pd->player.gun.reload.frames[i].txtr);
            pd->player.gun.reload.frames[i].txtr = NULL;
        }
        i++;
    }
}

static void init_gun_reload_anim(t_parsed_data *pd)
{
    int i;

    pd->player.gun.reload.active = false;
    pd->player.gun.reload.current = 0;
    pd->player.gun.reload.frame_count = GUN_RELOAD_FRMS;
    pd->player.gun.reload.frames = allocate_gc(malloc(sizeof(t_raw_img) * pd->player.gun.reload.frame_count));
    if (!pd->player.gun.reload.frames)
        mind_free_all(EXIT_FAILURE);
    pd->player.gun.reload.frames[0].txtr = mlx_load_png(GUN_RELOAD_1);
    pd->player.gun.reload.frames[1].txtr = mlx_load_png(GUN_RELOAD_2);
    pd->player.gun.reload.frames[2].txtr = mlx_load_png(GUN_RELOAD_3);
    pd->player.gun.reload.frames[3].txtr = mlx_load_png(GUN_RELOAD_4);
    pd->player.gun.reload.frames[4].txtr = mlx_load_png(GUN_RELOAD_5);
    pd->player.gun.reload.frames[5].txtr = mlx_load_png(GUN_RELOAD_6);
    i = 0;
    while (i < pd->player.gun.reload.frame_count)
    {
        if (!pd->player.gun.reload.frames[i].txtr)
            ui_error();
        pd->player.gun.reload.frames[i].img = mlx_texture_to_image(pd->mlx, pd->player.gun.reload.frames[i].txtr);
        if (!pd->player.gun.reload.frames[i].img ||
            mlx_image_to_window(pd->mlx, pd->player.gun.reload.frames[i].img, GUN_X, GUN_Y) == -1)
            mind_free_all(EXIT_FAILURE);
        pd->player.gun.reload.frames[i].img->enabled = false;
        i++;
    }
    delete_textures_gun_reload_anim(pd);
}



void    init_game_ui(t_parsed_data *pd)
{
    init_gun(pd);
    init_gun_shoot_anim(pd);
    init_gun_reload_anim(pd);
    pd->game_ui.vignette.txtr = mlx_load_png(VIGNETTE);
    if (!pd->game_ui.vignette.txtr)
        ui_error();
    pd->game_ui.vignette.img = mlx_texture_to_image(pd->mlx, pd->game_ui.vignette.txtr);
    if(!pd->game_ui.vignette.img|| mlx_image_to_window(pd->mlx, pd->game_ui.vignette.img, 0, 0) == -1)
        mind_free_all(EXIT_FAILURE);
}
