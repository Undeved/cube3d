#include "../../cube.h"

#include "../../cube.h"

static void delete_player_textures(t_parsed_data *pd)
{
    // Delete gun textures
    if (pd->player.gun.idle.img)
        mlx_delete_image(pd->mlx, pd->player.gun.idle.img);
    if (pd->player.gun.idle.txtr)
        mlx_delete_texture(pd->player.gun.idle.txtr);
    
    if (pd->player.gun.aim.img)
        mlx_delete_image(pd->mlx, pd->player.gun.aim.img);
    if (pd->player.gun.aim.txtr)
        mlx_delete_texture(pd->player.gun.aim.txtr);
    
    // Delete shoot frames
    int i = 0;
    while (i < GUN_SHOOT_FRMS && pd->player.gun.shoot.frames)
    {
        if (pd->player.gun.shoot.frames[i].img)
            mlx_delete_image(pd->mlx, pd->player.gun.shoot.frames[i].img);
        if (pd->player.gun.shoot.frames[i].txtr)
            mlx_delete_texture(pd->player.gun.shoot.frames[i].txtr);
        i++;
    }
    
    // Delete reload frames
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

static void delete_screen_and_map(t_parsed_data *pd)
{
    if (pd->screen)
        mlx_delete_image(pd->mlx, pd->screen);
    if (pd->minimap.img)
        mlx_delete_image(pd->mlx, pd->minimap.img);
}

static void delete_main_menu_textures(t_parsed_data *pd)
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

static void delete_characters_ui_textures(t_parsed_data *pd)
{
    if (pd->chars_menu.bg.img)
        mlx_delete_image(pd->mlx, pd->chars_menu.bg.img);
    if (pd->chars_menu.bg.txtr)
        mlx_delete_texture(pd->chars_menu.bg.txtr);
    
    if (pd->chars_menu.selected.img)
        mlx_delete_image(pd->mlx, pd->chars_menu.selected.img);
    if (pd->chars_menu.selected.txtr)
        mlx_delete_texture(pd->chars_menu.selected.txtr);
    
    if (pd->chars_menu.b_jesse.img)
        mlx_delete_image(pd->mlx, pd->chars_menu.b_jesse.img);
    if (pd->chars_menu.b_jesse.txtr)
        mlx_delete_texture(pd->chars_menu.b_jesse.txtr);
    
    if (pd->chars_menu.b_chorus.img)
        mlx_delete_image(pd->mlx, pd->chars_menu.b_chorus.img);
    if (pd->chars_menu.b_chorus.txtr)
        mlx_delete_texture(pd->chars_menu.b_chorus.txtr);
    
    if (pd->chars_menu.b_oussmac.img)
        mlx_delete_image(pd->mlx, pd->chars_menu.b_oussmac.img);
    if (pd->chars_menu.b_oussmac.txtr)
        mlx_delete_texture(pd->chars_menu.b_oussmac.txtr);
    
    if (pd->chars_menu.b_jesse_hv.img)
        mlx_delete_image(pd->mlx, pd->chars_menu.b_jesse_hv.img);
    if (pd->chars_menu.b_jesse_hv.txtr)
        mlx_delete_texture(pd->chars_menu.b_jesse_hv.txtr);
    
    if (pd->chars_menu.b_chorus_hv.img)
        mlx_delete_image(pd->mlx, pd->chars_menu.b_chorus_hv.img);
    if (pd->chars_menu.b_chorus_hv.txtr)
        mlx_delete_texture(pd->chars_menu.b_chorus_hv.txtr);
    
    if (pd->chars_menu.b_oussmac_hv.img)
        mlx_delete_image(pd->mlx, pd->chars_menu.b_oussmac_hv.img);
    if (pd->chars_menu.b_oussmac_hv.txtr)
        mlx_delete_texture(pd->chars_menu.b_oussmac_hv.txtr);
}

static void delete_game_ui_textures(t_parsed_data *pd)
{
    if (pd->game_ui.gun.img)
        mlx_delete_image(pd->mlx, pd->game_ui.gun.img);
    if (pd->game_ui.gun.txtr)
        mlx_delete_texture(pd->game_ui.gun.txtr);
    
    if (pd->game_ui.gun_aim.img)
        mlx_delete_image(pd->mlx, pd->game_ui.gun_aim.img);
    if (pd->game_ui.gun_aim.txtr)
        mlx_delete_texture(pd->game_ui.gun_aim.txtr);
    
    if (pd->game_ui.health.img)
        mlx_delete_image(pd->mlx, pd->game_ui.health.img);
    if (pd->game_ui.health.txtr)
        mlx_delete_texture(pd->game_ui.health.txtr);
    
    if (pd->game_ui.health_bg.img)
        mlx_delete_image(pd->mlx, pd->game_ui.health_bg.img);
    if (pd->game_ui.health_bg.txtr)
        mlx_delete_texture(pd->game_ui.health_bg.txtr);
    
    if (pd->game_ui.game_over.img)
        mlx_delete_image(pd->mlx, pd->game_ui.game_over.img);
    if (pd->game_ui.game_over.txtr)
        mlx_delete_texture(pd->game_ui.game_over.txtr);
    if (pd->game_ui.game_won.img)
        mlx_delete_image(pd->mlx, pd->game_ui.game_won.img);
    if (pd->game_ui.game_won.txtr)
        mlx_delete_texture(pd->game_ui.game_won.txtr);

}

static void delete_enemy_textures(t_parsed_data *pd)
{
    int i;

    if (pd->enemy_count == 0 || pd->enemies == NULL)
        return;
    
    i = 0;
    while (i < pd->enemy_count)
    {
        if (pd->enemies[i].skin.txtr)
            mlx_delete_texture(pd->enemies[i].skin.txtr);
        if (pd->enemies[i].skin.img)
            mlx_delete_image(pd->mlx, pd->enemies[i].skin.img);
        
        if (pd->enemies[i].walk1.txtr)
            mlx_delete_texture(pd->enemies[i].walk1.txtr);
        if (pd->enemies[i].walk1.img)
            mlx_delete_image(pd->mlx, pd->enemies[i].walk1.img);
        
        if (pd->enemies[i].walk2.txtr)
            mlx_delete_texture(pd->enemies[i].walk2.txtr);
        if (pd->enemies[i].walk2.img)
            mlx_delete_image(pd->mlx, pd->enemies[i].walk2.img);
        
        if (pd->enemies[i].walk3.txtr)
            mlx_delete_texture(pd->enemies[i].walk3.txtr);
        if (pd->enemies[i].walk3.img)
            mlx_delete_image(pd->mlx, pd->enemies[i].walk3.img);
        
        if (pd->enemies[i].attack1.txtr)
            mlx_delete_texture(pd->enemies[i].attack1.txtr);
        if (pd->enemies[i].attack1.img)
            mlx_delete_image(pd->mlx, pd->enemies[i].attack1.img);
        
        if (pd->enemies[i].attack2.txtr)
            mlx_delete_texture(pd->enemies[i].attack2.txtr);
        if (pd->enemies[i].attack2.img)
            mlx_delete_image(pd->mlx, pd->enemies[i].attack2.img);
        
        if (pd->enemies[i].attack3.txtr)
            mlx_delete_texture(pd->enemies[i].attack3.txtr);
        if (pd->enemies[i].attack3.img)
            mlx_delete_image(pd->mlx, pd->enemies[i].attack3.img);
        
        if (pd->enemies[i].death1.txtr)
            mlx_delete_texture(pd->enemies[i].death1.txtr);
        if (pd->enemies[i].death1.img)
            mlx_delete_image(pd->mlx, pd->enemies[i].death1.img);
        
        if (pd->enemies[i].death2.txtr)
            mlx_delete_texture(pd->enemies[i].death2.txtr);
        if (pd->enemies[i].death2.img)
            mlx_delete_image(pd->mlx, pd->enemies[i].death2.img);
        
        if (pd->enemies[i].anim_img)
            mlx_delete_image(pd->mlx, pd->enemies[i].anim_img);
        
        i++;
    }
}

static void delete_door_wall_textures(t_parsed_data *pd)
{
    if (pd->txtr_ea.img)
        mlx_delete_image(pd->mlx, pd->txtr_ea.img);
    if (pd->txtr_ea.txtr)
        mlx_delete_texture(pd->txtr_ea.txtr);
    
    if (pd->txtr_no.img)
        mlx_delete_image(pd->mlx, pd->txtr_no.img);
    if (pd->txtr_no.txtr)
        mlx_delete_texture(pd->txtr_no.txtr);
    
    if (pd->txtr_so.img)
        mlx_delete_image(pd->mlx, pd->txtr_so.img);
    if (pd->txtr_so.txtr)
        mlx_delete_texture(pd->txtr_so.txtr);
    
    if (pd->txtr_we.img)
        mlx_delete_image(pd->mlx, pd->txtr_we.img);
    if (pd->txtr_we.txtr)
        mlx_delete_texture(pd->txtr_we.txtr);
    
    if (pd->door_txt.img)
        mlx_delete_image(pd->mlx, pd->door_txt.img);
    if (pd->door_txt.txtr)
        mlx_delete_texture(pd->door_txt.txtr);
}

static void delete_medkit_textures(t_parsed_data *pd)
{
    int i;

    if (pd->medkit.img)
        mlx_delete_image(pd->mlx, pd->medkit.img);
    if (pd->medkit.txtr)
        mlx_delete_texture(pd->medkit.txtr);

    if (!pd->medkits)
        return ;
    i = 0;
    while (i < MAX_ENEMIES)
    {
        if (pd->medkits[i].img.img)
            mlx_delete_image(pd->mlx, pd->medkits[i].img.img);
        if (pd->medkits[i].img.txtr)
            mlx_delete_texture(pd->medkits[i].img.txtr);
        i++;
    }
}

void delete_all_textures(t_parsed_data *pd)
{
    if (!pd)
        return ;
    if (!pd->mlx)
        return ;
    delete_player_textures(pd);
    delete_screen_and_map(pd);
    delete_main_menu_textures(pd);
    delete_characters_ui_textures(pd);
    delete_game_ui_textures(pd);
    delete_enemy_textures(pd);
    delete_door_wall_textures(pd);
    delete_medkit_textures(pd);
}
