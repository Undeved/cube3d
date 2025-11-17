/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_roof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 04:35:16 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/16 15:15:28 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

bool	validate_floor_roof(char *str)
{
	char	**args;

	if (ft_strlen(str) < 1)
		return (false);
	args = tab_split(str, " \t");
	if (arg_count(args) != 2)
		return (false);
	if (ft_strcmp(args[0], "F") != 0 && ft_strcmp(args[0], "C") != 0)
		return (false);
	return (true);
}

static void	invalid_floor_roof(char type, int error_num)
{
	if (type == 'F')
	{
		if (error_num == 0)
			print_error("Error\nFloor Must To Be Seperated By 3 <,>\n");
		else if (error_num == 1)
			print_error("Error\nFloor Must To Be Have 3 Values\n");
		else if (error_num == 2)
			print_error("Error\nNo Double Floor Values\n");
		else if (error_num == 3)
			print_error("Error\nFloor Values Must Be Digits In Range 0-255\n");
	}
	else if (type == 'C')
	{
		if (error_num == 0)
			print_error("Error\nCeiling Values MustTo Be Seperated By 3 <,>\n");
		else if (error_num == 1)
			print_error("Error\nCeiling Must To Be Have 3 Values\n");
		else if (error_num == 2)
			print_error("Error\nNo Double Ceiling Values\n");
		else if (error_num == 3)
			print_error("Error\nCeeiling Values Must Be Digits (0-255)\n");
	}
	mind_free_all(EXIT_FAILURE);
}

static bool	has_semi(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count == 0 || count > 2)
		return (false);
	return (true);
}

static void	extract_rgbs(char *rgb_values, t_cube *cube, char type)
{
	char	**rgb;

	if (duplicated_floor_roof(type, cube))
		invalid_floor_roof(type, 2);
	if (!has_semi(rgb_values))
		invalid_floor_roof(type, 0);
	rgb = tab_split(rgb_values, ",");
	if (arg_count(rgb) != 3)
		invalid_floor_roof(type, 1);
	if (!is_num(rgb[0]) || !is_num(rgb[1]) || !is_num(rgb[2]))
		invalid_floor_roof(type, 3);
	if (type == 'F')
	{
		cube->pd.floor.r = ft_atoi(rgb[0]);
		cube->pd.floor.g = ft_atoi(rgb[1]);
		cube->pd.floor.b = ft_atoi(rgb[2]);
		cube->pd.floor.already_extracted = true;
	}
	else if (type == 'C')
	{
		cube->pd.roof.r = ft_atoi(rgb[0]);
		cube->pd.roof.g = ft_atoi(rgb[1]);
		cube->pd.roof.b = ft_atoi(rgb[2]);
		cube->pd.roof.already_extracted = true;
	}
}

void	extarct_floor_roof(char *str, t_cube *cube)
{
	char	**args;

	args = tab_split(str, " \t");
	if (ft_strcmp(args[0], "F") == 0)
		extract_rgbs(args[1], cube, 'F');
	else if (ft_strcmp(args[0], "C") == 0)
		extract_rgbs(args[1], cube, 'C');
}
