/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 03:12:50 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/10 13:07:28 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

static void	precise_direction(t_parsed_data *pd)
{
	if (pd->player.dir == 'N')
	{
		pd->player.bdir.x = 0;
		pd->player.bdir.y = -1;
	}
	else if (pd->player.dir == 'E')
	{
		pd->player.bdir.x = 1;
		pd->player.bdir.y = 0;
	}
	else if (pd->player.dir == 'S')
	{
		pd->player.bdir.x = 0;
		pd->player.bdir.y = 1;
	}
	else if (pd->player.dir == 'W')
	{
		pd->player.bdir.x = -1;
		pd->player.bdir.y = 0;
	}
}

static void	init_key_flags(t_parsed_data *pd)
{
	int	i;

	i = 0;
	while (i < KEYS_NUMBER)
		pd->keys.pressed[i++] = false;
}

void	init_precise_data(t_parsed_data *pd)
{
	pd->player.bpos.x = pd->player.pos.x + NUDGE_FROM_WALL;
	pd->player.bpos.y = pd->player.pos.y + NUDGE_FROM_WALL;
	pd->player.camera_plane.pos.x = pd->player.bdir.x;
	pd->player.camera_plane.pos.y = pd->player.bdir.y;
	pd->player.camera_plane.dir.x = pd->player.bdir.y;
	pd->player.camera_plane.dir.y = -pd->player.bdir.x;
	pd->level.game_started = false;
	pd->mouse_clicked = false;
	pd->player.pitch = 0;
	pd->player.health = PLAYER_HEALTH;
	pd->game_ui.health.img = NULL;
	pd->player.gun.ammo = 0;
	pd->player.gun.damage = DAMAGE;
	pd->player.is_shooting = false;
	pd->medkits = NULL;
	pd->player.last_killer = NULL;
	precise_direction(pd);
	init_key_flags(pd);
}

void	init_medkits(t_parsed_data *pd)
{
	int	i;

	pd->max_medkits = MAX_ENEMIES;
	pd->medkits = allocate_gc(malloc(sizeof(t_med_kit) * pd->max_medkits));
	pd->medkit_count = 0;
	pd->medkit.txtr = mlx_load_png(MEDKIT);
	if (!pd->medkit.txtr)
	{
		pd->medkits = NULL;
		ui_error();
	}
	pd->medkit.img = mlx_texture_to_image(pd->mlx, pd->medkit.txtr);
	if (!pd->medkit.img)
	{
		pd->medkits = NULL;
		ui_error();
	}
	mlx_delete_texture(pd->medkit.txtr);
	pd->medkit.txtr = NULL;
	i = 0;
	while (i < MAX_ENEMIES)
	{
		pd->medkits[i].img.txtr = NULL;
		pd->medkits[i++].img.img = pd->medkit.img;
	}
}
