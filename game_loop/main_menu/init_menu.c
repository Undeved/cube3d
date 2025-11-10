/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 03:57:23 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/10 04:02:42 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	ui_error(void)
{
	print_error("Error\nFailed To Load MENU UI\n");
	mind_free_all(EXIT_FAILURE);
}

static void	init_hovered_versions(t_parsed_data *pd)
{
	pd->menu.b_start_hv.txtr = mlx_load_png(START_BUTTON_PATH_HV);
	pd->menu.b_chars_hv.txtr = mlx_load_png(CHARS_BUTTON_PATH_HV);
	pd->menu.b_exit_hv.txtr = mlx_load_png(EXIT_BUTTON_PATH_HV);
	if (!pd->menu.b_start_hv.txtr || !pd->menu.b_chars_hv.txtr
		|| !pd->menu.b_exit_hv.txtr)
		ui_error();
	pd->menu.b_start_hv.img = mlx_texture_to_image(pd->mlx,
			pd->menu.b_start_hv.txtr);
	if (!pd->menu.b_start_hv.img
		|| mlx_image_to_window(pd->mlx, pd->menu.b_start_hv.img,
			START_BUTTON_X, START_BUTTON_Y))
		mind_free_all(EXIT_FAILURE);
	pd->menu.b_chars_hv.img = mlx_texture_to_image(pd->mlx,
			pd->menu.b_chars_hv.txtr);
	if (!pd->menu.b_chars_hv.img
		|| mlx_image_to_window(pd->mlx, pd->menu.b_chars_hv.img,
			CHARS_BUTTON_X, CHARS_BUTTON_Y))
		mind_free_all(EXIT_FAILURE);
	pd->menu.b_exit_hv.img = mlx_texture_to_image(pd->mlx,
			pd->menu.b_exit_hv.txtr);
	if (!pd->menu.b_exit_hv.img
		|| mlx_image_to_window(pd->mlx, pd->menu.b_exit_hv.img,
			EXIT_BUTTON_X, EXIT_BUTTON_Y))
		mind_free_all(EXIT_FAILURE);
}

static void	init_button_flags(t_parsed_data *pd)
{
	pd->menu.b_start.hoverd = true;
	pd->menu.b_chars.hoverd = false;
	pd->menu.b_exit.hoverd = false;
	pd->menu.b_start_hv.img->enabled = true;
	pd->menu.b_chars_hv.img->enabled = false;
	pd->menu.b_exit_hv.img->enabled = false;
}

static void	init_buttons(t_parsed_data *pd)
{
	pd->menu.b_start.txtr = mlx_load_png(START_BUTTON_PATH);
	pd->menu.b_chars.txtr = mlx_load_png(CHARS_BUTTON_PATH);
	pd->menu.b_exit.txtr = mlx_load_png(EXIT_BUTTON_PATH);
	if (!pd->menu.b_start.txtr || !pd->menu.b_chars.txtr
		|| !pd->menu.b_exit.txtr)
		ui_error();
	pd->menu.b_start.img = mlx_texture_to_image(pd->mlx,
			pd->menu.b_start.txtr);
	if (!pd->menu.b_start.img
		|| mlx_image_to_window(pd->mlx, pd->menu.b_start.img,
			START_BUTTON_X, START_BUTTON_Y - BTN_POP))
		mind_free_all(EXIT_FAILURE);
	pd->menu.b_chars.img = mlx_texture_to_image(pd->mlx,
			pd->menu.b_chars.txtr);
	if (!pd->menu.b_chars.img
		|| mlx_image_to_window(pd->mlx, pd->menu.b_chars.img,
			CHARS_BUTTON_X, CHARS_BUTTON_Y - BTN_POP))
		mind_free_all(EXIT_FAILURE);
	pd->menu.b_exit.img = mlx_texture_to_image(pd->mlx,
			pd->menu.b_exit.txtr);
	if (!pd->menu.b_exit.img
		|| mlx_image_to_window(pd->mlx, pd->menu.b_exit.img,
			EXIT_BUTTON_X, EXIT_BUTTON_Y - BTN_POP))
		mind_free_all(EXIT_FAILURE);
}

void	init_main_menu(t_parsed_data *pd)
{
	pd->menu.bg.txtr = mlx_load_png(MENU_CANVAS_PATH);
	pd->menu.title.txtr = mlx_load_png(MENU_TITLE_PATH);
	if (!pd->menu.bg.txtr || !pd->menu.title.txtr)
		ui_error();
	pd->menu.bg.img = mlx_texture_to_image(pd->mlx, pd->menu.bg.txtr);
	if (!pd->menu.bg.img
		|| mlx_image_to_window(pd->mlx, pd->menu.bg.img, 0, 0) == -1)
		mind_free_all(EXIT_FAILURE);
	pd->menu.title.img = mlx_texture_to_image(pd->mlx, pd->menu.title.txtr);
	if (!pd->menu.title.img || mlx_image_to_window(pd->mlx,
			pd->menu.title.img, TITLE_X, TITLE_Y) == -1)
		mind_free_all(EXIT_FAILURE);
	init_buttons(pd);
	init_hovered_versions(pd);
	init_button_flags(pd);
	pd->menu.button_index = 0;
	pd->ui_index = 0;
}
