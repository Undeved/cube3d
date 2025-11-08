/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 04:28:14 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/08 04:52:04 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	fill(char **grid, t_pos pos, t_pos max)
{
	if (pos.x < 0 || pos.y < 0 || pos.x > max.x || pos.y > max.y)
	{
		print_error("Error\nUnclosed Map Grid.\n");
		mind_free_all(EXIT_FAILURE);
	}
	if (grid[pos.y][pos.x] == '1' || grid[pos.y][pos.x] == 'V')
		return ;
	if (grid[pos.y][pos.x] == ' ')
	{
		print_error("Error\nUnclosed Map Grid.\n");
		mind_free_all(EXIT_FAILURE);
	}
	grid[pos.y][pos.x] = 'V';
	fill(grid, (t_pos){pos.x + 1, pos.y}, max);
	fill(grid, (t_pos){pos.x - 1, pos.y}, max);
	fill(grid, (t_pos){pos.x, pos.y + 1}, max);
	fill(grid, (t_pos){pos.x, pos.y - 1}, max);
}

void	flood_fill(char **grid, t_pos pos, t_pos max)
{
	fill(grid, pos, max);
}
