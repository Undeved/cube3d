/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_line_of_sight.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 01:14:03 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 02:32:54 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

bool	check_line_path(t_parsed_data *pd, t_bpos start,
		t_bpos step, double max_dist)
{
	double	dist;
	int		map_x;
	int		map_y;

	dist = 0.0;
	while (dist < max_dist)
	{
		start.x += step.x;
		start.y += step.y;
		dist += sqrt(step.x * step.x + step.y * step.y);
		if (dist >= max_dist)
			break ;
		map_x = (int)start.x;
		map_y = (int)start.y;
		if (map_y < 0 || map_y >= pd->level.max_y)
			return (false);
		if (map_x < 0 || map_x >= pd->level.max_x)
			return (false);
		if (pd->map_grid[map_y][map_x] == '1'
			|| pd->map_grid[map_y][map_x] == 'D')
			return (false);
	}
	return (true);
}

bool	has_line_of_sight(t_parsed_data *pd, t_bpos start, t_bpos end)
{
	t_bpos	delta;
	t_bpos	step;
	double	max_dist;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	max_dist = sqrt(delta.x * delta.x + delta.y * delta.y);
	step.x = delta.x / (max_dist * 4.0);
	step.y = delta.y / (max_dist * 4.0);
	return (check_line_path(pd, start, step, max_dist));
}
