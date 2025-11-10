/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:45:43 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/09 22:46:40 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	game_render(void *param)
{
	t_parsed_data	*pd;

	pd = param;
	main_menu(pd);
	characters_menu(pd);
	if (!pd->level.game_started)
		return ;
	update_ui_anim(&pd->player.gun.shoot);
	update_ui_anim(&pd->player.gun.reload);
	update_player_data(pd);
	update_enemies(pd);
	update_raycast_data(pd);
	raycast_render(pd);
	draw_medkits(pd);
	render_gun(pd);
	render_radar(pd);
	check_medkit_pickup(pd);
}
