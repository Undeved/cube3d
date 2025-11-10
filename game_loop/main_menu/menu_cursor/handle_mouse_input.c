/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 05:05:02 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/10 05:18:00 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"

static bool	within_bounds(t_pos m_pos, t_pos img_pos, int width, int height)
{
	(void)width;
	(void)height;
	if (m_pos.x < (img_pos.x + width - TRN_OFST)
		&& m_pos.y < (img_pos.y + height - TRN_OFST)
		&& m_pos.x >= (img_pos.x + TRN_OFST)
		&& m_pos.y >= (img_pos.y + TRN_OFST))
		return (true);
	return (false);
}

static void	main_menu_buttons(double xpos, double ypos, t_parsed_data *pd)
{
	if (within_bounds((t_pos){xpos, ypos},
		(t_pos){START_BUTTON_X,
		START_BUTTON_Y},
		pd->menu.b_start.img->width,
		pd->menu.b_start.img->height))
	{
		pd->menu.button_index = 0;
	}
	else if (within_bounds((t_pos){xpos, ypos},
		(t_pos){CHARS_BUTTON_X,
		CHARS_BUTTON_Y},
		pd->menu.b_chars.img->width,
		pd->menu.b_chars.img->height))
	{
		pd->menu.button_index = 1;
	}
	else if (within_bounds((t_pos){xpos, ypos},
		(t_pos){EXIT_BUTTON_X,
		EXIT_BUTTON_Y},
		pd->menu.b_exit.img->width,
		pd->menu.b_exit.img->height))
	{
		pd->menu.button_index = 2;
	}
}

static void	characters_buttons(double xpos, double ypos, t_parsed_data *pd)
{
	if (within_bounds((t_pos){xpos, ypos},
		(t_pos){JESSE_X,
		JESSE_Y},
		pd->chars_menu.b_jesse.img->width,
		pd->chars_menu.b_jesse.img->height))
	{
		pd->chars_menu.button_index = 0;
	}
	else if (within_bounds((t_pos){xpos, ypos},
		(t_pos){CHORUS_X,
		CHORUS_Y},
		pd->chars_menu.b_chorus.img->width,
		pd->chars_menu.b_chorus.img->height))
	{
		pd->chars_menu.button_index = 1;
	}
	else if (within_bounds((t_pos){xpos, ypos},
		(t_pos){OUSSMAC_X,
		OUSSMAC_Y},
		pd->chars_menu.b_oussmac.img->width,
		pd->chars_menu.b_oussmac.img->height))
	{
		pd->chars_menu.button_index = 2;
	}
}

static void	button_events(double xpos, double ypos, t_parsed_data *pd)
{
	if (pd->ui_index == 0)
		main_menu_buttons(xpos, ypos, pd);
	else if (pd->ui_index == 1)
		characters_buttons(xpos, ypos, pd);
}

void	handle_mouse_input(double xpos, double ypos, void *param)
{
	t_parsed_data	*pd;

	pd = param;
	button_events(xpos, ypos, pd);
}
