/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_radar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:15:07 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/10 08:27:48 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

static void	rotate_point(double *x, double *y, double angle)
{
	double	old_x;
	double	old_y;

	old_x = *x;
	old_y = *y;
	*x = old_x * cos(angle) - old_y * sin(angle);
	*y = old_x * sin(angle) + old_y * cos(angle);
}

static void	draw_valid_map_cell(t_parsed_data *pd,
	t_pos pixel, char cell, int pixel_dist)
{
	if (cell == '1' || cell == ' ')
		mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y,
			shade_color(WALL_ICON, pixel_dist, 0.015));
	else if (cell == '0')
		mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y,
			shade_color(FLOOR_ICON, pixel_dist, 0.015));
	else if (cell == 'D')
		mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y,
			shade_color(DOOR_ICON, pixel_dist, 0.015));
	else if (cell == 'O')
		mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y,
			shade_color(OPEN_DOOR_ICON, pixel_dist, 0.015));
}

static void	init_mv(t_mv *mv, t_pos pixel, t_pos center)
{
	mv->diff.x = pixel.x - center.x;
	mv->diff.y = pixel.y - center.y;
	mv->pixel_dist = sqrt(sqr(mv->diff.x) + sqr(mv->diff.y));
}

static void	draw_minimap_pixel(t_parsed_data *pd,
	t_pos pixel, t_pos center, double angle)
{
	t_mv	mv;

	init_mv(&mv, pixel, center);
	if (sqr(mv.diff.x) + sqr(mv.diff.y) <= sqr(MINI_MAP_SIZE / 2
			- RADIOUS_MARGIN - BORDER_WIDTH))
	{
		mv.w.x = mv.diff.x * 0.1;
		mv.w.y = mv.diff.y * 0.1;
		rotate_point(&mv.w.x, &mv.w.y, -angle);
		mv.map.x = (int)(pd->player.bpos.x + mv.w.x);
		mv.map.y = (int)(pd->player.bpos.y + mv.w.y);
		if (mv.map.x >= 0 && mv.map.x < pd->level.max_x
			&& mv.map.y >= 0 && mv.map.y < pd->level.max_y)
		{
			mv.cell = pd->map_grid[mv.map.y][mv.map.x];
			draw_valid_map_cell(pd, pixel, mv.cell, mv.pixel_dist);
			if (enemy_icon(pd->player.bpos.x + mv.w.x,
					pd->player.bpos.y + mv.w.y, pd))
				mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y,
					shade_color(0xFF0000FF, mv.pixel_dist, 0.015));
		}
		else
			mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y,
				shade_color(WALL_ICON, mv.pixel_dist, 0.015));
	}
}

void	draw_minimap_grid(t_parsed_data *pd)
{
	t_pos	center;
	t_pos	pixel;
	double	angle;

	center.x = MINI_MAP_SIZE / 2;
	center.y = MINI_MAP_SIZE / 2;
	angle = atan2(-pd->player.bdir.y, pd->player.bdir.x) - (PI / 2);
	pixel.y = 0;
	while (pixel.y < MINI_MAP_SIZE)
	{
		pixel.x = 0;
		while (pixel.x < MINI_MAP_SIZE)
		{
			draw_minimap_pixel(pd, pixel, center, angle);
			pixel.x++;
		}
		pixel.y++;
	}
}
