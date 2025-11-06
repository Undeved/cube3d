/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 04:09:04 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 04:57:06 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	camera_plane(t_parsed_data *pd)
{
	pd->player.camera_plane.pos.x = pd->player.bdir.x * SCALER;
	pd->player.camera_plane.pos.y = pd->player.bdir.y * SCALER;
	pd->player.camera_plane.dir.x = pd->player.bdir.y;
	pd->player.camera_plane.dir.y = -pd->player.bdir.x;
}

void	update_raycast_data(t_parsed_data *pd)
{
	camera_plane(pd);
}
