/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 03:51:00 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 04:58:16 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	compute_delta_dist(t_bdir ray_dir, t_bpos *delta_dist)
{
	if (ray_dir.x == 0.0)
		delta_dist->x = 1000000.0;
	else
		delta_dist->x = fabs(1.0 / ray_dir.x);
	if (ray_dir.y == 0.0)
		delta_dist->y = 1000000.0;
	else
		delta_dist->y = fabs(1.0 / ray_dir.y);
}

void	setup_door_stepping(t_door_column *dc)
{
	dc->step = (double)dc->tex_h / (double)dc->line->height;
	dc->tex_pos = ((double)dc->line->draw_start
			- ((double)dc->screen_h / 2.0 + (double)dc->pd->player.pitch)
			+ (double)dc->line->height / 2.0) * dc->step;
}

mlx_texture_t	*get_door_texture(t_parsed_data *pd)
{
	if (!pd)
		return (NULL);
	return (pd->door_txt.txtr);
}

int	medkit_drop_chance(t_enemy_type type)
{
	if (type == FT_SKIN_WALKER)
		return (30);
	else if (type == MEMORY_LEAK)
		return (50);
	else if (type == SEGV)
		return (69);
	return (25);
}

bool	should_drop_medkit(t_enemy_type type)
{
	int	r;
	int	chance;

	chance = medkit_drop_chance(type);
	r = ft_rand() % 100;
	return (r < chance);
}
