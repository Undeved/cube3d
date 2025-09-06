/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:29:41 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/27 22:44:00 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

//# include "MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include "unistd.h"
# include <stdio.h>

typedef struct s_cube
{
    char    *map_path;
}   t_cube;


// Validate input args.
int     ft_strlen(char *str);
void    print_error(char *str);
void    print_comm(char *str);
void    evaluate_input(int argc, char **argv);

// Map parser.
void    parse_map(char *map_path, t_cube *cube);
char	*ft_strdup(char *s1);

#endif // CUBE_H