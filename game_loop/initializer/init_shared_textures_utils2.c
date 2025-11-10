/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shared_textures_utils2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 03:43:21 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/10 03:44:12 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

static void	default_textures_to_images(t_parsed_data *pd)
{
	if (pd->sh.skin_walker_default.txtr && !pd->sh.skin_walker_default.img)
	{
		pd->sh.skin_walker_default.img = mlx_texture_to_image(pd->mlx,
				pd->sh.skin_walker_default.txtr);
		if (!pd->sh.skin_walker_default.img)
			ui_error();
	}
	if (pd->sh.memory_leak_default.txtr && !pd->sh.memory_leak_default.img)
	{
		pd->sh.memory_leak_default.img = mlx_texture_to_image(pd->mlx,
				pd->sh.memory_leak_default.txtr);
		if (!pd->sh.memory_leak_default.img)
			ui_error();
	}
	if (pd->sh.segv_default.txtr && !pd->sh.segv_default.img)
	{
		pd->sh.segv_default.img = mlx_texture_to_image(pd->mlx,
				pd->sh.segv_default.txtr);
		if (!pd->sh.segv_default.img)
			ui_error();
	}
}

void	init_default_skins(t_parsed_data *pd)
{
	if (pd->sh.skin_walker_default.txtr == NULL)
	{
		pd->sh.skin_walker_default.txtr = mlx_load_png(SKIN_WALKER_DFL);
		if (pd->sh.skin_walker_default.txtr == NULL)
			ui_error();
	}
	if (pd->sh.memory_leak_default.txtr == NULL)
	{
		pd->sh.memory_leak_default.txtr = mlx_load_png(MEMORY_LEAK_DFL);
		if (pd->sh.memory_leak_default.txtr == NULL)
			ui_error();
	}
	if (pd->sh.segv_default.txtr == NULL)
	{
		pd->sh.segv_default.txtr = mlx_load_png(SEGV_DFL);
		if (pd->sh.segv_default.txtr == NULL)
			ui_error();
	}
	default_textures_to_images(pd);
}
