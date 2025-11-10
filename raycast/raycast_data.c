/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 04:09:04 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/10 12:03:38 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	camera_plane(t_parsed_data *pd)
{
	pd->player.camera_plane.pos.x = pd->player.bdir.x;
	pd->player.camera_plane.pos.y = pd->player.bdir.y;
	pd->player.camera_plane.dir.x = pd->player.bdir.y;
	pd->player.camera_plane.dir.y = -pd->player.bdir.x;
}

void	update_raycast_data(t_parsed_data *pd)
{
	camera_plane(pd);
}
