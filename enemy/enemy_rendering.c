/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 01:13:48 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 03:20:07 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_sorted_enemies(t_parsed_data *pd, t_enemy_draw_data *draw_data,
		int draw_count)
{
	int	i;
	int	horizon;

	i = 0;
	horizon = HEIGHT / 2 + (int)pd->player.pitch;
	while (i < draw_count)
	{
		draw_single_enemy(pd, &draw_data[i], horizon);
		i++;
	}
}

void	draw_enemies(t_parsed_data *pd)
{
	int					draw_count;
	t_enemy_draw_data	draw_data[MAX_ENEMIES];

	if (!pd->enemies || pd->enemy_count == 0)
		return ;
	draw_count = collect_and_sort_enemies_small(pd, draw_data);
	handle_shooting_once(pd, draw_data, draw_count);
	update_all_death_animations(pd);
	draw_sorted_enemies(pd, draw_data, draw_count);
}
