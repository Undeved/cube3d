/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:01:29 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/10 08:02:17 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	update_player_movement(t_parsed_data *pd)
{
	player_movement(pd);
	player_rotation(pd);
	player_pitch(pd);
	interact_with_door(pd);
	update_health_ui(pd);
	reload_gun(pd);
}

double	get_move_speed(t_parsed_data *pd, double speed)
{
	double	sprint_mult;
	double	move_speed;

	if (pd->keys.pressed[MLX_KEY_LEFT_SHIFT]
		|| pd->keys.pressed[MLX_KEY_RIGHT_SHIFT])
		sprint_mult = 2.0;
	else
		sprint_mult = 1.0;
	move_speed = speed;
	move_speed *= sprint_mult;
	return (move_speed);
}
