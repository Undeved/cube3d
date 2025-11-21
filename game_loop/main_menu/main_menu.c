/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 04:11:37 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/21 12:55:12 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

static void	render_button_index(t_parsed_data *pd)
{
	pd->menu.b_start.hoverd = false;
	pd->menu.b_chars.hoverd = false;
	pd->menu.b_exit.hoverd = false;
	if (pd->menu.button_index == 0)
		pd->menu.b_start.hoverd = true;
	else if (pd->menu.button_index == 1)
		pd->menu.b_chars.hoverd = true;
	else if (pd->menu.button_index == 2)
		pd->menu.b_exit.hoverd = true;
}

static void	exit_chars_button_state(t_parsed_data *pd)
{
	if (pd->menu.b_chars.hoverd)
	{
		pd->menu.b_chars_hv.img->enabled = true;
		pd->menu.b_chars.img->enabled = false;
	}
	else
	{
		pd->menu.b_chars.img->enabled = true;
		pd->menu.b_chars_hv.img->enabled = false;
	}
	if (pd->menu.b_exit.hoverd)
	{
		pd->menu.b_exit_hv.img->enabled = true;
		pd->menu.b_exit.img->enabled = false;
	}
	else
	{
		pd->menu.b_exit.img->enabled = true;
		pd->menu.b_exit_hv.img->enabled = false;
	}
}

static void	update_button_state(t_parsed_data *pd)
{
	render_button_index(pd);
	if (pd->menu.b_start.hoverd)
	{
		pd->menu.b_start_hv.img->enabled = true;
		pd->menu.b_start.img->enabled = false;
	}
	else
	{
		pd->menu.b_start.img->enabled = true;
		pd->menu.b_start_hv.img->enabled = false;
	}
	exit_chars_button_state(pd);
}

void	main_menu(t_parsed_data *pd)
{
	if (pd->level.game_started || pd->ui_index != 0)
		return ;
	update_button_state(pd);
}

void	characters_trigger_click(t_parsed_data *pd)
{
	play_sound_once(pd, "sound/click.mp3");
	if (pd->chars_menu.button_index == JESSE)
		pd->chars_menu.select_index = JESSE;
	else if (pd->chars_menu.button_index == CHORUS)
		pd->chars_menu.select_index = CHORUS;
	else if (pd->chars_menu.button_index == OUSSMAC)
		pd->chars_menu.select_index = OUSSMAC;
}
