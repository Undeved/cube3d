#include "../../cube.h"

static void	free_shared_walk_attack_textures(t_parsed_data *pd)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (pd->shared_enemy_textures.skin_walker_walk[i].txtr)
			mlx_delete_texture(pd->shared_enemy_textures.skin_walker_walk[i].txtr);
		if (pd->shared_enemy_textures.skin_walker_attack[i].txtr)
			mlx_delete_texture(pd->shared_enemy_textures.skin_walker_attack[i].txtr);
		if (pd->shared_enemy_textures.memory_leak_walk[i].txtr)
			mlx_delete_texture(pd->shared_enemy_textures.memory_leak_walk[i].txtr);
		if (pd->shared_enemy_textures.memory_leak_attack[i].txtr)
			mlx_delete_texture(pd->shared_enemy_textures.memory_leak_attack[i].txtr);
		if (pd->shared_enemy_textures.segv_walk[i].txtr)
			mlx_delete_texture(pd->shared_enemy_textures.segv_walk[i].txtr);
		if (pd->shared_enemy_textures.segv_attack[i].txtr)
			mlx_delete_texture(pd->shared_enemy_textures.segv_attack[i].txtr);
		i++;
	}
}

static void	free_shared_death_textures(t_parsed_data *pd)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (pd->shared_enemy_textures.skin_walker_death[i].txtr)
			mlx_delete_texture(pd->shared_enemy_textures.skin_walker_death[i].txtr);
		if (pd->shared_enemy_textures.memory_leak_death[i].txtr)
			mlx_delete_texture(pd->shared_enemy_textures.memory_leak_death[i].txtr);
		if (pd->shared_enemy_textures.segv_death[i].txtr)
			mlx_delete_texture(pd->shared_enemy_textures.segv_death[i].txtr);
		i++;
	}
}

void free_shared_enemy_textures(t_parsed_data *pd)
{
	if (!pd->shared_enemy_textures.initialized)
		return ;
	free_shared_walk_attack_textures(pd);
	free_shared_death_textures(pd);
	pd->shared_enemy_textures.initialized = false;
	pd->shared_enemy_textures.skin_walker_initialized = false;
	pd->shared_enemy_textures.memory_leak_initialized = false;
	pd->shared_enemy_textures.segv_initialized = false;
}

static void	free_enemy_skin_textures(t_enemy *enemy)
{
	if (enemy->skin.txtr)
	{
		mlx_delete_texture(enemy->skin.txtr);
		enemy->skin.txtr = NULL;
	}
}

void	free_enemy_textures(t_parsed_data *pd)
{
	int	i;

	if (pd->enemy_count == 0 || pd->enemies == NULL)
		return ;
	i = 0;
	while (i < pd->enemy_count)
	{
		free_enemy_skin_textures(&pd->enemies[i]);
		i++;
	}
}
