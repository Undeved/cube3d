/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 04:09:26 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 05:05:35 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_wall(t_parsed_data *pd, int x, t_line_data *line,
		uint32_t wall_col)
{
	int	y;

	y = line->draw_start;
	while (y <= line->draw_end)
	{
		mlx_put_pixel(pd->screen, x, y, wall_col);
		y++;
	}
}

mlx_texture_t	*get_wall_texture(t_parsed_data *pd, int side, t_bdir ray_dir)
{
	mlx_texture_t	*tx;

	if (side == 0)
	{
		if (ray_dir.x > 0)
			tx = pd->txtr_we.txtr;
		else
			tx = pd->txtr_ea.txtr;
	}
	else
	{
		if (ray_dir.y > 0)
			tx = pd->txtr_no.txtr;
		else
			tx = pd->txtr_so.txtr;
	}
	return (tx);
}

inline uint32_t	darken_color(uint32_t c)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	r = (c >> 24) & 0xFF;
	g = (c >> 16) & 0xFF;
	b = (c >> 8) & 0xFF;
	r >>= 1;
	g >>= 1;
	b >>= 1;
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

void	draw_ceiling(t_parsed_data *pd, int x, int draw_start, int horizon)
{
	int			y;
	uint32_t	color;

	y = 0;
	while (y < draw_start)
	{
		color = shade_color(CEILING, horizon + y, ROOF_FALLOF);
		mlx_put_pixel(pd->screen, x, y, color);
		y++;
	}
}

void	draw_floor(t_parsed_data *pd, int x, int draw_end, int horizon)
{
	int			y;
	uint32_t	color;

	y = draw_end + 1;
	while (y < (horizon * 2))
	{
		color = shade_color(FLOOR, ((horizon * 2)
					+ SHIFT_FLOOR_SHADE) - y, FLOOR_FALLOF);
		mlx_put_pixel(pd->screen, x, y, color);
		y++;
	}
}
