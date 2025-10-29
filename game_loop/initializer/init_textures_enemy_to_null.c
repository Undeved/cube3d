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

void init_shared_enemy_textures_to_null(t_parsed_data *pd)
{
	int	i;
	pd->shared_enemy_textures.initialized = false;
	pd->shared_enemy_textures.skin_walker_initialized = false;
	pd->shared_enemy_textures.memory_leak_initialized = false;
	pd->shared_enemy_textures.segv_initialized = false;
    
	i = 0;
	while (i < 3)
	{
		pd->shared_enemy_textures.skin_walker_walk[i].img = NULL;
		pd->shared_enemy_textures.skin_walker_walk[i].txtr = NULL;
		pd->shared_enemy_textures.skin_walker_attack[i].img = NULL;
		pd->shared_enemy_textures.skin_walker_attack[i].txtr = NULL;
		pd->shared_enemy_textures.memory_leak_walk[i].img = NULL;
		pd->shared_enemy_textures.memory_leak_walk[i].txtr = NULL;
		pd->shared_enemy_textures.memory_leak_attack[i].img = NULL;
		pd->shared_enemy_textures.memory_leak_attack[i].txtr = NULL;
		pd->shared_enemy_textures.segv_walk[i].img = NULL;
		pd->shared_enemy_textures.segv_walk[i].txtr = NULL;
		pd->shared_enemy_textures.segv_attack[i].img = NULL;
		pd->shared_enemy_textures.segv_attack[i].txtr = NULL;
		i++;
	}
	i = 0;
	while (i < 2)
	{
		pd->shared_enemy_textures.skin_walker_death[i].img = NULL;
		pd->shared_enemy_textures.skin_walker_death[i].txtr = NULL;
		pd->shared_enemy_textures.memory_leak_death[i].img = NULL;
		pd->shared_enemy_textures.memory_leak_death[i].txtr = NULL;
		pd->shared_enemy_textures.segv_death[i].img = NULL;
		pd->shared_enemy_textures.segv_death[i].txtr = NULL;
		i++;
	}
}

void init_enemy_textures_to_null(t_parsed_data *pd)
{
	int	i;

	if (pd->enemy_count == 0 || pd->enemies == NULL)
		return ;
    init_shared_enemy_textures_to_null(pd);
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
