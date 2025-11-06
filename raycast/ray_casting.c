/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 04:08:43 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 04:52:27 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	init_ray_data(t_ray_data *ray, t_player *pl, int x, int w)
{
	t_ray_dir_data	ray_dir_data;

	ray_dir_data.pl = pl;
	ray_dir_data.cam = &pl->camera_plane;
	ray_dir_data.x = x;
	ray_dir_data.w = w;
	ray_dir_data.ray_dir = &ray->ray_dir;
	set_ray_dir(&ray_dir_data);
	ray->player_pos.x = pl->bpos.x;
	ray->player_pos.y = pl->bpos.y;
	ray->map.x = (int)ray->player_pos.x;
	ray->map.y = (int)ray->player_pos.y;
}

void	init_dda_data(t_parsed_data *pd, t_ray_data *ray, t_dda_data *dda_data)
{
	dda_data->pd = pd;
	dda_data->map = &ray->map;
	dda_data->side_dist = &ray->side_dist;
	dda_data->delta_dist = ray->delta_dist;
	dda_data->step = ray->step;
	dda_data->side = &ray->side;
}

void	init_perp_and_col_data(t_parsed_data *pd, int x, t_ray_data *ray,
		t_column_data *col_data)
{
	t_perp_data	perp_data;

	perp_data.map = ray->map;
	perp_data.pos = ray->player_pos;
	perp_data.step = ray->step;
	perp_data.ray_dir = ray->ray_dir;
	perp_data.side = ray->side;
	col_data->pd = pd;
	col_data->x = x;
	col_data->h = pd->screen->height;
	col_data->perp_dist = compute_perp_wall_dist(&perp_data);
	col_data->side = ray->side;
	col_data->ray_dir = ray->ray_dir;
	col_data->player_pos = ray->player_pos;
	col_data->map = ray->map;
}

void	cast_single_ray(t_parsed_data *pd, int x)
{
	t_ray_data		ray;
	t_step_data		step_data;
	t_dda_data		dda_data;
	t_column_data	col_data;

	init_ray_data(&ray, &pd->player, x, pd->screen->width);
	compute_delta_dist(ray.ray_dir, &ray.delta_dist);
	step_data.ray_dir = ray.ray_dir;
	step_data.delta_dist = ray.delta_dist;
	step_data.map = ray.map;
	step_data.step = &ray.step;
	step_data.side_dist = &ray.side_dist;
	init_step_and_sidedist(ray.player_pos, &step_data);
	init_dda_data(pd, &ray, &dda_data);
	perform_dda(pd, &dda_data);
	init_perp_and_col_data(pd, x, &ray, &col_data);
	pd->zbuffer[x] = col_data.perp_dist;
	draw_column(pd, &col_data);
}

void	raycast_render(t_parsed_data *pd)
{
	int	x;
	int	w;

	w = pd->screen->width;
	x = 0;
	while (x < w)
	{
		cast_single_ray(pd, x);
		x++;
	}
	draw_enemies(pd);
}
