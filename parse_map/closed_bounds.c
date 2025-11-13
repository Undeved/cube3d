/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_bounds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 03:56:23 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/14 00:02:40 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static int	biggest_line_len(char **argv)
{
	int	biggest_len;
	int	i;

	biggest_len = 0;
	i = 0;
	while (argv[i])
	{
		if ((int)ft_strlen(argv[i]) > biggest_len)
			biggest_len = (int)ft_strlen(argv[i]);
		i++;
	}
	return (biggest_len);
}

char	*append_spaces(char *str, int big_len, int len)
{
	int		difference;
	char	*appended;
	int		i;
	int		j;

	len = (int)ft_strlen(str);
	difference = big_len - len;
	len = len + difference;
	appended = allocate_gc(malloc(sizeof(char) * (len + 1)));
	i = 0;
	j = 0;
	while (str[i])
		appended[j++] = str[i++];
	while (j < len)
		appended[j++] = ' ';
	appended[j] = '\0';
	return (appended);
}

static void	gridify_map(char **old_grid)
{
	int	i;
	int	biggest_len;
	int	len;

	len = 0;
	biggest_len = biggest_line_len(old_grid);
	if (biggest_len >= MAX_MAP)
	{
		print_error("Error\nBig Map.\n");
		mind_free_all(EXIT_FAILURE);
	}
	i = 0;
	while (old_grid[i])
	{
		if ((int)ft_strlen(old_grid[i]) < biggest_len)
			old_grid[i] = append_spaces(old_grid[i], biggest_len, len);
		i++;
	}
}

char	**grid_dup(char **grid)
{
	int		i;
	int		argc;
	char	**new_grid;

	i = 0;
	argc = arg_count(grid);
	new_grid = allocate_gc(malloc((argc + 1) * sizeof(char *)));
	while (grid[i])
	{
		new_grid[i] = allocate_gc(ft_strdup(grid[i]));
		i++;
	}
	new_grid[i] = NULL;
	return (new_grid);
}

void	closed_bounds(t_cube *cube)
{
	char	**grid_cpy;

	gridify_map(cube->pd.map_grid);
	get_level_data(cube);
	get_player_pos(cube->pd.map_grid, &cube->pd.player.pos.x,
		&cube->pd.player.pos.y, &cube->pd.player.dir);
	grid_cpy = grid_dup(cube->pd.map_grid);
	get_enemies(cube);
	cube->pd.enemy_count_r = 0;
	flood_fill(grid_cpy, cube->pd.player.pos,
		(t_pos){cube->pd.level.max_x, cube->pd.level.max_y},
		&cube->pd.enemy_count_r);
	if (cube->pd.enemy_count_r != cube->pd.enemy_count)
	{
		print_error("Error\nMake Sure All Enemies Are Reachable\n");
		mind_free_all(EXIT_FAILURE);
	}
}
