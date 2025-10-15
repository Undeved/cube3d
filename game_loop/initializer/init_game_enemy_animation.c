#include "../../cube.h"

static void set_animation_path_segv(char **paths)
{
    paths[0] = SEGV_W1;
    paths[1] = SEGV_W2;
    paths[2] = SEGV_W3;
    paths[3] = SEGV_A1;
    paths[4] = SEGV_A2;
    paths[5] = SEGV_A3;
    paths[6] = SEGV_D1;
    paths[7] = SEGV_D2;
}

static void	set_animation_paths(t_enemy *enemy, char **paths)
{
	if (enemy->type == FT_SKIN_WALKER)
	{
		paths[0] = SKIN_WALKER_W1;
		paths[1] = SKIN_WALKER_W2;
		paths[2] = SKIN_WALKER_W3;
		paths[3] = SKIN_WALKER_A1;
		paths[4] = SKIN_WALKER_A2;
		paths[5] = SKIN_WALKER_A3;
		paths[6] = SKIN_WALKER_D1;
		paths[7] = SKIN_WALKER_D2;
	}
	else if (enemy->type == MEMORY_LEAK)
	{
		paths[0] = MEMORY_LEAK_W1;
		paths[1] = MEMORY_LEAK_W2;
		paths[2] = MEMORY_LEAK_W3;
		paths[3] = MEMORY_LEAK_A1;
		paths[4] = MEMORY_LEAK_A2;
		paths[5] = MEMORY_LEAK_A3;
		paths[6] = MEMORY_LEAK_D1;
		paths[7] = MEMORY_LEAK_D2;
	}
	else if (enemy->type == SEGV)
		set_animation_path_segv(paths);
}

static void	load_animation_frame(t_parsed_data *pd, int i, t_raw_img *frame, char *path)
{
	if (frame->txtr == NULL)
	{
		frame->txtr = mlx_load_png(path);
		if (frame->txtr == NULL)
		{
			print_error("Error\nEnemy animation Texture Path Missing.\n");
			mind_free_all(EXIT_FAILURE);
		}
	}
	if (frame->img == NULL)
	{
		frame->img = mlx_texture_to_image(pd->mlx, frame->txtr);
		if (frame->img == NULL)
			mind_free_all(EXIT_FAILURE);
	}
}

void	init_animation_frames(t_parsed_data *pd, int i)
{
	char	*paths[8];

	set_animation_paths(&pd->enemies[i], paths);
	load_animation_frame(pd, i, &pd->enemies[i].walk1, paths[0]);
	load_animation_frame(pd, i, &pd->enemies[i].walk2, paths[1]);
	load_animation_frame(pd, i, &pd->enemies[i].walk3, paths[2]);
	load_animation_frame(pd, i, &pd->enemies[i].attack1, paths[3]);
	load_animation_frame(pd, i, &pd->enemies[i].attack2, paths[4]);
	load_animation_frame(pd, i, &pd->enemies[i].attack3, paths[5]);
	load_animation_frame(pd, i, &pd->enemies[i].death1, paths[6]);
	load_animation_frame(pd, i, &pd->enemies[i].death2, paths[7]);
}
