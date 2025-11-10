/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_textures_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 03:08:32 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/10 03:09:00 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	delete_door_wall_textures(t_parsed_data *pd)
{
	if (pd->txtr_ea.img)
		mlx_delete_image(pd->mlx, pd->txtr_ea.img);
	if (pd->txtr_ea.txtr)
		mlx_delete_texture(pd->txtr_ea.txtr);
	if (pd->txtr_no.img)
		mlx_delete_image(pd->mlx, pd->txtr_no.img);
	if (pd->txtr_no.txtr)
		mlx_delete_texture(pd->txtr_no.txtr);
	if (pd->txtr_so.img)
		mlx_delete_image(pd->mlx, pd->txtr_so.img);
	if (pd->txtr_so.txtr)
		mlx_delete_texture(pd->txtr_so.txtr);
	if (pd->txtr_we.img)
		mlx_delete_image(pd->mlx, pd->txtr_we.img);
	if (pd->txtr_we.txtr)
		mlx_delete_texture(pd->txtr_we.txtr);
	if (pd->door_txt.img)
		mlx_delete_image(pd->mlx, pd->door_txt.img);
	if (pd->door_txt.txtr)
		mlx_delete_texture(pd->door_txt.txtr);
}

static void	delete_game_ui_helper(t_parsed_data *pd)
{
	if (pd->game_ui.health_bg.img)
		mlx_delete_image(pd->mlx, pd->game_ui.health_bg.img);
	if (pd->game_ui.health_bg.txtr)
		mlx_delete_texture(pd->game_ui.health_bg.txtr);
	if (pd->game_ui.game_over.img)
		mlx_delete_image(pd->mlx, pd->game_ui.game_over.img);
	if (pd->game_ui.game_over.txtr)
		mlx_delete_texture(pd->game_ui.game_over.txtr);
	if (pd->game_ui.game_won.img)
		mlx_delete_image(pd->mlx, pd->game_ui.game_won.img);
	if (pd->game_ui.game_won.txtr)
		mlx_delete_texture(pd->game_ui.game_won.txtr);
}

void	delete_game_ui_textures(t_parsed_data *pd)
{
	if (pd->game_ui.gun.img)
		mlx_delete_image(pd->mlx, pd->game_ui.gun.img);
	if (pd->game_ui.gun.txtr)
		mlx_delete_texture(pd->game_ui.gun.txtr);
	if (pd->game_ui.gun_aim.img)
		mlx_delete_image(pd->mlx, pd->game_ui.gun_aim.img);
	if (pd->game_ui.gun_aim.txtr)
		mlx_delete_texture(pd->game_ui.gun_aim.txtr);
	if (pd->game_ui.no_ammo.img)
		mlx_delete_image(pd->mlx, pd->game_ui.no_ammo.img);
	if (pd->game_ui.no_ammo.txtr)
		mlx_delete_texture(pd->game_ui.no_ammo.txtr);
	if (pd->game_ui.health.img)
		mlx_delete_image(pd->mlx, pd->game_ui.health.img);
	if (pd->game_ui.health.txtr)
		mlx_delete_texture(pd->game_ui.health.txtr);
}

static void	delete_characters_ui_textures_helper(t_parsed_data *pd)
{
	if (pd->chars_menu.b_oussmac.img)
		mlx_delete_image(pd->mlx, pd->chars_menu.b_oussmac.img);
	if (pd->chars_menu.b_oussmac.txtr)
		mlx_delete_texture(pd->chars_menu.b_oussmac.txtr);
	if (pd->chars_menu.b_jesse_hv.img)
		mlx_delete_image(pd->mlx, pd->chars_menu.b_jesse_hv.img);
	if (pd->chars_menu.b_jesse_hv.txtr)
		mlx_delete_texture(pd->chars_menu.b_jesse_hv.txtr);
	if (pd->chars_menu.b_chorus_hv.img)
		mlx_delete_image(pd->mlx, pd->chars_menu.b_chorus_hv.img);
	if (pd->chars_menu.b_chorus_hv.txtr)
		mlx_delete_texture(pd->chars_menu.b_chorus_hv.txtr);
	if (pd->chars_menu.b_oussmac_hv.img)
		mlx_delete_image(pd->mlx, pd->chars_menu.b_oussmac_hv.img);
	if (pd->chars_menu.b_oussmac_hv.txtr)
		mlx_delete_texture(pd->chars_menu.b_oussmac_hv.txtr);
}

void	delete_characters_ui_textures(t_parsed_data *pd)
{
	if (pd->chars_menu.bg.img)
		mlx_delete_image(pd->mlx, pd->chars_menu.bg.img);
	if (pd->chars_menu.bg.txtr)
		mlx_delete_texture(pd->chars_menu.bg.txtr);
	if (pd->chars_menu.selected.img)
		mlx_delete_image(pd->mlx, pd->chars_menu.selected.img);
	if (pd->chars_menu.selected.txtr)
		mlx_delete_texture(pd->chars_menu.selected.txtr);
	if (pd->chars_menu.b_jesse.img)
		mlx_delete_image(pd->mlx, pd->chars_menu.b_jesse.img);
	if (pd->chars_menu.b_jesse.txtr)
		mlx_delete_texture(pd->chars_menu.b_jesse.txtr);
	if (pd->chars_menu.b_chorus.img)
		mlx_delete_image(pd->mlx, pd->chars_menu.b_chorus.img);
	if (pd->chars_menu.b_chorus.txtr)
		mlx_delete_texture(pd->chars_menu.b_chorus.txtr);
	delete_characters_ui_textures_helper(pd);
}
