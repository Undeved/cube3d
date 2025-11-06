/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 03:55:54 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 05:18:12 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	init_door_column(t_door_column *dc)
{
	dc->tx = get_door_texture(dc->pd);
	if (!dc->tx || !dc->tx->pixels)
	{
		draw_wall(dc->pd, dc->x, dc->line, 0x0000FF00);
		return ;
	}
	dc->tex_w = (int)dc->tx->width;
	dc->tex_h = (int)dc->tx->height;
	dc->screen_h = dc->pd->screen->height;
	if (dc->side == 0)
		dc->wall_x = dc->pos.y + dc->perp_dist * dc->ray_dir.y;
	else
		dc->wall_x = dc->pos.x + dc->perp_dist * dc->ray_dir.x;
	dc->wall_x -= floor(dc->wall_x);
	dc->tex_x = (int)(dc->wall_x * (double)dc->tex_w);
	if (dc->tex_x < 0)
		dc->tex_x = 0;
	if (dc->tex_x >= dc->tex_w)
		dc->tex_x = dc->tex_w - 1;
	dc->tex_x = dc->tex_w - dc->tex_x - 1;
	if (dc->side == 0 && dc->ray_dir.x > 0.0)
		dc->tex_x = dc->tex_w - dc->tex_x - 1;
	if (dc->side == 1 && dc->ray_dir.y < 0.0)
		dc->tex_x = dc->tex_w - dc->tex_x - 1;
}

uint32_t	get_door_pixel_color(t_door_column *dc, int tex_y)
{
	unsigned char	*p;
	int				idx;
	uint32_t		color;

	p = (unsigned char *)dc->tx->pixels;
	idx = (tex_y * dc->tx->width + dc->tex_x) * 4;
	color = (p[idx + 0] << 24) | (p[idx + 1] << 16) | (p[idx + 2] << 8) | 0xFF;
	return (color);
}

void	draw_door_pixels(t_door_column *dc)
{
	int			y;
	int			tex_y;
	uint32_t	sample;

	y = dc->line->draw_start;
	while (y <= dc->line->draw_end)
	{
		tex_y = (int)dc->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= dc->tex_h)
			tex_y = dc->tex_h - 1;
		sample = get_door_pixel_color(dc, tex_y);
		if (dc->side == 1)
			sample = darken_color(sample);
		if (dc->tile_char == 'O')
			mlx_put_pixel(dc->pd->screen, dc->x, y,
				shade_color(sample, dc->perp_dist, WALLS_FALLOF * 0.65));
		else
			mlx_put_pixel(dc->pd->screen, dc->x, y,
				shade_color(sample, dc->perp_dist, WALLS_FALLOF));
		dc->tex_pos += dc->step;
		y++;
	}
}

static char	get_column_tile_char(t_parsed_data *pd, t_column_data *col)
{
	char	tile_char;

	tile_char = 'D';
	if (col->map.y >= 0 && col->map.y < 99999)
	{
		if (pd->map_grid[col->map.y] && col->map.x >= 0)
			tile_char = pd->map_grid[col->map.y][col->map.x];
	}
	else
	{
		if (pd->map_grid[col->map.y] && pd->map_grid[col->map.y][col->map.x])
			tile_char = pd->map_grid[col->map.y][col->map.x];
	}
	return (tile_char);
}

void	draw_door_column(t_parsed_data *pd, t_column_data *col,
		t_line_data *line)
{
	t_door_column	dc;
	char			tile_char;

	dc.pd = pd;
	dc.x = col->x;
	dc.line = line;
	dc.perp_dist = col->perp_dist;
	dc.side = col->side;
	dc.ray_dir = col->ray_dir;
	dc.pos = col->player_pos;
	tile_char = get_column_tile_char(pd, col);
	dc.tile_char = tile_char;
	init_door_column(&dc);
	if (!dc.tx)
		return ;
	setup_door_stepping(&dc);
	draw_door_pixels(&dc);
}
