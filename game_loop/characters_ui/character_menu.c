/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:46:52 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/09 22:48:09 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

static void	render_ch_button_index(t_parsed_data *pd)
{
	pd->chars_menu.b_jesse.hoverd = false;
	pd->chars_menu.b_chorus.hoverd = false;
	pd->chars_menu.b_oussmac.hoverd = false;
	if (pd->chars_menu.button_index == 0)
		pd->chars_menu.b_jesse.hoverd = true;
	else if (pd->chars_menu.button_index == 1)
		pd->chars_menu.b_chorus.hoverd = true;
	else if (pd->chars_menu.button_index == 2)
		pd->chars_menu.b_oussmac.hoverd = true;
}

static void	jesse_button_state(t_parsed_data *pd)
{
	if (pd->chars_menu.b_jesse.hoverd)
	{
		pd->chars_menu.b_jesse_hv.img->enabled = true;
		pd->chars_menu.b_jesse.img->enabled = false;
	}
	else
	{
		pd->chars_menu.b_jesse.img->enabled = true;
		pd->chars_menu.b_jesse_hv.img->enabled = false;
	}
}

static void	update_ch_button_state(t_parsed_data *pd)
{
	render_ch_button_index(pd);
	jesse_button_state(pd);
	if (pd->chars_menu.b_chorus.hoverd)
	{
		pd->chars_menu.b_chorus_hv.img->enabled = true;
		pd->chars_menu.b_chorus.img->enabled = false;
	}
	else
	{
		pd->chars_menu.b_chorus.img->enabled = true;
		pd->chars_menu.b_chorus_hv.img->enabled = false;
	}
	if (pd->chars_menu.b_oussmac.hoverd)
	{
		pd->chars_menu.b_oussmac_hv.img->enabled = true;
		pd->chars_menu.b_oussmac.img->enabled = false;
	}
	else
	{
		pd->chars_menu.b_oussmac.img->enabled = true;
		pd->chars_menu.b_oussmac_hv.img->enabled = false;
	}
}

static void	update_selection(t_parsed_data *pd)
{
	if (!pd->chars_menu.selected.img->enabled)
		pd->chars_menu.selected.img->enabled = true;
	if (pd->chars_menu.select_index == JESSE
		&& pd->chars_menu.selected.img->instances->x != SELECT_JESSE_X)
		pd->chars_menu.selected.img->instances->x = SELECT_JESSE_X;
	else if (pd->chars_menu.select_index == CHORUS
		&& pd->chars_menu.selected.img->instances->x != SELECT_CHORUS_X)
		pd->chars_menu.selected.img->instances->x = SELECT_CHORUS_X;
	else if (pd->chars_menu.select_index == OUSSMAC
		&& pd->chars_menu.selected.img->instances->x != SELECT_OUSSMAC_X)
		pd->chars_menu.selected.img->instances->x = SELECT_OUSSMAC_X;
}

void	characters_menu(t_parsed_data *pd)
{
	if (pd->level.game_started || pd->ui_index != 1)
		return ;
	update_selection(pd);
	update_ch_button_state(pd);
}
