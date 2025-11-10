/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_radar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:49 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/10 08:12:16 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

int	sqr(int x)
{
	return (x * x);
}

static bool	within_circle_radious(int diff_x,
	int diff_y, int radious, int border_width)
{
	if (sqr(diff_x) + sqr(diff_y) <= sqr(radious)
		&& sqr(diff_x) + sqr(diff_y) > sqr(radious - border_width))
		return (true);
	return (false);
}

static void	draw_circle_frame(t_parsed_data *pd, t_pos center, int radious)
{
	t_pos	pixel;
	t_pos	diff;
	int		pixel_dist;

	pixel.y = 0;
	while (pixel.y < MINI_MAP_SIZE)
	{
		pixel.x = 0;
		while (pixel.x < MINI_MAP_SIZE)
		{
			diff.x = pixel.x - center.x;
			diff.y = pixel.y - center.y;
			pixel_dist = sqrt(sqr(diff.x) + sqr(diff.y));
			if (sqr(diff.x) + sqr(diff.y) < sqr(radious - BORDER_WIDTH))
				mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y,
					shade_color(CIRCLE_FRAME, pixel_dist, 0.005));
			else if (within_circle_radious(diff.x, diff.y,
					radious, BORDER_WIDTH))
				mlx_put_pixel(pd->minimap.img, pixel.x, pixel.y,
					shade_color(CIRCLE_BORDER, pixel_dist, 0.008));
			pixel.x++;
		}
		pixel.y++;
	}
}

void	init_radar(t_parsed_data *pd)
{
	t_pos	center;
	int		radious;

	center.x = MINI_MAP_SIZE / 2;
	center.y = MINI_MAP_SIZE / 2;
	radious = MINI_MAP_SIZE / 2 - RADIOUS_MARGIN;
	draw_circle_frame(pd, center, radious);
}
