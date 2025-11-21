/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:01:29 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/21 13:37:03 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

static void play_walking_sound(t_parsed_data *pd)
{
	static long	last_played = 0;
	long			now;

	now = current_time_ms();
	if ((pd->keys.pressed[MLX_KEY_W]
			|| pd->keys.pressed[MLX_KEY_A]
			|| pd->keys.pressed[MLX_KEY_S]
			|| pd->keys.pressed[MLX_KEY_D])
		&& now - last_played >= 400)
	{
		// based on move speed
		if (pd->player.move_speed > SPEED)
			play_sound_once(pd, "sound/sprint_walk.mp3");
		else
			play_sound_once(pd, "sound/walk.mp3");
		last_played = now;
	}
}

void	update_player_movement(t_parsed_data *pd)
{
	// pitch
	// play sound whilest walking based on x and y movement difference
	play_walking_sound(pd);
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
