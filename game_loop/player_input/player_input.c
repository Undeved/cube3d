/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 05:31:29 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/16 04:02:41 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	player_pitch(t_parsed_data *pd)
{
	(void)pd;
	if (pd->keys.pressed[MLX_KEY_UP] || pd->mouse.y < (HEIGHT / 2))
	{
		pd->player.pitch += PITCH_SPEED;
		if (pd->player.pitch > MAX_PITCH)
			pd->player.pitch = MAX_PITCH;
	}
	if (pd->keys.pressed[MLX_KEY_DOWN] || pd->mouse.y > (HEIGHT / 2))
	{
		pd->player.pitch -= PITCH_SPEED;
		if (pd->player.pitch < MIN_PITCH)
			pd->player.pitch = MIN_PITCH;
	}
}

void	reload_gun(t_parsed_data *pd)
{
	if (pd->keys.pressed[MLX_KEY_R]
		&& pd->player.gun.ammo < pd->player.gun.max_ammo
		&& !pd->player.gun.reload.active)
	{
		pd->player.gun.reload.active = true;
		pd->player.gun.shoot.active = false;
		pd->player.gun.aiming = false;
		pd->player.gun.ammo = pd->player.gun.max_ammo;
		trigger_reload_anim(pd);
	}
}

bool	cool_down(long usec)
{
	static struct timeval	start = {0};
	struct timeval			current;
	static bool				running = false;
	long					elapsed;

	if (!running)
	{
		gettimeofday(&start, NULL);
		running = true;
		return (false);
	}
	gettimeofday(&current, NULL);
	elapsed = (current.tv_sec - start.tv_sec)
		* 1000000L + (current.tv_usec - start.tv_usec);
	if (elapsed >= usec)
	{
		running = false;
		return (true);
	}
	return (false);
}

void	update_player_data(t_parsed_data *pd)
{
	if (pd->player.health <= 0)
	{
		pd->game_ui.game_over.img->enabled = true;
		pd->player.is_dead = true;
		if (cool_down(0))
		{
			pd->player.health = 0;
			print_death_message(pd, pd->player.last_killer, false);
			mind_free_all(EXIT_SUCCESS);
		}
	}
	if (pd->player.has_won)
	{
		pd->game_ui.game_won.img->enabled = true;
		if (cool_down(0))
		{
			print_comm(GRN"Norminette: [OK], [OK], [OK], [OK], [OK], [OK]\n");
			print_comm("File: You Won.exe"RST"\n");
			mind_free_all(EXIT_SUCCESS);
		}
	}
	mlx_get_mouse_pos(pd->mlx, &pd->mouse.x, &pd->mouse.y);
	update_player_movement(pd);
}

void	handle_player_input(mlx_key_data_t keydata, void *param)
{
	t_parsed_data	*pd;

	pd = param;
	if (keydata.key == MLX_KEY_ESCAPE
		&& keydata.action == MLX_PRESS && pd->ui_index != 1)
	{
		mlx_close_window(pd->mlx);
		return ;
	}
	handle_ui_input(keydata, pd);
	if (!pd->level.game_started)
		return ;
	if (keydata.key >= 0 && keydata.key < KEYS_NUMBER)
	{
		if (keydata.action == MLX_RELEASE)
			pd->keys.pressed[keydata.key] = false;
		else
			pd->keys.pressed[keydata.key] = true;
	}
}
