/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 04:28:14 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/13 23:57:42 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	fill(char **grid, t_pos pos, t_pos max, int *enemy_count)
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
	if (grid[pos.y][pos.x] == 'X'
		|| grid[pos.y][pos.x] == 'Y'
		|| grid[pos.y][pos.x] == 'Z')
	{
		(*enemy_count)++;
	}
	grid[pos.y][pos.x] = 'V';
	fill(grid, (t_pos){pos.x + 1, pos.y}, max, enemy_count);
	fill(grid, (t_pos){pos.x - 1, pos.y}, max, enemy_count);
	fill(grid, (t_pos){pos.x, pos.y + 1}, max, enemy_count);
	fill(grid, (t_pos){pos.x, pos.y - 1}, max, enemy_count);
}

void	flood_fill(char **grid, t_pos pos, t_pos max, int *enemy_count)
{
	fill(grid, pos, max, enemy_count);
}
