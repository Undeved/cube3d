/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_doors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 05:00:59 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/09 05:12:18 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

bool	is_door(char c)
{
	if (c == 'D')
		return (true);
	return (false);
}

static bool	is_clear(t_parsed_data *pd, int x, int y)
{
	if (x < 0 || y < 0 || y >= pd->level.max_y || x >= pd->level.max_x)
		return (false);
	return (pd->map_grid[y][x] == '0' || pd->map_grid[y][x] == 'X'
		|| pd->map_grid[y][x] == 'Y' || pd->map_grid[y][x] == 'Z');
}

bool	only_two_clear_sides(t_parsed_data *pd, int x, int y)
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;

	up = is_clear(pd, x, y - 1);
	down = is_clear(pd, x, y + 1);
	left = is_clear(pd, x - 1, y);
	right = is_clear(pd, x + 1, y);
	if (up && down && !left && !right)
		return (true);
	if (left && right && !up && !down)
		return (true);
	return (false);
}

bool	validate_door(t_parsed_data *pd, int x, int y)
{
	if (x <= 0 || x >= pd->level.max_x || y <= 0 || y >= pd->level.max_y)
		return (false);
	if (pd->map_grid[y][x + 1] == '1' || pd->map_grid[y][x - 1] == '1')
	{
		if (pd->map_grid[y + 1][x] != '0' && pd->map_grid[y - 1][x] != '0')
			return (false);
	}
	else if (pd->map_grid[y + 1][x] == '1' || pd->map_grid[y - 1][x] == '1')
	{
		if (pd->map_grid[y][x + 1] != '0' && pd->map_grid[y][x - 1] != '0')
			return (false);
	}
	if (!only_two_clear_sides(pd, x, y))
		return (false);
	return (true);
}
