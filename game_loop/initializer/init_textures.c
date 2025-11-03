#include "../../cube.h"

static void init_player_textures(t_parsed_data *pd)
{
    // init gun textures
    pd->player.gun.idle.img = NULL;
    pd->player.gun.idle.txtr = NULL;
    pd->player.gun.aim.img = NULL;
    pd->player.gun.aim.txtr = NULL;
    pd->player.gun.shoot.frames = NULL;
    pd->player.gun.reload.frames = NULL;
}

static void init_main_menu_textures(t_parsed_data *pd)
{
    pd->menu.bg.img = NULL;
    pd->menu.bg.txtr = NULL;
    pd->menu.title.img = NULL;
    pd->menu.title.txtr = NULL;
    pd->menu.b_start.img = NULL;
    pd->menu.b_start.txtr = NULL;
    pd->menu.b_chars.img = NULL;
    pd->menu.b_chars.txtr = NULL;
    pd->menu.b_exit.img = NULL;
    pd->menu.b_exit.txtr = NULL;
    pd->menu.b_start_hv.img = NULL;
    pd->menu.b_start_hv.txtr = NULL;
    pd->menu.b_chars_hv.img = NULL;
    pd->menu.b_chars_hv.txtr = NULL;
    pd->menu.b_exit_hv.img = NULL;
    pd->menu.b_exit_hv.txtr = NULL;
}

static void init_characters_ui_textures(t_parsed_data *pd)
{
    pd->chars_menu.bg.img = NULL;
    pd->chars_menu.bg.txtr = NULL;
    pd->chars_menu.selected.img = NULL;
    pd->chars_menu.selected.txtr = NULL;

    pd->chars_menu.b_jesse.img = NULL;
    pd->chars_menu.b_jesse.txtr = NULL;
    pd->chars_menu.b_chorus.img = NULL;
    pd->chars_menu.b_chorus.txtr = NULL;
    pd->chars_menu.b_oussmac.img = NULL;
    pd->chars_menu.b_oussmac.txtr = NULL;

    pd->chars_menu.b_jesse_hv.img = NULL;
    pd->chars_menu.b_jesse_hv.txtr = NULL;
    pd->chars_menu.b_chorus_hv.img = NULL;
    pd->chars_menu.b_chorus_hv.txtr = NULL;
    pd->chars_menu.b_oussmac_hv.img = NULL;
    pd->chars_menu.b_oussmac_hv.txtr = NULL;
}

static void init_game_ui_textures(t_parsed_data *pd)
{
    pd->game_ui.no_ammo.img = NULL;
    pd->game_ui.no_ammo.txtr = NULL;
    pd->game_ui.gun.img = NULL;
    pd->game_ui.gun.txtr = NULL;
    pd->game_ui.gun_aim.img = NULL;
    pd->game_ui.gun_aim.txtr = NULL;
    pd->game_ui.health.img = NULL;
    pd->game_ui.health.txtr = NULL;
    pd->game_ui.health_bg.img = NULL;
    pd->game_ui.health_bg.txtr = NULL;
    pd->game_ui.game_over.img = NULL;
    pd->game_ui.game_over.txtr = NULL;
    pd->game_ui.game_won.img = NULL;
    pd->game_ui.game_won.txtr = NULL;
}

void init_all_textures(t_parsed_data *pd)
{
    init_player_textures(pd);
    init_screen_and_map(pd);
    init_main_menu_textures(pd);
    init_characters_ui_textures(pd);
    init_game_ui_textures(pd);
    init_enemy_textures_to_null(pd);
    init_door_wall(pd);
    init_medkit_textures(pd);
}