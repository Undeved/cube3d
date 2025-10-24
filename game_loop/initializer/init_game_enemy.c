#include "../../cube.h"

static void	load_default_skin(t_parsed_data *pd, int i)
{
	if (pd->enemies[i].type == FT_SKIN_WALKER)
		pd->enemies[i].skin.txtr = mlx_load_png(SKIN_WALKER_DFL);
	else if (pd->enemies[i].type == MEMORY_LEAK)
		pd->enemies[i].skin.txtr = mlx_load_png(MEMORY_LEAK_DFL);
	else if (pd->enemies[i].type == SEGV)
		pd->enemies[i].skin.txtr = mlx_load_png(SEGV_DFL);
	if (pd->enemies[i].skin.txtr == NULL)
	{
		print_error("Error\nEnemy Texture Path Missing.\n");
		mind_free_all(EXIT_FAILURE);
	}
}

static void	init_enemy_skin(t_parsed_data *pd, int i)
{
	if (pd->enemies[i].skin.txtr == NULL)
		load_default_skin(pd, i);
	if (pd->enemies[i].skin.img == NULL)
	{
		pd->enemies[i].skin.img = mlx_texture_to_image(pd->mlx,
				pd->enemies[i].skin.txtr);
		if (pd->enemies[i].skin.img == NULL)
			mind_free_all(EXIT_FAILURE);
	}
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
    enemy->patrol_change_interval = 300 ;
}

void	init_enemy_textures(t_parsed_data *pd)
{
	int	i;

	if (pd->enemy_count == 0 || pd->enemies == NULL)
		return ;
	i = 0;
	while (i < pd->enemy_count)
	{
		init_enemy_skin(pd, i);
		init_animation_frames(pd, i);
		init_animation_state(&pd->enemies[i]);
		i++;
	}
	free_enemy_textures(pd);
}
