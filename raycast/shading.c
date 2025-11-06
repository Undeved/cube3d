/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 04:09:12 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/11/06 04:28:48 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

uint32_t	shade_color(uint32_t base_col, double dist, double magnitude)
{
	double		shade;
	uint8_t		a;
	uint32_t	color;

	shade = 1.0 / (1.0 + dist * magnitude);
	color = (((uint8_t)(((base_col >> 24) & 0xFF) * shade)) << 24)
		| (((uint8_t)(((base_col >> 16) & 0xFF) * shade)) << 16)
		| (((uint8_t)(((base_col >> 8) & 0xFF) * shade)) << 8);
	a = base_col & 0xFF;
	return (color | a);
}
