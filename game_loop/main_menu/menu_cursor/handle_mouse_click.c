/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_click.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 04:57:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/10 05:01:48 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"

long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	update_ui_anim(t_ui_anim *anim)
{
	long	now;

	if (!anim->active)
		return ;
	now = current_time_ms();
	if (now - anim->last_frame_time >= anim->frame_delay)
	{
		anim->current++;
		if (anim->current >= anim->frame_count)
		{
			anim->current = 0;
			anim->active = false;
		}
		anim->last_frame_time = now;
	}
}

static void	disbale_all_frames(t_parsed_data *pd)
{
	int	i;

	pd->game_ui.gun.img->enabled = false;
	pd->game_ui.gun_aim.img->enabled = false;
	if (pd->game_ui.no_ammo.img)
		pd->game_ui.no_ammo.img->enabled = false;
	i = 0;
	while (i < pd->player.gun.shoot.frame_count)
		pd->player.gun.shoot.frames[i++].img->enabled = false;
	i = 0;
	while (i < pd->player.gun.reload.frame_count)
		pd->player.gun.reload.frames[i++].img->enabled = false;
}

void	render_gun(t_parsed_data *pd)
{
	t_gun	*gun;

	gun = &pd->player.gun;
	disbale_all_frames(pd);
	if (gun->shoot.active)
		gun->shoot.frames[gun->shoot.current].img->enabled = true;
	else if (gun->reload.active)
		gun->reload.frames[gun->reload.current].img->enabled = true;
	else if (gun->aiming)
		pd->game_ui.gun_aim.img->enabled = true;
	else
	{
		if (pd->player.character == JESSE)
		{
			if (pd->player.gun.ammo > 0)
				pd->game_ui.gun.img->enabled = true;
			else
			{
				if (pd->game_ui.no_ammo.img)
					pd->game_ui.no_ammo.img->enabled = true;
			}
		}
		else
			pd->game_ui.gun.img->enabled = true;
	}
}

void	handle_mouse_click(mouse_key_t button,
	action_t action, modifier_key_t mods, void *param)
{
	t_parsed_data	*pd;

	pd = param;
	(void)mods;
	game_mouse_input(button, action, mods, pd);
	if (pd->level.game_started || pd->ui_index == 2)
		return ;
	if (action == MLX_PRESS)
	{
		if (button == MLX_MOUSE_BUTTON_LEFT)
		{
			pd->mouse_clicked = true;
			if (pd->ui_index == 0)
				menu_trigger_click(pd);
			else if (pd->ui_index == 1)
				characters_trigger_click(pd);
		}
	}
	else
	{
		if (button == MLX_MOUSE_BUTTON_LEFT)
			pd->mouse_clicked = false;
	}
}
