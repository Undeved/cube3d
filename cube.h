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

# include "MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include "unistd.h"
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// our Macros
# define HEIGHT 600
# define WIDTH 800
# define TITLE "CUBE 3D"


// Garbage collector struct.
// IMPOOORTANT ADD FD TO GC.
typedef struct s_mind_alloc
{
	void				*ptr;
	bool				free_at_end;
	struct s_mind_alloc	*next;
}	t_mind_alloc;

typedef struct s_pd
{
    // parsed data
    char    **map_file;
    int     fd;
}   t_parsed_data;

typedef struct s_cube
{
    char            *map_path;
    t_parsed_data    pd;
}   t_cube;


// Validate input args.
int     ft_strlen(char *str);
void    print_error(char *str);
void    print_comm(char *str);
void    evaluate_input(int argc, char **argv);

// Map parser.
void    parse_map(char *map_path, t_cube *cube);
char	*ft_strdup(char *s1);

// Garbage Collector.
void	*allocate_gc(void *ptr);
void	mind_free_all(int status);

// GNL
char	*get_next_line(int fd);
char	*gnl_ft_strdup(char *s1);
size_t	gnl_ft_strlen(const char *s);
char	*gnl_ft_strjoin(char *s1, char *s2);
char	*gnl_ft_strchr(const char *s, int c);
char	*gnl_ft_substr(char *s, unsigned int start, size_t len);

// Validate map.
void    validate_map(char **map_file);
void north_texture(char **map_file);
char	*ft_strchr(char	*s, int c);
int	ft_strcmp(char *s1, char *s2);

// helpers test
void    print_argv(char **argv);
void simple_raycast(void* param);

#endif