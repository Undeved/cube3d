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
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Our Macros
# define HEIGHT 1080
# define WIDTH 1920
# define TITLE "CUBE 3D"

// Mini map
# define MAX_MAP 500
# define MINI_MAP_X 0
# define MINI_MAP_Y 0
# define PIXEL_BLOCK 38
# define PIXEL_RAY 4

// Minimap colors
# define MM_WALL_COLOR 0x7851A9FF
# define MM_FLOOR_COLOR 0xA085C2FF
# define MM_PLAYER_COLOR 0xBE0000FF
# define MINI_MAP_SIZE 320

// Player movement.
# define SPEED 0.07;
# define STRAFE_SPEED 0.04;
# define ROT_SPEED 0.1
# define NUDGE_FROM_WALL 0.5

# define COLLISION 0.2

# define KEYS_NUMBER 350

// Main menu

// UI positions based on figma
# define TITLE_X ((WIDTH / 2) - (605 / 2))
# define TITLE_Y 165
# define START_BUTTON_X ((WIDTH / 2) - (549 / 2))
# define START_BUTTON_Y 484
# define CHARS_BUTTON_X ((WIDTH / 2) - (549 / 2))
# define CHARS_BUTTON_Y 639
# define EXIT_BUTTON_X ((WIDTH / 2) - (549 / 2))
# define EXIT_BUTTON_Y 806
# define BTN_POP 5

# define JESSE_X (96 - 30) // to offset transparent shadow edge
# define JESSE_Y 271
# define CHORUS_X (691 - 30)
# define CHORUS_Y 271
# define OUSSMAC_X (1286 - 30)
# define OUSSMAC_Y 271
# define SELECT_JESSE_X 238 // select button.
# define SELECT_CHORUS_X 833
# define SELECT_OUSSMAC_X 1428
# define SELECT_Y 208

// UI Textures.
# define MENU_CANVAS_PATH "textures/ui/menu/menu_bg.png"
# define MENU_TITLE_PATH "textures/ui/menu/menu_title.png"
# define START_BUTTON_PATH "textures/ui/menu/start_button.png"
# define CHARS_BUTTON_PATH "textures/ui/menu/characters_button.png"
# define EXIT_BUTTON_PATH "textures/ui/menu/exit_button.png"
# define START_BUTTON_PATH_HV "textures/ui/menu/start_button_hovered.png"
# define CHARS_BUTTON_PATH_HV "textures/ui/menu/characters_button_hovered.png"
# define EXIT_BUTTON_PATH_HV "textures/ui/menu/exit_button_hovered.png"

# define CHARS_BG "textures/ui/characters/characters_bg.png"
# define JESSE_BUTTON "textures/ui/characters/jesse.png"
# define CHORUS_BUTTON "textures/ui/characters/chorus.png"
# define OUSSMAC_BUTTON "textures/ui/characters/oussmac.png"
# define JESSE_BUTTON_HV "textures/ui/characters/jesse_hovered.png"
# define CHORUS_BUTTON_HV "textures/ui/characters/chorus_hovered.png"
# define OUSSMAC_BUTTON_HV "textures/ui/characters/oussmac_hovered.png"
# define SELECTED_BUTTON "textures/ui/characters/selected.png"


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

// Character IDs
typedef enum e_character
{
    JESSE,
    CHORUS,
    OUSSMAC
}   t_character;

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

typedef struct s_level
{
    int     max_x;
    int     max_y;
    bool    game_started;
}   t_level;

typedef struct s_pos
{
    int x;
    int y;
}   t_pos;

typedef struct s_bpos
{
    double x;
    double y;
}   t_bpos;

typedef struct s_bdir
{
    double x;
    double y;
}   t_bdir;

typedef struct s_player
{
    t_pos   pos;
    t_bpos  bpos;
    t_bdir  bdir;
    char    dir;
    t_bpos   offset;
    t_bpos   new_pos;
}   t_player;

typedef struct s_minimap
{
    t_pos       pos;
    mlx_image_t *img;
}   t_minimap;

typedef struct s_keys
{
    bool    pressed[KEYS_NUMBER];
}   t_keys;

typedef struct s_raw_img
{
    mlx_texture_t       *txtr;
    mlx_image_t     *img;
}   t_raw_img;

typedef struct s_button
{
    mlx_texture_t       *txtr;
    mlx_image_t     *img;
    bool            hoverd;
}   t_button;

typedef struct s_main_menu
{
    t_raw_img           bg;
    t_raw_img           title;
    t_button            b_start;
    t_button            b_chars;
    t_button            b_exit;
    t_button            b_start_hv;
    t_button            b_chars_hv;
    t_button            b_exit_hv;
    int                 button_index;
}   t_main_menu;

typedef struct s_characters_ui
{
    t_raw_img           bg;
    t_raw_img           selected;
    t_character         select_index;
    t_button            b_jesse;
    t_button            b_chorus;
    t_button            b_oussmac;
    t_button            b_jesse_hv;
    t_button            b_chorus_hv;
    t_button            b_oussmac_hv;
    int                 button_index;
}   t_characters_ui;

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
    int             player_count;
    t_level         level;
    t_player        player;
    mlx_t           *mlx;
    mlx_image_t     *screen;
    t_minimap       minimap;
    t_keys          keys;
    t_main_menu     menu;
    t_characters_ui chars_menu;
    int             ui_index;
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
void    validate_params(char **map_file, t_cube *cube);
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
bool valid_grid_chars(char *str, int *player_count, bool map_grid);
void    extract_map(char **map_file, int *i, t_cube *cube);
void    closed_bounds(t_cube *cube);
void    get_level_data(t_cube *cube);
void    get_player_pos(char **map_grid, int *x, int *y, char *dir);
void    flood_fill(char **grid, t_pos pos, t_pos max);
char    **grid_dup(char **grid);

// Game loop.
void    game_loop(t_parsed_data *pd);
void    game_render(void *param);
void    draw_minimap(t_parsed_data *pd);
void    handle_player_input(mlx_key_data_t keydata, void *param);
void    update_player_data(t_parsed_data *pd);

// Raycast
void	raycast_system(t_parsed_data *pd);
void    raycast_render(t_parsed_data *pd);

// UI
void    init_main_menu(t_parsed_data *pd);
void    main_menu(t_parsed_data *pd);
void    handle_ui_input(mlx_key_data_t keydata, t_parsed_data *pd);
void    ui_error(void);
void    init_characters_menu(t_parsed_data *pd);
void    characters_menu(t_parsed_data *pd);

// helpers test
void    print_argv(char **argv);

#endif