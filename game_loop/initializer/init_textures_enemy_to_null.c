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
	pd->medkit.img = NULL;
	pd->medkit.txtr = NULL;
	pd->medkits = NULL;
}

void init_sh_to_null(t_parsed_data *pd)
{
	int	i;
	pd->sh.initialized = false;
	pd->sh.skin_walker_initialized = false;
	pd->sh.memory_leak_initialized = false;
	pd->sh.segv_initialized = false;
	init_shared_attack_null(pd);
	i = 0;
	while (i < 2)
	{
		pd->sh.skin_walker_death[i].img = NULL;
		pd->sh.skin_walker_death[i].txtr = NULL;
		pd->sh.memory_leak_death[i].img = NULL;
		pd->sh.memory_leak_death[i].txtr = NULL;
		pd->sh.segv_death[i].img = NULL;
		pd->sh.segv_death[i].txtr = NULL;
		i++;
	}
}

void init_enemy_textures_to_null(t_parsed_data *pd)
{
	int	i;

	if (pd->enemy_count == 0 || pd->enemies == NULL)
		return ;
    init_sh_to_null(pd);
	i = 0;
	while (i < pd->enemy_count)
	{
		pd->enemies[i].anim_img = NULL;
		pd->enemies[i].anim_frame = 0;
		pd->enemies[i].anim_counter = 0;
		pd->enemies[i].is_attacking = false;
		pd->enemies[i].attack_anim_counter = 0;
		pd->enemies[i].is_dying = false;
		pd->enemies[i].death_anim_counter = 0;
		pd->enemies[i].death_anim_frame = 0;
		pd->enemies[i].death_timer = 0;
		i++;
	}
}
