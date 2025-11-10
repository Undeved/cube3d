/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player_icon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:13:38 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/10 08:27:54 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

bool	enemy_icon(double x, double y, t_parsed_data *pd)
{
	int		i;
	double	ex;
	double	ey;

	i = 0;
	while (i < pd->enemy_count)
	{
		if (pd->enemies[i].dead)
		{
			i++;
			continue ;
		}
		ex = pd->enemies[i].b_pos.x;
		ey = pd->enemies[i].b_pos.y;
		if (fabs(ex - x) < 0.5 && fabs(ey - y) < 0.5)
			return (true);
		i++;
	}
	return (false);
}

void	render_player_icon(t_parsed_data *pd)
{
	t_pos	pixel;
	t_pos	diff;
	t_pos	center;
	int		radious;

	center.x = MINI_MAP_SIZE / 2;
	center.y = MINI_MAP_SIZE / 2;
	radious = 5;
	pixel.y = 0;
	while (pixel.y < MINI_MAP_SIZE)
	{
		pixel.x = 0;
		while (pixel.x < MINI_MAP_SIZE)
		{
			diff.x = pixel.x - center.x;
			diff.y = pixel.y - center.y;
			if (sqr(diff.x) + sqr(diff.y) <= sqr(radious))
				mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y, PLAYER_ICON);
			pixel.x++;
		}
		pixel.y++;
	}
}

void	render_radar(t_parsed_data *pd)
{
	draw_minimap_grid(pd);
	render_player_icon(pd);
}
