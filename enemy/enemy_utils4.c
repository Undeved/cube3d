/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 01:12:06 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 03:39:04 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

bool	all_enemies_dead(t_parsed_data *pd)
{
	int	i;

	if (!pd || !pd->enemies || pd->enemy_count == 0)
		return (false);
	i = 0;
	while (i < pd->enemy_count)
	{
		if (!pd->enemies[i].dead)
			return (false);
		i++;
	}
	return (true);
}

uint32_t	tint_with_red(uint32_t color, float red_percentage)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	r = r + (uint8_t)((149 - r) * red_percentage);
	g = g + (uint8_t)((6 - g) * red_percentage);
	b = b + (uint8_t)((6 - b) * red_percentage);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

void	set_death_frame(t_enemy *enemy)
{
	if (enemy->death_anim_frame == 1)
	{
		enemy->anim_img = enemy->death2->img;
		enemy->is_highlighted = false;
	}
	else if (enemy->death_anim_frame == 2)
		enemy->anim_img = enemy->death2->img;
}

double	calculate_distance_to_player(t_enemy *enemy, t_parsed_data *pd)
{
	double	dx;
	double	dy;
	double	distance;

	dx = enemy->b_pos.x - pd->player.bpos.x;
	dy = enemy->b_pos.y - pd->player.bpos.y;
	distance = sqrt(dx * dx + dy * dy);
	return (distance);
}

int	calculate_new_direction(int current_dir_index)
{
	int	turn_direction;
	int	new_dir_index;

	if (ft_rand() % 2 == 0)
		turn_direction = -1;
	else
		turn_direction = 1;
	new_dir_index = (current_dir_index + turn_direction + 4) % 4;
	return (new_dir_index);
}
