/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_calculations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 03:49:40 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 03:51:58 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	set_x_step(t_bpos pos, t_pos map, t_bdir ray_dir, t_step_data *data)
{
	if (ray_dir.x < 0.0)
	{
		data->step->x = -1;
		data->side_dist->x = (pos.x - (double)map.x) * data->delta_dist.x;
	}
	else
	{
		data->step->x = 1;
		data->side_dist->x = ((double)map.x + 1.0 - pos.x) * data->delta_dist.x;
	}
}

void	set_y_step(t_bpos pos, t_pos map, t_bdir ray_dir, t_step_data *data)
{
	if (ray_dir.y < 0.0)
	{
		data->step->y = -1;
		data->side_dist->y = (pos.y - (double)map.y) * data->delta_dist.y;
	}
	else
	{
		data->step->y = 1;
		data->side_dist->y = ((double)map.y + 1.0 - pos.y) * data->delta_dist.y;
	}
}

void	init_step_and_sidedist(t_bpos player, t_step_data *data)
{
	set_x_step(player, data->map, data->ray_dir, data);
	set_y_step(player, data->map, data->ray_dir, data);
}

void	update_x_side(t_dda_data *data)
{
	data->side_dist->x += data->delta_dist.x;
	data->map->x += data->step.x;
	*data->side = 0;
}

void	update_y_side(t_dda_data *data)
{
	data->side_dist->y += data->delta_dist.y;
	data->map->y += data->step.y;
	*data->side = 1;
}
