/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 01:15:21 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 03:12:09 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	change_enemy_direction(t_enemy *enemy)
{
	double	directions[4][2];
	int		current_dir_index;
	int		new_dir_index;

	directions[0][0] = 0;
	directions[0][1] = 1;
	directions[1][0] = 1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = -1;
	directions[3][0] = -1;
	directions[3][1] = 0;
	current_dir_index = find_current_direction(enemy, directions);
	if (current_dir_index != -1)
	{
		new_dir_index = calculate_new_direction(current_dir_index);
		enemy->dir.x = directions[new_dir_index][0];
		enemy->dir.y = directions[new_dir_index][1];
	}
	else
	{
		new_dir_index = ft_rand() % 4;
		enemy->dir.x = directions[new_dir_index][0];
		enemy->dir.y = directions[new_dir_index][1];
	}
}

bool	circle_intersects_tile(double cx, double cy, double r, t_bpos tile)
{
	double	nx;
	double	ny;
	double	dx;
	double	dy;

	if (cx < tile.x)
		nx = tile.x;
	else if (cx > tile.x + 1.0)
		nx = tile.x + 1.0;
	else
		nx = cx;
	if (cy < tile.y)
		ny = tile.y;
	else if (cy > tile.y + 1.0)
		ny = tile.y + 1.0;
	else
		ny = cy;
	dx = cx - nx;
	dy = cy - ny;
	return (dx * dx + dy * dy < r * r);
}

bool	check_circle_collision(t_parsed_data *pd, double pos[2],
		double radius, int bounds[4])
{
	int		tx;
	char	tile;
	int		ty;
	t_bpos	tile_pos;

	tx = bounds[0];
	while (tx <= bounds[1])
	{
		ty = bounds[2];
		while (ty <= bounds[3])
		{
			tile = pd->map_grid[ty][tx];
			if ((tile == '1' || tile == 'D'))
			{
				tile_pos.x = (double)tx;
				tile_pos.y = (double)ty;
				if (circle_intersects_tile(pos[0], pos[1], radius, tile_pos))
					return (true);
			}
			ty++;
		}
		tx++;
	}
	return (false);
}

bool	is_position_blocked_circle(t_parsed_data *pd, double cx, double cy,
		double radius)
{
	int		bounds[4];
	double	pos[2];

	if (!pd)
		return (true);
	pos[0] = cx;
	pos[1] = cy;
	bounds[0] = (int)floor(cx - radius);
	bounds[1] = (int)floor(cx + radius);
	bounds[2] = (int)floor(cy - radius);
	bounds[3] = (int)floor(cy + radius);
	if (bounds[0] < 0 || bounds[2] < 0
		|| bounds[1] >= pd->level.max_x
		|| bounds[3] >= pd->level.max_y)
		return (true);
	return (check_circle_collision(pd, pos, radius, bounds));
}

bool	is_valid_move_position_circle_global(t_parsed_data *pd,
		double x, double y)
{
	return (!is_position_blocked_circle(pd, x, y, COLLISION_RADIUS));
}
