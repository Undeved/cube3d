#include "../../cube.h"

static void	free_enemy_skin_walk_textures(t_enemy *enemy)
{
    if (enemy->skin.txtr)
	{
		mlx_delete_texture(enemy->skin.txtr);
		enemy->skin.txtr = NULL;
	}
	if (enemy->walk1.txtr)
	{
		mlx_delete_texture(enemy->walk1.txtr);
		enemy->walk1.txtr = NULL;
	}
	if (enemy->walk2.txtr)
	{
		mlx_delete_texture(enemy->walk2.txtr);
		enemy->walk2.txtr = NULL;
	}
	if (enemy->walk3.txtr)
	{
		mlx_delete_texture(enemy->walk3.txtr);
		enemy->walk3.txtr = NULL;
	}
}

static void	free_enemy_attack_textures(t_enemy *enemy)
{
	if (enemy->attack1.txtr)
	{
		mlx_delete_texture(enemy->attack1.txtr);
		enemy->attack1.txtr = NULL;
	}
	if (enemy->attack2.txtr)
	{
		mlx_delete_texture(enemy->attack2.txtr);
		enemy->attack2.txtr = NULL;
	}
	if (enemy->attack3.txtr)
	{
		mlx_delete_texture(enemy->attack3.txtr);
		enemy->attack3.txtr = NULL;
	}
}

static void	free_enemy_death_textures(t_enemy *enemy)
{
	if (enemy->death1.txtr)
	{
		mlx_delete_texture(enemy->death1.txtr);
		enemy->death1.txtr = NULL;
	}
	if (enemy->death2.txtr)
	{
		mlx_delete_texture(enemy->death2.txtr);
		enemy->death2.txtr = NULL;
	}
}

static void	free_single_enemy_textures(t_enemy *enemy)
{
	free_enemy_skin_walk_textures(enemy);
	free_enemy_attack_textures(enemy);
	free_enemy_death_textures(enemy);
}

void	free_enemy_textures(t_parsed_data *pd)
{
	int	i;

	if (pd->enemy_count == 0 || pd->enemies == NULL)
		return ;
	i = 0;
	while (i < pd->enemy_count)
	{
		free_single_enemy_textures(&pd->enemies[i]);
		i++;
	}
}
