/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 04:08:56 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 04:54:25 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

bool	is_wall_hit(t_parsed_data *pd, t_pos map)
{
	if (map.y < 0 || !pd->map_grid[map.y])
		return (false);
	if (map.x < 0 || !pd->map_grid[map.y][map.x])
		return (false);
	return (pd->map_grid[map.y][map.x] != '0' &&
			pd->map_grid[map.y][map.x] != 'O');
}

void	perform_dda(t_parsed_data *pd, t_dda_data *data)
{
	while (1)
	{
		if (data->side_dist->x < data->side_dist->y)
			update_x_side(data);
		else
			update_y_side(data);
		if (is_wall_hit(pd, *data->map))
			break ;
	}
}

double	calc_x_perp_dist(t_pos map, t_bpos pos, t_pos step, t_bdir ray_dir)
{
	if (ray_dir.x == 0.0)
		return (0.000001);
	return (((double)map.x - pos.x + (1 - step.x) / 2.0) / ray_dir.x);
}

double	calc_y_perp_dist(t_pos map, t_bpos pos, t_pos step, t_bdir ray_dir)
{
	if (ray_dir.y == 0.0)
		return (0.000001);
	return (((double)map.y - pos.y + (1 - step.y) / 2.0) / ray_dir.y);
}

double	compute_perp_wall_dist(t_perp_data *data)
{
	double	perp_wall_dist;

	if (data->side == 0)
		perp_wall_dist = calc_x_perp_dist(data->map, data->pos,
				data->step, data->ray_dir);
	else
		perp_wall_dist = calc_y_perp_dist(data->map, data->pos,
				data->step, data->ray_dir);
	if (perp_wall_dist <= 0.0)
		perp_wall_dist = 0.000001;
	return (perp_wall_dist);
}
