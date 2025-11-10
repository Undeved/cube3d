/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shared_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 03:49:40 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/10 03:53:10 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

static void	init_enemy_skin(t_parsed_data *pd, int i)
{
	if (pd->enemies[i].type == FT_SKIN_WALKER)
	{
		pd->enemies[i].skin = pd->sh.skin_walker_default;
	}
	else if (pd->enemies[i].type == MEMORY_LEAK)
	{
		pd->enemies[i].skin = pd->sh.memory_leak_default;
	}
	else if (pd->enemies[i].type == SEGV)
	{
		pd->enemies[i].skin = pd->sh.segv_default;
	}
}

static void	assign_mem_segv(t_parsed_data *pd, int i)
{
	t_enemy	*enemy;

	enemy = &pd->enemies[i];
	if (enemy->type == MEMORY_LEAK)
	{
		enemy->walk1 = &pd->sh.memory_leak_walk[0];
		enemy->walk2 = &pd->sh.memory_leak_walk[1];
		enemy->walk3 = &pd->sh.memory_leak_walk[2];
		enemy->attack1 = &pd->sh.memory_leak_attack[0];
		enemy->attack2 = &pd->sh.memory_leak_attack[1];
		enemy->attack3 = &pd->sh.memory_leak_attack[2];
		enemy->death1 = &pd->sh.memory_leak_death[0];
		enemy->death2 = &pd->sh.memory_leak_death[1];
	}
	else if (enemy->type == SEGV)
	{
		enemy->walk1 = &pd->sh.segv_walk[0];
		enemy->walk2 = &pd->sh.segv_walk[1];
		enemy->walk3 = &pd->sh.segv_walk[2];
		enemy->attack1 = &pd->sh.segv_attack[0];
		enemy->attack2 = &pd->sh.segv_attack[1];
		enemy->attack3 = &pd->sh.segv_attack[2];
		enemy->death1 = &pd->sh.segv_death[0];
		enemy->death2 = &pd->sh.segv_death[1];
	}
}

static void	assign_shared_textures(t_parsed_data *pd, int i)
{
	t_enemy	*enemy;

	enemy = &pd->enemies[i];
	if (enemy->type == FT_SKIN_WALKER)
	{
		enemy->walk1 = &pd->sh.skin_walker_walk[0];
		enemy->walk2 = &pd->sh.skin_walker_walk[1];
		enemy->walk3 = &pd->sh.skin_walker_walk[2];
		enemy->attack1 = &pd->sh.skin_walker_attack[0];
		enemy->attack2 = &pd->sh.skin_walker_attack[1];
		enemy->attack3 = &pd->sh.skin_walker_attack[2];
		enemy->death1 = &pd->sh.skin_walker_death[0];
		enemy->death2 = &pd->sh.skin_walker_death[1];
	}
	else
		assign_mem_segv(pd, i);
}

static void	init_animation_state(t_enemy *enemy)
{
	enemy->anim_img = enemy->skin.img;
	enemy->anim_frame = 0;
	enemy->anim_counter = 0;
	enemy->is_attacking = false;
	enemy->attack_anim_counter = 0;
	enemy->is_dying = false;
	enemy->death_anim_frame = 0;
	enemy->death_anim_counter = 0;
	enemy->death_timer = 0;
	enemy->is_highlighted = false;
	enemy->highlight_timer = 0;
	enemy->patrol_target_timer = 0;
	enemy->patrol_change_interval = 300;
}

void	init_sh(t_parsed_data *pd)
{
	int	i;

	if (pd->enemy_count == 0 || pd->enemies == NULL)
		return ;
	init_shared_textures(pd);
	i = 0;
	while (i < pd->enemy_count)
	{
		init_enemy_skin(pd, i);
		assign_shared_textures(pd, i);
		init_animation_state(&pd->enemies[i]);
		i++;
	}
	free_sh_txtrs(pd);
}
