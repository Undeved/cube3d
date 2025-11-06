/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 04:03:51 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 04:52:46 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	set_ray_dir(t_ray_dir_data *data)
{
	double	camera_x;

	camera_x = 2.0 * data->x / (double)data->w - 1.0;
	data->ray_dir->x = data->pl->bdir.x + -data->cam->dir.x * camera_x;
	data->ray_dir->y = data->pl->bdir.y + -data->cam->dir.y * camera_x;
}

void	sort_medkits_by_distance(t_medkit_draw_data *draw_data, int draw_count)
{
	int					i;
	int					j;
	t_medkit_draw_data	tmp;

	i = 0;
	while (i < draw_count - 1)
	{
		j = i + 1;
		while (j < draw_count)
		{
			if (draw_data[i].distance < draw_data[j].distance)
			{
				tmp = draw_data[i];
				draw_data[i] = draw_data[j];
				draw_data[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
