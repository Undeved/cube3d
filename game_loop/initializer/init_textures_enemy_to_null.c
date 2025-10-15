#include "../../cube.h"

void init_screen_and_map(t_parsed_data *pd)
{
    pd->screen = NULL;
    pd->minimap.img = NULL;
}

void init_door_wall(t_parsed_data *pd)
{
    pd->txtr_ea.img = NULL;
    pd->txtr_ea.txtr = NULL;
    pd->txtr_no.img = NULL;
    pd->txtr_no.txtr = NULL;
    pd->txtr_so.img = NULL;
    pd->txtr_so.txtr = NULL;
    pd->txtr_we.img = NULL;
    pd->txtr_we.txtr = NULL;
    pd->door_txt.img = NULL;
    pd->door_txt.txtr = NULL;
}

void init_medkit_textures(t_parsed_data *pd)
{
    int i;

    pd->medkit.img = NULL;
    pd->medkit.txtr = NULL;
    pd->medkits = NULL;
}

static void skin_walk_attack(t_parsed_data *pd, int i)
{
    pd->enemies[i].skin.txtr = NULL;
    pd->enemies[i].skin.img = NULL;
    pd->enemies[i].walk1.txtr = NULL;
    pd->enemies[i].walk1.img  = NULL;
    pd->enemies[i].walk2.txtr = NULL;
    pd->enemies[i].walk2.img  = NULL;
    pd->enemies[i].walk3.txtr = NULL;
    pd->enemies[i].walk3.img  = NULL;
    pd->enemies[i].attack1.txtr = NULL;
    pd->enemies[i].attack1.img  = NULL;
    pd->enemies[i].attack2.txtr = NULL;
    pd->enemies[i].attack2.img  = NULL;
    pd->enemies[i].attack3.txtr = NULL;
    pd->enemies[i].attack3.img  = NULL;
}

void init_enemy_textures_to_null(t_parsed_data *pd)
{
    int i;

    if (pd->enemy_count == 0 || pd->enemies == NULL)
        return ;
    i = 0;
    while (i < pd->enemy_count)
    {
        skin_walk_attack(pd, i);
        pd->enemies[i].anim_img = NULL;
        pd->enemies[i].anim_frame = 0;
        pd->enemies[i].anim_counter = 0;
        pd->enemies[i].is_attacking = false;
        pd->enemies[i].attack_anim_counter = 0;
        pd->enemies[i].death1.txtr = NULL;
        pd->enemies[i].death1.img = NULL;
        pd->enemies[i].death2.txtr = NULL;
        pd->enemies[i].death2.img = NULL;
        pd->enemies[i].is_dying = false;
        pd->enemies[i].death_anim_counter = 0;
        pd->enemies[i].death_anim_frame = 0;
        pd->enemies[i].death_timer = 0; 
        i++;
    }
}
