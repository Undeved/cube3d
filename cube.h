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
# define HEIGHT 1080
# define WIDTH 1920
# define TITLE "CUBE 3D"


// Garbage collector struct.
// IMPOOORTANT ADD FD TO GC.
typedef struct s_mind_alloc
{
	void				*ptr;
	bool				free_at_end;
	struct s_mind_alloc	*next;
}	t_mind_alloc;

typedef enum e_direction
{
    NORTH_TXT,
    SOUTH_TXT,
    WEST_TXT,
    EAST_TXT
}   t_direction;

typedef struct s_texture
{
    t_direction dir;
    char        *path;
    bool        already_extracted;
}   t_texture;

typedef struct s_floor_roof
{
    unsigned char   r;
    unsigned char   g;
    unsigned char   b;
    bool        already_extracted;
}   t_floor_roof;

typedef struct s_pd
{
    // parsed data
    char            **map_file;
    int             fd;
    t_texture       txtr_no;
    t_texture       txtr_so;
    t_texture       txtr_we;
    t_texture       txtr_ea;
    t_floor_roof    floor;
    t_floor_roof    roof;
    char            **map_grid;
}   t_parsed_data;

typedef struct s_cube
{
    char            *map_path;
    t_parsed_data    pd;
}   t_cube;


// Validate input args.
size_t  ft_strlen(char *str);
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
void    validate_map(char **map_file, t_cube *cube);
void    validate_textures(char **map_file, t_cube *cube);
char	**tab_split(char *s, char *sep);
char	*ft_strchr(char	*s, int c);
int     ft_strcmp(char *s1, char *s2);
size_t	arg_count(char **argv);
char    *ft_substr(char *s, size_t start, size_t len);
bool    validate_floor_roof(char *str);
bool    validate_floor_roof(char *str);
bool    is_num(char *str);
int     ft_atoi(const char *str);
void     extarct_floor_roof(char *str, t_cube *cube);
char    **trim_newlines(char **old_argv);
bool    valid_grid_chars(char *str);
void    extract_map(char **map_file, int *i, t_cube *cube);

// helpers test
void    print_argv(char **argv);
void    simple_raycast(void* param);
void    basic_game_loop(void);

#endif