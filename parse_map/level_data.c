/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 05:49:47 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/08 05:52:27 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	get_level_data(t_cube *cube)
{
	cube->pd.level.max_x = ft_strlen(cube->pd.map_grid[1]) - 1;
	cube->pd.level.max_y = arg_count(cube->pd.map_grid) - 1;
}

static bool	is_player(char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'W' || c == 'E')
		return (true);
	return (false);
}

static bool	has_player(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_player(str[i]))
			return (true);
		i++;
	}
	return (false);
}

void	get_player_pos(char **map_grid, int *x, int *y, char *dir)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map_grid[i])
	{
		if (has_player(map_grid[i]))
		{
			*y = i;
			while (map_grid[i][j])
			{
				if (is_player(map_grid[i][j]))
				{
					*x = j;
					*dir = map_grid[i][j];
					map_grid[i][j] = '0';
					break ;
				}
				j++;
			}
		}
		i++;
	}
}
