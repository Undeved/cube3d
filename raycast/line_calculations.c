/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_calculations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 04:08:12 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 04:31:31 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	calc_line_params(int h, double perp_dist,
		t_line_data *line, t_parsed_data *pd)
{
	line->height = (int)((double)h / perp_dist);
	line->draw_start = -line->height / 2 + (h / 2 + (int)pd->player.pitch);
	if (line->draw_start < 0)
		line->draw_start = 0;
	line->draw_end = line->height / 2 + (h / 2 + (int)pd->player.pitch);
	if (line->draw_end >= h)
		line->draw_end = h - 1;
}

void	draw_column(t_parsed_data *pd, t_column_data *col)
{
	t_line_data	line;
	char		tile;

	tile = '0';
	calc_line_params(col->h, col->perp_dist, &line, pd);
	draw_ceiling(pd, col->x, line.draw_start, col->h / 2);
	if (col->map.y >= 0 && col->map.y < 99999)
	{
		if (pd->map_grid[col->map.y] && col->map.x >= 0)
			tile = pd->map_grid[col->map.y][col->map.x];
	}
	else
	{
		if (pd->map_grid[col->map.y] && pd->map_grid[col->map.y][col->map.x])
			tile = pd->map_grid[col->map.y][col->map.x];
	}
	if (tile == 'D')
		draw_door_column(pd, col, &line);
	else
		draw_textured_column(pd, col, &line);
	draw_floor(pd, col->x, line.draw_end, col->h / 2);
}
