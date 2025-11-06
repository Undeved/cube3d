/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_visibility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 01:11:45 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 03:41:56 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	sort_enemies_by_distance(t_enemy_draw_data *draw_data, int count)
{
	int					i;
	int					j;
	t_enemy_draw_data	tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (draw_data[j].distance < draw_data[j + 1].distance)
			{
				tmp = draw_data[j];
				draw_data[j] = draw_data[j + 1];
				draw_data[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

bool	compute_enemy_transform(t_parsed_data *pd, int i, t_enemy_calc *res)
{
	bool	visible;
	double	inv_det;

	res->rel_pos.x = pd->enemies[i].b_pos.x - pd->player.bpos.x;
	res->rel_pos.y = pd->enemies[i].b_pos.y - pd->player.bpos.y;
	res->distance = sqrt(res->rel_pos.x * res->rel_pos.x
			+ res->rel_pos.y * res->rel_pos.y);
	visible = has_line_of_sight(pd, pd->player.bpos, pd->enemies[i].b_pos);
	if (res->distance > 24.0 || !visible)
		return (false);
	inv_det = 1.0 / (pd->player.camera_plane.dir.x * pd->player.bdir.y
			- pd->player.bdir.x * pd->player.camera_plane.dir.y);
	res->transform.x = -inv_det * (pd->player.bdir.y * res->rel_pos.x
			- pd->player.bdir.x * res->rel_pos.y);
	res->transform.y = inv_det * (-pd->player.camera_plane.dir.y
			* res->rel_pos.x + pd->player.camera_plane.dir.x * res->rel_pos.y);
	if (res->transform.y <= 0)
		return (false);
	return (true);
}

bool	process_and_store_enemy(t_parsed_data *pd, int i,
		t_enemy_draw_data *out_draw)
{
	t_enemy_calc	calc;

	if (!compute_enemy_transform(pd, i, &calc))
		return (false);
	out_draw->enemy = &pd->enemies[i];
	out_draw->distance = calc.distance;
	out_draw->visible = true;
	out_draw->transform = calc.transform;
	out_draw->sprite_screen_x = (int)((WIDTH / 2)
			* (1 + calc.transform.x / calc.transform.y));
	out_draw->sprite_height = abs((int)(HEIGHT / calc.transform.y));
	out_draw->sprite_width = abs((int)(HEIGHT / calc.transform.y));
	return (true);
}

int	collect_visible_enemies(t_parsed_data *pd, t_enemy_draw_data *draw_data)
{
	int	i;
	int	draw_count;

	draw_count = 0;
	i = 0;
	while (i < pd->enemy_count && draw_count < MAX_ENEMIES)
	{
		if (pd->enemies[i].dead && !pd->enemies[i].is_dying)
		{
			i++;
			continue ;
		}
		if (process_and_store_enemy(pd, i, &draw_data[draw_count]))
		{
			draw_count++;
		}
		i++;
	}
	return (draw_count);
}

int	collect_and_sort_enemies_small(t_parsed_data *pd,
		t_enemy_draw_data *draw_data)
{
	int	draw_count;

	draw_count = collect_visible_enemies(pd, draw_data);
	if (draw_count > 1)
		sort_enemies_by_distance(draw_data, draw_count);
	return (draw_count);
}
