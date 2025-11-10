/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_health_ui.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 02:42:57 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/10 02:56:03 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

static void	load_oussmac_health_background(t_parsed_data *pd)
{
	pd->game_ui.health_bg.txtr = mlx_load_png(HP_OUSSMAC);
	if (!pd->game_ui.health_bg.txtr)
		ui_error();
	pd->game_ui.health_bg.img = mlx_texture_to_image(pd->mlx,
			pd->game_ui.health_bg.txtr);
	if (!pd->game_ui.health_bg.img
		|| mlx_image_to_window(pd->mlx, pd->game_ui.health_bg.img,
			HBAR_BG_X, HBAR_BG_Y) == -1)
		mind_free_all(EXIT_FAILURE);
}

static void	load_health_background(t_parsed_data *pd)
{
	if (pd->player.character == JESSE)
	{
		pd->game_ui.health_bg.txtr = mlx_load_png(HP_JESSE);
		if (!pd->game_ui.health_bg.txtr)
			ui_error();
		pd->game_ui.health_bg.img = mlx_texture_to_image(pd->mlx,
				pd->game_ui.health_bg.txtr);
		if (!pd->game_ui.health_bg.img || mlx_image_to_window(pd->mlx,
				pd->game_ui.health_bg.img, HBAR_BG_X, HBAR_BG_Y) == -1)
			mind_free_all(EXIT_FAILURE);
	}
	else if (pd->player.character == CHORUS)
	{
		pd->game_ui.health_bg.txtr = mlx_load_png(HP_CHORUS);
		if (!pd->game_ui.health_bg.txtr)
			ui_error();
		pd->game_ui.health_bg.img = mlx_texture_to_image(pd->mlx,
				pd->game_ui.health_bg.txtr);
		if (!pd->game_ui.health_bg.img
			|| mlx_image_to_window(pd->mlx, pd->game_ui.health_bg.img,
				HBAR_BG_X, HBAR_BG_Y) == -1)
			mind_free_all(EXIT_FAILURE);
	}
	else if (pd->player.character == OUSSMAC)
		load_oussmac_health_background(pd);
}

static void	delete_health_textures(t_parsed_data *pd)
{
	if (pd->game_ui.health.txtr)
	{
		mlx_delete_texture(pd->game_ui.health.txtr);
		pd->game_ui.health.txtr = NULL;
	}
	if (pd->game_ui.health_bg.txtr)
	{
		mlx_delete_texture(pd->game_ui.health_bg.txtr);
		pd->game_ui.health_bg.txtr = NULL;
	}
}

void	setup_health_ui(t_parsed_data *pd)
{
	load_health_background(pd);
	pd->game_ui.health.txtr = mlx_load_png(HEALTH_BAR);
	if (!pd->game_ui.health.txtr)
		ui_error();
	pd->game_ui.health.img = mlx_texture_to_image(pd->mlx,
			pd->game_ui.health.txtr);
	if (!pd->game_ui.health.img
		|| mlx_image_to_window(pd->mlx, pd->game_ui.health.img,
			HBAR_X, HBAR_Y) == -1)
		mind_free_all(EXIT_FAILURE);
	delete_health_textures(pd);
}

void	set_gun_stats(t_parsed_data *pd)
{
	if (pd->player.gun.type == JESSE_SLINGER)
	{
		pd->player.gun.ammo = 1;
		pd->player.gun.max_ammo = 1;
		pd->player.gun.damage = 45;
	}
	else if (pd->player.gun.type == CHORUS_MP42)
	{
		pd->player.gun.ammo = 40;
		pd->player.gun.max_ammo = 40;
		pd->player.gun.damage = 12;
	}
	else if (pd->player.gun.type == OUSSMAC_37MM)
	{
		pd->player.gun.ammo = 7;
		pd->player.gun.max_ammo = 7;
		pd->player.gun.damage = 20;
	}
}
