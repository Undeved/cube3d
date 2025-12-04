/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_interaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 05:28:48 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/22 14:37:13 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

static bool	check_nearby_doors(t_parsed_data *pd, int px, int py)
{
	bool opened_one;

	opened_one = false;
	if (pd->map_grid[py][px + 1] == 'D')
	{
		pd->map_grid[py][px + 1] = 'O';
		opened_one = true;
	}
	else if (pd->map_grid[py][px + 1] == 'O')
	{
		pd->map_grid[py][px + 1] = 'D';
		opened_one = true;
	}
	if (pd->map_grid[py][px - 1] == 'D')
	{
		pd->map_grid[py][px - 1] = 'O';
		opened_one = true;
	}
	else if (pd->map_grid[py][px - 1] == 'O')
	{
		pd->map_grid[py][px - 1] = 'D';
		opened_one = true;
	}
	if (pd->map_grid[py + 1][px] == 'D')
	{
		pd->map_grid[py + 1][px] = 'O';
		opened_one = true;
	}
	else if (pd->map_grid[py + 1][px] == 'O')
	{
		pd->map_grid[py + 1][px] = 'D';
		opened_one = true;
	}
	if (pd->map_grid[py - 1][px] == 'D')
	{
		pd->map_grid[py - 1][px] = 'O';
		opened_one = true;
	}
	else if (pd->map_grid[py - 1][px] == 'O')
	{
		pd->map_grid[py - 1][px] = 'D';
		opened_one = true;
	}
	return (opened_one);
}

void	interact_with_door(t_parsed_data *pd)
{
	static bool	e_was_pressed = false;
	bool		e_pressed;
	int			px;
	int			py;

	px = (int)pd->player.bpos.x;
	py = (int)pd->player.bpos.y;
	e_pressed = pd->keys.pressed[MLX_KEY_E];
	if (e_pressed && !e_was_pressed)
	{
		if (check_nearby_doors(pd, px, py) == true)
			play_sound_once(pd, "sound/door.mp3");
	}
	e_was_pressed = e_pressed;
}

void	init_door_texture(t_parsed_data *pd)
{
	pd->door_txt.txtr = mlx_load_png(DOOR_TEXTURE);
	if (pd->door_txt.txtr == NULL)
	{
		print_error("Error\nDoor Texture Path Missing.\n");
		mind_free_all(EXIT_FAILURE);
	}
	pd->door_txt.img = mlx_texture_to_image(pd->mlx, pd->door_txt.txtr);
	if (pd->door_txt.img == NULL)
		mind_free_all(EXIT_FAILURE);
}
