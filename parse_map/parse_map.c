/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 05:53:50 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/08 05:55:05 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	map_error(void)
{
	print_error("Error\nMap File Invalid.\n");
	mind_free_all(EXIT_FAILURE);
}

static void	closer(int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}

static int	count_map_size(t_cube *cube)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(cube->pd.fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(cube->pd.fd);
	}
	get_next_line(-1);
	closer(&cube->pd.fd);
	if (count >= MAX_MAP || count == 0)
		map_error();
	return (count);
}

static int	read_map_file(char *map_path, t_cube *cube)
{
	char	*line;
	int		count;
	int		i;

	cube->pd.fd = open(map_path, O_RDONLY);
	if (cube->pd.fd == -1)
		map_error();
	count = count_map_size(cube);
	cube->pd.map_file = allocate_gc(malloc(sizeof(char *) * (count + 1)));
	cube->pd.fd = open(map_path, O_RDONLY);
	if (cube->pd.fd == -1)
		map_error();
	i = 0;
	line = get_next_line(cube->pd.fd);
	while (line != NULL)
	{
		cube->pd.map_file[i] = allocate_gc(ft_strdup(line));
		free(line);
		if (!cube->pd.map_file[i])
			return (closer(&cube->pd.fd), mind_free_all(EXIT_FAILURE), 1);
		i++;
		line = get_next_line(cube->pd.fd);
	}
	return (cube->pd.map_file[i] = NULL, closer(&cube->pd.fd), 0);
}

void	parse_map(char *map_path, t_cube *cube)
{
	init_parsed_data(cube);
	cube->map_path = allocate_gc(ft_strdup(map_path));
	read_map_file(cube->map_path, cube);
	cube->pd.map_file = trim_newlines(cube->pd.map_file);
	validate_map(cube->pd.map_file, cube);
}
