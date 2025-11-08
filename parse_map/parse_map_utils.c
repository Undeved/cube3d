/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 05:53:13 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/08 05:53:21 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	init_parsed_textures(t_cube *cube)
{
	cube->pd.txtr_no.path = NULL;
	cube->pd.txtr_so.path = NULL;
	cube->pd.txtr_we.path = NULL;
	cube->pd.txtr_ea.path = NULL;
	cube->pd.txtr_no.already_extracted = false;
	cube->pd.txtr_so.already_extracted = false;
	cube->pd.txtr_we.already_extracted = false;
	cube->pd.txtr_ea.already_extracted = false;
	cube->pd.txtr_no.dir = NORTH_TXT;
	cube->pd.txtr_so.dir = SOUTH_TXT;
	cube->pd.txtr_we.dir = WEST_TXT;
	cube->pd.txtr_ea.dir = EAST_TXT;
	cube->pd.floor.already_extracted = false;
	cube->pd.roof.already_extracted = false;
}

void	init_parsed_data(t_cube *cube)
{
	cube->pd.fd = -1;
	cube->pd.map_file = NULL;
	cube->pd.map_grid = NULL;
	cube->pd.level.max_x = 0;
	cube->pd.level.max_y = 0;
	cube->pd.player.pos.x = 0;
	cube->pd.player.pos.y = 0;
	cube->pd.player.dir = 'E';
	cube->pd.player_count = 0;
	init_parsed_textures(cube);
}
