#include "../../cube.h"

void delete_screen_and_map(t_parsed_data *pd)
{
    if (pd->screen)
        mlx_delete_image(pd->mlx, pd->screen);
    if (pd->minimap.img)
        mlx_delete_image(pd->mlx, pd->minimap.img);
}

static void delete_main_menu_hovered(t_parsed_data *pd)
{
    if (pd->menu.b_exit.img)
        mlx_delete_image(pd->mlx, pd->menu.b_exit.img);
    if (pd->menu.b_exit.txtr)
        mlx_delete_texture(pd->menu.b_exit.txtr);
    if (pd->menu.b_start_hv.img)
        mlx_delete_image(pd->mlx, pd->menu.b_start_hv.img);
    if (pd->menu.b_start_hv.txtr)
        mlx_delete_texture(pd->menu.b_start_hv.txtr);
    if (pd->menu.b_chars_hv.img)
        mlx_delete_image(pd->mlx, pd->menu.b_chars_hv.img);
    if (pd->menu.b_chars_hv.txtr)
        mlx_delete_texture(pd->menu.b_chars_hv.txtr);
    if (pd->menu.b_exit_hv.img)
        mlx_delete_image(pd->mlx, pd->menu.b_exit_hv.img);
    if (pd->menu.b_exit_hv.txtr)
        mlx_delete_texture(pd->menu.b_exit_hv.txtr);
}

void delete_main_menu_textures(t_parsed_data *pd)
{
    if (pd->menu.bg.img)
        mlx_delete_image(pd->mlx, pd->menu.bg.img);
    if (pd->menu.bg.txtr)
        mlx_delete_texture(pd->menu.bg.txtr);
    if (pd->menu.title.img)
        mlx_delete_image(pd->mlx, pd->menu.title.img);
    if (pd->menu.title.txtr)
        mlx_delete_texture(pd->menu.title.txtr);
    if (pd->menu.b_start.img)
        mlx_delete_image(pd->mlx, pd->menu.b_start.img);
    if (pd->menu.b_start.txtr)
        mlx_delete_texture(pd->menu.b_start.txtr);
    if (pd->menu.b_chars.img)
        mlx_delete_image(pd->mlx, pd->menu.b_chars.img);
    if (pd->menu.b_chars.txtr)
        mlx_delete_texture(pd->menu.b_chars.txtr);
    delete_main_menu_hovered(pd);
}

static void delete_idle_aim_textures(t_parsed_data *pd)
{
    if (pd->player.gun.idle.img)
        mlx_delete_image(pd->mlx, pd->player.gun.idle.img);
    if (pd->player.gun.idle.txtr)
        mlx_delete_texture(pd->player.gun.idle.txtr);
    if (pd->player.gun.aim.img)
        mlx_delete_image(pd->mlx, pd->player.gun.aim.img);
    if (pd->player.gun.aim.txtr)
        mlx_delete_texture(pd->player.gun.aim.txtr);
}

void delete_player_textures(t_parsed_data *pd)
{
    int i;

    delete_idle_aim_textures(pd);
    i = 0;
    while (i < GUN_SHOOT_FRMS && pd->player.gun.shoot.frames)
    {
        if (pd->player.gun.shoot.frames[i].img)
            mlx_delete_image(pd->mlx, pd->player.gun.shoot.frames[i].img);
        if (pd->player.gun.shoot.frames[i].txtr)
            mlx_delete_texture(pd->player.gun.shoot.frames[i].txtr);
        i++;
    }
    i = 0;
    while (i < GUN_RELOAD_FRMS && pd->player.gun.reload.frames)
    {
        if (pd->player.gun.reload.frames[i].img)
            mlx_delete_image(pd->mlx, pd->player.gun.reload.frames[i].img);
        if (pd->player.gun.reload.frames[i].txtr)
            mlx_delete_texture(pd->player.gun.reload.frames[i].txtr);
        i++;
    }
}
