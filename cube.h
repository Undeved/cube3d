/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:29:41 by oimzilen          #+#    #+#             */
/*   Updated: 2025/11/17 15:43:45 by oimzilen         ###   ########.fr       */
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
# include <sys/time.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
// Colors
# define RED "\e[31m"
# define GRN "\e[32m"
# define BLU "\e[34m"
# define YLW "\e[33m"
# define MGN "\e[35m"
# define CYN "\e[36m"
# define RST "\e[97m"
// Our Macros
# define HEIGHT 1080
# define WIDTH 1920
# define TITLE "1337 Ways To Die"
// Mini map
# define MAX_MAP 500
# define MINI_MAP_SIZE 300
# define MINI_MAP_Y 20
# define MINI_MAP_X 1600
# define PIXEL_BLOCK 18
# define PIXEL_RAY 4
# define RADIOUS_MARGIN 20
# define BORDER_WIDTH 8
# define CIRCLE_BORDER 0x8EB82CFF
# define CIRCLE_FRAME 0x102308FF
# define PLAYER_ICON 0xB0F01BFF
# define WALL_ICON 0x2D4225FF
# define FLOOR_ICON 0x4F6845FF
# define DOOR_ICON 0xE3BB51FF
# define OPEN_DOOR_ICON 0xAC56E3FF
// Minimap colors
# define MM_WALL_COLOR 0x7851A9FF
# define MM_FLOOR_COLOR 0xA085C2FF
# define MM_PLAYER_COLOR 0xBE0000FF
// Player movement.
# define SPEED 0.085
# define STRAFE_SPEED 0.070
# define ROT_SPEED 0.08
# define NUDGE_FROM_WALL 0.5
# define MOUSE_SENSITIVITY 0.00088
# define PI 3.14159
# define PITCH_SPEED 30
# define MAX_PITCH  210
# define MIN_PITCH  -50
# define FOV 60
// player stats
# define PLAYER_HEALTH 100
# define COLLISION 0.1
# define KEYS_NUMBER 350
// UI Positions Based On Figma
# define TITLE_X 658
# define TITLE_Y 165
# define START_BUTTON_X 686
# define START_BUTTON_Y 484
# define CHARS_BUTTON_X 686
# define CHARS_BUTTON_Y 639
# define EXIT_BUTTON_X 686
# define EXIT_BUTTON_Y 806
# define BTN_POP 5
# define TRN_OFST 30
# define JESSE_X 66
# define JESSE_Y 271
# define CHORUS_X 661
# define CHORUS_Y 271
# define OUSSMAC_X 1256
# define OUSSMAC_Y 271
# define SELECT_JESSE_X 238
# define SELECT_CHORUS_X 833
# define SELECT_OUSSMAC_X 1428
# define SELECT_Y 208
// UI Textures.
# define MENU_CANVAS_PATH "txt/ui/menu/menu_bg.png"
# define MENU_TITLE_PATH "txt/ui/menu/menu_title.png"
# define START_BUTTON_PATH "txt/ui/menu/start_button.png"
# define CHARS_BUTTON_PATH "txt/ui/menu/characters_button.png"
# define EXIT_BUTTON_PATH "txt/ui/menu/exit_button.png"
# define START_BUTTON_PATH_HV "txt/ui/menu/start_button_hovered.png"
# define CHARS_BUTTON_PATH_HV "txt/ui/menu/characters_button_hovered.png"
# define EXIT_BUTTON_PATH_HV "txt/ui/menu/exit_button_hovered.png"
# define CHARS_BG "txt/ui/characters/characters_bg.png"
# define JESSE_BUTTON "txt/ui/characters/jesse.png"
# define CHORUS_BUTTON "txt/ui/characters/chorus.png"
# define OUSSMAC_BUTTON "txt/ui/characters/oussmac.png"
# define JESSE_BUTTON_HV "txt/ui/characters/jesse_hovered.png"
# define CHORUS_BUTTON_HV "txt/ui/characters/chorus_hovered.png"
# define OUSSMAC_BUTTON_HV "txt/ui/characters/oussmac_hovered.png"
# define SELECTED_BUTTON "txt/ui/characters/selected.png"
# define GAME_OVER "txt/ui/in_game/game_over.png"
# define GAME_WON "txt/ui/in_game/game_won.png"
// Door Texture
# define DOOR_TEXTURE "txt/wall_textures/door.png"
// Gun textures -----------------------------------------------------------
# define GUN_JESSE_IDLE "txt/ui/in_game/gun/slingshot_idle.png"
# define GUN_JESSE_AIM "txt/ui/in_game/gun/slingshot_aim.png"
# define GUN_JESSE_NOAMMO "txt/ui/in_game/gun/slingshot_idle_empty.png"
// Gun shoot anim
# define GUN_JESSE_SHOOT_1 "txt/ui/in_game/gun/shoot/slingshot_shoot0001.png"
# define GUN_JESSE_SHOOT_2 "txt/ui/in_game/gun/shoot/slingshot_shoot0002.png"
# define GUN_JESSE_SHOOT_3 "txt/ui/in_game/gun/shoot/slingshot_shoot0003.png"
# define GUN_JESSE_SHOOT_4 "txt/ui/in_game/gun/shoot/slingshot_shoot0004.png"
# define GUN_SHOOT_FRMS 4
// Gun reload anim
# define GUN_JESSE_RELOAD_1 "txt/ui/in_game/gun/reload/slingshot_reload0001.png"
# define GUN_JESSE_RELOAD_2 "txt/ui/in_game/gun/reload/slingshot_reload0002.png"
# define GUN_JESSE_RELOAD_3 "txt/ui/in_game/gun/reload/slingshot_reload0003.png"
# define GUN_JESSE_RELOAD_4 "txt/ui/in_game/gun/reload/slingshot_reload0004.png"
# define GUN_JESSE_RELOAD_5 "txt/ui/in_game/gun/reload/slingshot_reload0005.png"
# define GUN_JESSE_RELOAD_6 "txt/ui/in_game/gun/reload/slingshot_reload0006.png"
# define GUN_RELOAD_FRMS 6
// Chorus gun textures
# define GUN_CHORUS_IDLE "txt/ui/in_game/chorus/m42_idle.png"
# define GUN_CHORUS_AIM "txt/ui/in_game/chorus/m42_aim.png"
# define GUN_CHORUS_SHOOT_1 "txt/ui/in_game/chorus/shoot/m42_shoot0001.png"
# define GUN_CHORUS_SHOOT_2 "txt/ui/in_game/chorus/shoot/m42_shoot0002.png"
# define GUN_CHORUS_SHOOT_3 "txt/ui/in_game/chorus/shoot/m42_shoot0003.png"
# define GUN_CHORUS_SHOOT_4 "txt/ui/in_game/chorus/shoot/m42_shoot0004.png"
# define GUN_CHORUS_RELOAD_1 "txt/ui/in_game/chorus/reload/m42_reload0001.png"
# define GUN_CHORUS_RELOAD_2 "txt/ui/in_game/chorus/reload/m42_reload0002.png"
# define GUN_CHORUS_RELOAD_3 "txt/ui/in_game/chorus/reload/m42_reload0003.png"
# define GUN_CHORUS_RELOAD_4 "txt/ui/in_game/chorus/reload/m42_reload0004.png"
# define GUN_CHORUS_RELOAD_5 "txt/ui/in_game/chorus/reload/m42_reload0005.png"
# define GUN_CHORUS_RELOAD_6 "txt/ui/in_game/chorus/reload/m42_reload0006.png"
// Oussmac gun textures
# define GUN_OUSSMAC_IDLE "txt/ui/in_game/ouss/37mm_idle.png"
# define GUN_OUSSMAC_AIM "txt/ui/in_game/ouss/37mm_aim.png"
# define GUN_OUSSMAC_SHOOT_1 "txt/ui/in_game/ouss/shoot/37mm_shoot0001.png"
# define GUN_OUSSMAC_SHOOT_2 "txt/ui/in_game/ouss/shoot/37mm_shoot0002.png"
# define GUN_OUSSMAC_SHOOT_3 "txt/ui/in_game/ouss/shoot/37mm_shoot0003.png"
# define GUN_OUSSMAC_SHOOT_4 "txt/ui/in_game/ouss/shoot/37mm_shoot0004.png"
# define GUN_OUSSMAC_RELOAD_1 "txt/ui/in_game/ouss/reload/37mm_reload0001.png"
# define GUN_OUSSMAC_RELOAD_2 "txt/ui/in_game/ouss/reload/37mm_reload0002.png"
# define GUN_OUSSMAC_RELOAD_3 "txt/ui/in_game/ouss/reload/37mm_reload0003.png"
# define GUN_OUSSMAC_RELOAD_4 "txt/ui/in_game/ouss/reload/37mm_reload0004.png"
# define GUN_OUSSMAC_RELOAD_5 "txt/ui/in_game/ouss/reload/37mm_reload0005.png"
# define GUN_OUSSMAC_RELOAD_6 "txt/ui/in_game/ouss/reload/37mm_reload0006.png"
// Health_UI textures
# define HEALTH_BAR "txt/ui/in_game/health/health_bar.png"
// health backgrounds
# define HP_JESSE "txt/ui/in_game/health/jesse_health_bar.png"
# define HP_CHORUS "txt/ui/in_game/health/chorus_health_bar.png"
# define HP_OUSSMAC "txt/ui/in_game/health/oussmac_health_bar.png"
# define HBAR_X 1625
# define HBAR_Y 342
# define HBAR_BG_X 1592
# define HBAR_BG_Y 298
# define SKIN_WALKER_DFL "txt/enemy/animation_enemy/x/garbage_value_idle.png"
# define MEMORY_LEAK_DFL "txt/enemy/animation_enemy/y/memleak_idle.png"
# define SEGV_DFL "txt/enemy/animation_enemy/z/segfault_idle.png"
# define GUN_X 767
# define GUN_Y 432
# define GUN_AIM_X 383
# define GUN_AIM_Y 431
# define DAMAGE 10
# define MAX_ENEMIES 100

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
}	t_direction;

// Character IDs
typedef enum e_character
{
	JESSE,
	CHORUS,
	OUSSMAC
}	t_character;

typedef struct s_texture
{
	t_direction		dir;
	char			*path;
	mlx_texture_t	*txtr;
	mlx_image_t		*img;
	bool			already_extracted;
}	t_texture;

typedef struct s_floor_roof
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	bool			already_extracted;
}	t_floor_roof;

typedef struct s_level
{
	int		max_x;
	int		max_y;
	bool	game_started;
}	t_level;

// point object [x, y].
typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_bpos
{
	double	x;
	double	y;
}	t_bpos;

typedef struct s_bdir
{
	double	x;
	double	y;
}	t_bdir;

typedef struct s_plane
{
	t_bpos	pos;
	t_bdir	dir;
}	t_plane;

typedef struct s_raw_img
{
	mlx_texture_t	*txtr;
	mlx_image_t		*img;
}	t_raw_img;

typedef struct s_button
{
	mlx_texture_t	*txtr;
	mlx_image_t		*img;
	bool			hoverd;
}	t_button;

typedef struct s_mv
{
	t_pos	diff;
	t_bpos	w;
	t_pos	map;
	char	cell;
	int		pixel_dist;
}	t_mv;

typedef struct ui_anim
{
	t_raw_img	*frames;
	int			frame_count;
	int			current;
	bool		active;
	long		last_frame_time;
	int			frame_delay;
}	t_ui_anim;

typedef enum e_gun_type
{
	JESSE_SLINGER,
	CHORUS_MP42,
	OUSSMAC_37MM
}	t_gun_type;

typedef struct s_gun
{
	t_raw_img	idle;
	t_raw_img	aim;
	t_ui_anim	shoot;
	t_ui_anim	reload;
	bool		aiming;
	int			ammo;
	int			max_ammo;
	int			damage;
	t_gun_type	type;
}	t_gun;

typedef struct s_med_kit
{
	t_raw_img	img;
	t_bpos		pos;
	bool		picked;
	int			hp;
	float		size_scale;
	float		vertical_offset;
	int			sprite_width;
	int			sprite_height;
	int			stripe_count;
}	t_med_kit;

typedef struct s_enemy	t_enemy;

typedef struct s_player
{
	t_pos		pos;
	t_bpos		bpos;
	t_bdir		bdir;
	char		dir;
	t_bpos		new_pos;
	t_plane		camera_plane;
	double		pitch;
	int			health;
	t_gun		gun;
	bool		is_shooting;
	t_character	character;
	bool		is_dead;
	bool		has_won;
	t_enemy		*last_killer;
}	t_player;

typedef struct s_minimap
{
	t_pos		pos;
	mlx_image_t	*img;
}	t_minimap;

typedef struct s_keys
{
	bool	pressed[KEYS_NUMBER];
}	t_keys;

typedef struct s_main_menu
{
	t_raw_img	bg;
	t_raw_img	title;
	t_button	b_start;
	t_button	b_chars;
	t_button	b_exit;
	t_button	b_start_hv;
	t_button	b_chars_hv;
	t_button	b_exit_hv;
	int			button_index;
}	t_main_menu;

typedef struct s_characters_ui
{
	t_raw_img	bg;
	t_raw_img	selected;
	t_character	select_index;
	t_button	b_jesse;
	t_button	b_chorus;
	t_button	b_oussmac;
	t_button	b_jesse_hv;
	t_button	b_chorus_hv;
	t_button	b_oussmac_hv;
	int			button_index;
}	t_characters_ui;

typedef struct s_game_ui
{
	t_raw_img	gun;
	t_raw_img	gun_aim;
	t_raw_img	no_ammo;
	t_raw_img	health;
	t_raw_img	health_bg;
	t_raw_img	game_over;
	t_raw_img	game_won;
}	t_game_ui;

// Enemy Types.
typedef enum e_enemy_type
{
	FT_SKIN_WALKER,
	MEMORY_LEAK,
	SEGV,
}	t_enemy_type;

# define CHASE_DISTANCE 4.0
# define LOSE_DISTANCE 45.0
# define ATTACK_DISTANCE 1.5
# define ENEMY_ANIM_RATE 8

# define SKIN_WALKER_W1 "txt/enemy/animation_enemy/x/garbage_value_walk_1.png"
# define SKIN_WALKER_W2 "txt/enemy/animation_enemy/x/garbage_value_walk_2.png"
# define SKIN_WALKER_W3 "txt/enemy/animation_enemy/x/garbage_value_walk_3.png"
# define SKIN_WALKER_A1 "txt/enemy/animation_enemy/x/garbage_value_attack_1.png"
# define SKIN_WALKER_A2 "txt/enemy/animation_enemy/x/garbage_value_attack_2.png"
# define SKIN_WALKER_A3 "txt/enemy/animation_enemy/x/garbage_value_attack_3.png"
# define SKIN_WALKER_D1 "txt/enemy/animation_enemy/x/garbage_value_death_1.png"
# define SKIN_WALKER_D2 "txt/enemy/animation_enemy/x/garbage_value_death_2.png"

# define MEMORY_LEAK_W1 "txt/enemy/animation_enemy/y/memleak_walk_1.png"
# define MEMORY_LEAK_W2 "txt/enemy/animation_enemy/y/memleak_walk_2.png"
# define MEMORY_LEAK_W3 "txt/enemy/animation_enemy/y/memleak_walk_3.png"
# define MEMORY_LEAK_A1 "txt/enemy/animation_enemy/y/memleak_attack_1.png"
# define MEMORY_LEAK_A2 "txt/enemy/animation_enemy/y/memleak_attack_2.png"
# define MEMORY_LEAK_A3 "txt/enemy/animation_enemy/y/memleak_attack_3.png"
# define MEMORY_LEAK_D1 "txt/enemy/animation_enemy/y/memleak_death_1.png"
# define MEMORY_LEAK_D2 "txt/enemy/animation_enemy/y/memleak_death_2.png"

# define SEGV_W1 "txt/enemy/animation_enemy/z/segfault_walk_1.png"
# define SEGV_W2 "txt/enemy/animation_enemy/z/segfault_walk_2.png"
# define SEGV_W3 "txt/enemy/animation_enemy/z/segfault_walk_3.png"
# define SEGV_A1 "txt/enemy/animation_enemy/z/segfault_attack_1.png"
# define SEGV_A2 "txt/enemy/animation_enemy/z/segfault_attack_2.png"
# define SEGV_A3 "txt/enemy/animation_enemy/z/segfault_attack_3.png"
# define SEGV_D1 "txt/enemy/animation_enemy/z/segfault_death_1.png"
# define SEGV_D2 "txt/enemy/animation_enemy/z/segfault_death_2.png"
# define DEATH_ANIMATION_DURATION 20
# define HIGHLIGHT_FRAMES 3
# define MEDKIT "txt/enemy/med_kit.png"

typedef enum e_enemy_state
{
	ENEMY_PATROL,
	ENEMY_CHASE,
	ENEMY_ATTACK,
	ENEMY_RETURN
}	t_enemy_state;

typedef struct s_enemy
{
	t_pos			pos;
	t_bpos			b_pos;
	t_bdir			dir;
	t_enemy_type	type;
	t_raw_img		skin;
	int				health;
	int				damage;
	bool			dead;
	t_enemy_state	state;
	t_bpos			patrol_origin;
	double			chase_speed;
	double			patrol_speed;
	t_raw_img		*walk1;
	t_raw_img		*walk2;
	t_raw_img		*walk3;
	t_raw_img		*attack1;
	t_raw_img		*attack2;
	t_raw_img		*attack3;
	mlx_image_t		*anim_img;
	int				anim_frame;
	int				anim_counter;
	int				attack_cooldown;
	bool			is_attacking;
	int				attack_anim_counter;
	t_raw_img		*death1;
	t_raw_img		*death2;
	bool			is_dying;
	int				death_anim_frame;
	int				death_anim_counter;
	int				death_timer;
	bool			is_highlighted;
	int				highlight_timer;
	t_bpos			patrol_target;
	int				patrol_target_timer;
	int				patrol_change_interval;
}	t_enemy;

typedef struct s_enemy_draw_data
{
	t_enemy		*enemy;
	double		distance;
	bool		visible;
	t_bpos		transform;
	int			sprite_screen_x;
	int			sprite_height;
	int			sprite_width;
}	t_enemy_draw_data;

typedef struct s_sh
{
	t_raw_img	skin_walker_default;
	t_raw_img	memory_leak_default;
	t_raw_img	segv_default;
	t_raw_img	skin_walker_walk[3];
	t_raw_img	skin_walker_attack[3];
	t_raw_img	skin_walker_death[2];
	bool		skin_walker_initialized;
	t_raw_img	memory_leak_walk[3];
	t_raw_img	memory_leak_attack[3];
	t_raw_img	memory_leak_death[2];
	bool		memory_leak_initialized;
	t_raw_img	segv_walk[3];
	t_raw_img	segv_attack[3];
	t_raw_img	segv_death[2];
	bool		segv_initialized;
	bool		initialized;
}	t_sh;

#include "miniaudio.h"

typedef struct s_audio
{
    ma_engine       engine;
    ma_sound        bg_music;
    bool            bg_music_playing;
}   t_audio;

typedef struct s_pd
{
	char			**map_file;
	int				fd;
	t_texture		txtr_no;
	t_texture		txtr_so;
	t_texture		txtr_we;
	t_texture		txtr_ea;
	t_floor_roof	floor;
	t_floor_roof	roof;
	char			**map_grid;
	int				player_count;
	t_level			level;
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*screen;
	t_minimap		minimap;
	t_keys			keys;
	t_main_menu		menu;
	t_characters_ui	chars_menu;
	t_game_ui		game_ui;
	int				ui_index;
	bool			mouse_clicked;
	t_pos			mouse;
	t_enemy			*enemies;
	uint8_t			enemy_count;
	t_raw_img		door_txt;
	t_med_kit		*medkits;
	t_raw_img		medkit;
	int				medkit_count;
	int				max_medkits;
	double			*zbuffer;
	t_sh			sh;
	int				enemy_count_r;
	__uint32_t		floor_color;
	__uint32_t		roof_color;
	t_audio     audio;
}	t_parsed_data;

typedef struct s_cube
{
	char			*map_path;
	t_parsed_data	pd;
}	t_cube;

void    audio_init(t_parsed_data *pd);
void    audio_init(t_parsed_data *pd);
void    audio_cleanup(t_parsed_data *pd);
void    play_bg_music(t_parsed_data *pd, const char *path);
void    stop_bg_music(t_parsed_data *pd);
void    play_sound_once(t_parsed_data *pd, const char *path);
void    start_loop_sound(t_parsed_data *pd, ma_sound *snd, const char *path);
void    play_enemy_sound_3d(t_parsed_data *pd, t_enemy *e,
                            const char *path);
void    stop_loop_sound(ma_sound *snd);

// Validate input args.
size_t					ft_strlen(char *str);
void					print_error(char *str);
void					print_comm(char *str);
void					evaluate_input(int argc, char **argv);
// Map parser.
void					parse_map(char *map_path, t_cube *cube);
bool					duplicated_floor_roof(char type, t_cube *cube);
void					init_parsed_textures(t_cube *cube);
void					init_parsed_data(t_cube *cube);
char					*ft_strdup(char *s1);
// Garbage Collector.
void					*allocate_gc(void *ptr);
void					mind_free_all(int status);
void					delete_all_textures(t_parsed_data *pd);
void					delete_player_textures(t_parsed_data *pd);
void					delete_main_menu_textures(t_parsed_data *pd);
void					delete_screen_and_map(t_parsed_data *pd);
void					delete_characters_ui_textures(t_parsed_data *pd);
void					delete_game_ui_textures(t_parsed_data *pd);
void					delete_door_wall_textures(t_parsed_data *pd);
void					set_pd(t_parsed_data *new_pd);
t_parsed_data			**get_pd(void);
// GNL
char					*get_next_line(int fd);
char					*gnl_ft_strdup(char *s1);
size_t					gnl_ft_strlen(const char *s);
char					*gnl_ft_strjoin(char *s1, char *s2);
char					*gnl_ft_strchr(const char *s, int c);
char					*gnl_ft_substr(char *s, unsigned int start, size_t len);
// Validate map.
void					validate_map(char **map_file, t_cube *cube);
void					validate_params(char **map_file, t_cube *cube);
void					invalid_params(void);
char					**tab_split(char *s, char *sep);
char					*ft_strchr(char			*s, int c);
int						ft_strcmp(char *s1, char *s2);
size_t					arg_count(char **argv);
char					*ft_substr(char *s, size_t start, size_t len);
bool					validate_floor_roof(char *str);
bool					validate_floor_roof(char *str);
bool					is_num(char *str);
int						ft_atoi(const char *str);
void					extarct_floor_roof(char *str, t_cube *cube);
char					**trim_newlines(char **old_argv);
bool					valid_grid_chars(char *str,
							int *player_count, bool map_grid);
void					extract_map(char **map_file,
							int *i, t_cube *cube);
void					closed_bounds(t_cube *cube);
void					get_level_data(t_cube *cube);
void					get_player_pos(char **map_grid,
							int *x, int *y, char *dir);
void					flood_fill(char **grid, t_pos pos,
							t_pos max, int *enemy_count);
char					**grid_dup(char **grid);
bool					is_door(char c);
bool					validate_door(t_parsed_data *pd, int x, int y);
void					scrap_enemy_data(int x, int y,
							char c, t_enemy *curr_enemy);
void					init_all_textures(t_parsed_data *pd);
void					game_loop(t_parsed_data *pd);
void					game_render(void *param);
void					draw_minimap(t_parsed_data *pd);
bool					enemy_icon(double x, double y,
							t_parsed_data *pd);
void					handle_player_input(mlx_key_data_t keydata,
							void *param);
void					update_player_data(t_parsed_data *pd);
void					update_player_movement(t_parsed_data *pd);
double					get_move_speed(t_parsed_data *pd,
							double speed);
void					player_pitch(t_parsed_data *pd);
void					reload_gun(t_parsed_data *pd);
void					update_health_ui(t_parsed_data *pd);
void					interact_with_door(t_parsed_data *pd);
bool					cool_down(long usec);
// Player Input
void					player_movement(t_parsed_data *pd);
void					player_rotation(t_parsed_data *pd);
void					game_mouse_input(mouse_key_t button,
							action_t action, modifier_key_t mods,
							t_parsed_data *pd);
void					trigger_reload_anim(t_parsed_data *pd);
long					current_time_ms(void);
void					keyboard_shoot(t_parsed_data *pd);
// Init For Gameloop
void					init_enemy_textures(t_parsed_data *pd);
void					init_animation_frames(t_parsed_data *pd, int i);
void					free_enemy_textures(t_parsed_data *pd);
void					init_precise_data(t_parsed_data *pd);
void					init_medkits(t_parsed_data *pd);
void					init_screen_and_map(t_parsed_data *pd);
void					init_door_wall(t_parsed_data *pd);
void					init_medkit_textures(t_parsed_data *pd);
void					init_enemy_textures_to_null(t_parsed_data *pd);
void					init_door_texture(t_parsed_data *pd);
void					init_shared_textures(t_parsed_data *pd);
void					free_sh_txtrs(t_parsed_data *pd);
void					init_shared_attack_null(t_parsed_data *pd);
void					init_default_skins(t_parsed_data *pd);
void					init_sh(t_parsed_data *pd);
// Raycast
void					update_raycast_data(t_parsed_data *pd);
void					raycast_render(t_parsed_data *pd);
// UI
void					init_main_menu(t_parsed_data *pd);
void					main_menu(t_parsed_data *pd);
void					handle_ui_input(mlx_key_data_t keydata,
							t_parsed_data *pd);
void					ui_error(void);
void					init_characters_menu(t_parsed_data *pd);
void					characters_menu(t_parsed_data *pd);
void					handle_mouse_input(double xpos,
							double ypos, void *param);
void					handle_mouse_click(mouse_key_t button,
							action_t action, modifier_key_t mods, void *param);
void					menu_trigger_click(t_parsed_data *pd);
void					characters_trigger_click(t_parsed_data *pd);
void					toggle_game_ui(t_parsed_data *pd);
void					init_radar(t_parsed_data *pd);
void					render_radar(t_parsed_data *pd);
void					render_player_icon(t_parsed_data *pd);
void					draw_minimap_grid(t_parsed_data *pd);
int						sqr(int x);
void					update_ui_anim(t_ui_anim *anim);
void					render_gun(t_parsed_data *pd);
void					setup_character(t_parsed_data *pd);
void					set_gun_stats(t_parsed_data *pd);
void					setup_health_ui(t_parsed_data *pd);
void					load_gun_shoot_anim(t_parsed_data *pd,
							t_character character);
void					load_gun_reload_anim(t_parsed_data *pd,
							t_character character);
void					delete_gun_textures(t_parsed_data *pd);
void					update_health_ui(t_parsed_data *pd);
int						ft_rand(void);

typedef struct s_ray_dir_data
{
	t_player		*pl;
	t_plane			*cam;
	int				x;
	int				w;
	t_bdir			*ray_dir;
}	t_ray_dir_data;

typedef struct s_step_data
{
	t_bdir		ray_dir;
	t_bpos		delta_dist;
	t_pos		map;
	t_pos		*step;
	t_bpos		*side_dist;
}	t_step_data;

typedef struct s_dda_data
{
	t_parsed_data	*pd;
	t_pos			*map;
	t_bpos			*side_dist;
	t_bpos			delta_dist;
	t_pos			step;
	int				*side;
}	t_dda_data;

typedef struct s_perp_data
{
	t_pos		map;
	t_bpos		pos;
	t_pos		step;
	t_bdir		ray_dir;
	int			side;
}	t_perp_data;

typedef struct s_line_data
{
	int	height;
	int	draw_start;
	int	draw_end;
}	t_line_data;

typedef struct s_column_data
{
	t_parsed_data	*pd;
	int				x;
	int				h;
	double			perp_dist;
	t_bdir			ray_dir;
	t_bpos			player_pos;
	t_bpos			pos;
	int				side;
	t_pos			map;
}	t_column_data;

typedef struct s_ray_data
{
	t_bdir		ray_dir;
	t_bpos		player_pos;
	t_pos		map;
	t_bpos		delta_dist;
	t_pos		step;
	t_bpos		side_dist;
	int			side;
}	t_ray_data;

typedef struct s_texture_data
{
	mlx_texture_t	*texture;
	double			perp_dist;
	int				side;
	t_bdir			ray_dir;
	t_bpos			pos;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
}	t_texture_data;

typedef struct s_draw_bounds
{
	int	draw_start_y;
	int	draw_end_y;
	int	draw_start_x;
	int	draw_end_x;
	int	orig_draw_start_x;
	int	orig_draw_start_y;
}	t_draw_bounds;

typedef struct s_draw_context
{
	t_parsed_data		*pd;
	t_enemy_draw_data	*curr;
	t_draw_bounds		*b;
}	t_draw_context;

typedef struct s_tex_sample
{
	uint32_t		color;
	unsigned char	alpha;
	int				ok;
}	t_tex_sample;

typedef struct s_enemy_calc
{
	t_bpos	rel_pos;
	t_bpos	transform;
	double	distance;
}	t_enemy_calc;

typedef struct s_enemy_ctx
{
	t_parsed_data	*pd;
	t_enemy			*enemy;
	int				index;
	double			distance;
	bool			visible;
}	t_enemy_ctx;

typedef struct s_door_column
{
	t_parsed_data	*pd;
	int				x;
	t_line_data		*line;
	double			perp_dist;
	int				side;
	t_bdir			ray_dir;
	t_bpos			pos;
	char			tile_char;
	mlx_texture_t	*tx;
	int				tex_w;
	int				tex_h;
	int				screen_h;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
}	t_door_column;

typedef struct s_texture_column
{
	t_parsed_data	*pd;
	int				x;
	t_line_data		*line;
	double			perp_dist;
	int				side;
	t_bdir			ray_dir;
	t_bpos			pos;
	mlx_texture_t	*tx;
	int				tex_w;
	int				tex_h;
	int				screen_h;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
}	t_texture_column;

typedef struct s_medkit_draw_data
{
	t_med_kit		*medkit;
	double			distance;
	t_bpos			transform;
	int				sprite_screen_x;
	int				sprite_height;
	int				sprite_width;
	int				v_offset_pixels;
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start_y;
	int				draw_end_y;
	int				stripe;
	int				y;
	int				tex_x;
	int				tex_y;
	t_tex_sample	tmp_sample;
}	t_medkit_draw_data;

typedef struct s_move_ctx
{
	double	step_x;
	double	step_y;
	double	alt_step;
	int		steps;
	int		s;
	bool	moved;
}	t_move_ctx;

void					draw_medkits(t_parsed_data *pd);
void					spawn_medkit(t_parsed_data *pd,
							t_bpos pos, t_enemy_type type);
void					check_medkit_pickup(t_parsed_data *pd);
void					draw_medkits(t_parsed_data *pd);
void					get_enemies(t_cube *cube);
void					draw_enemies(t_parsed_data *pd);
bool					has_line_of_sight(t_parsed_data *pd,
							t_bpos start, t_bpos end);
int						collect_and_sort_enemies_small(t_parsed_data *pd,
							t_enemy_draw_data *draw_data);
void					draw_single_enemy(t_parsed_data *pd,
							t_enemy_draw_data *curr, int horizon);
t_tex_sample			sample_texture_pixel(mlx_image_t *img, int tx, int ty);
void					handle_shooting_once(t_parsed_data *pd,
							t_enemy_draw_data *draw_data, int draw_count);
void					update_all_death_animations(t_parsed_data *pd);
void					update_death_animation(t_parsed_data *pd,
							t_enemy *enemy);
void					change_enemy_direction(t_enemy *enemy);
void					calculate_direction_to_player(t_enemy *enemy,
							t_bpos player_pos, t_bpos *direction);
bool					is_valid_move_position_circle_global(t_parsed_data *pd,
							double x, double y);
void					set_alternative_directions(t_bpos alternatives[8],
							t_bpos direction);
bool					return_to_patrol(t_enemy *enemy, t_parsed_data *pd);
void					smart_chase_player(t_enemy *enemy, t_bpos player_pos,
							double speed, t_parsed_data *pd);
double					calculate_distance_to_player(t_enemy *enemy,
							t_parsed_data *pd);
bool					is_position_blocked_circle(t_parsed_data *pd,
							double cx, double cy, double radius);
void					perform_patrol_movement(t_enemy *enemy,
							t_parsed_data *pd);
void					handle_patrol_state(t_enemy_ctx *ctx);
void					handle_enemy_state(t_enemy_ctx *ctx);
void					update_attack_animation(t_enemy *enemy);
void					update_walk_animation(t_enemy *enemy);
void					draw_wall(t_parsed_data *pd, int x,
							t_line_data *line, uint32_t wall_col);
mlx_texture_t			*get_wall_texture(t_parsed_data *pd,
							int side, t_bdir ray_dir);
uint32_t				darken_color(uint32_t c);
void					draw_ceiling(t_parsed_data *pd,
							int x, int draw_start, int horizon);
void					draw_floor(t_parsed_data *pd,
							int x, int draw_end, int horizon);
void					init_texture_column(t_texture_column *tc);
void					setup_texture_stepping(t_texture_column *tc);
uint32_t				get_pixel_color(t_texture_column *tc, int tex_y);
uint32_t				get_door_pixel_color(t_door_column *dc, int tex_y);
void					draw_texture_pixels(t_texture_column *tc);
void					draw_textured_column(t_parsed_data *pd,
							t_column_data *col, t_line_data *line);
mlx_texture_t			*get_door_texture(t_parsed_data *pd);
void					init_door_column(t_door_column *dc);
void					setup_door_stepping(t_door_column *dc);
void					draw_door_pixels(t_door_column *dc);
void					draw_door_column(t_parsed_data *pd,
							t_column_data *col, t_line_data *line);
void					compute_delta_dist(t_bdir ray_dir,
							t_bpos *delta_dist);
void					set_x_step(t_bpos pos, t_pos map,
							t_bdir ray_dir, t_step_data *data);
void					set_y_step(t_bpos pos, t_pos map,
							t_bdir ray_dir, t_step_data *data);
void					init_step_and_sidedist(t_bpos player,
							t_step_data *data);
void					update_x_side(t_dda_data *data);
void					update_y_side(t_dda_data *data);
bool					is_wall_hit(t_parsed_data *pd, t_pos map);
void					perform_dda(t_parsed_data *pd, t_dda_data *data);
double					calc_x_perp_dist(t_pos map, t_bpos pos,
							t_pos step, t_bdir ray_dir);
double					calc_y_perp_dist(t_pos map, t_bpos pos,
							t_pos step, t_bdir ray_dir);
double					compute_perp_wall_dist(t_perp_data *data);
void					calc_line_params(int h, double perp_dist,
							t_line_data *line, t_parsed_data *pd);
void					draw_column(t_parsed_data *pd, t_column_data *col);
void					set_ray_dir(t_ray_dir_data *data);
void					init_ray_data(t_ray_data *ray,
							t_player *pl, int x, int w);
void					init_dda_data(t_parsed_data *pd,
							t_ray_data *ray, t_dda_data *dda_data);
void					init_perp_and_col_data(t_parsed_data *pd,
							int x, t_ray_data *ray, t_column_data *col_data);
void					cast_single_ray(t_parsed_data *pd, int x);
void					raycast_render(t_parsed_data *pd);
void					draw_enemies(t_parsed_data *pd);
void					handle_patrol_state(t_enemy_ctx *ctx);
bool					move_towards_target(t_enemy *enemy,
							t_parsed_data *pd, t_bpos target, double speed);
uint32_t				shade_color(uint32_t base_col,
							double dist, double magnitude);
void					update_enemies(t_parsed_data *pd);
void					spawn_medkit(t_parsed_data *pd,
							t_bpos pos, t_enemy_type type);
void					check_medkit_pickup(t_parsed_data *pd);
bool					medkit_visible(t_parsed_data *pd,
							t_med_kit *medkit, t_medkit_draw_data *out);
bool					all_enemies_dead(t_parsed_data *pd);
void					calculate_draw_bounds(t_enemy_draw_data *curr,
							int horizon, t_draw_bounds *b);
int						find_current_direction(t_enemy *enemy,
							double directions[4][2]);
uint32_t				tint_with_red(uint32_t color, float red_percentage);
t_enemy_draw_data		*find_shot_target(t_enemy_draw_data *draw_data,
							int draw_count, double center_tolerance);
void					apply_damage_to_enemy(t_parsed_data *pd,
							t_enemy *enemy);
int						is_valid_enemy(t_enemy_draw_data *data);
double					dist2(t_bpos a, t_bpos b);
void					perform_patrol_movement(t_enemy *enemy,
							t_parsed_data *pd);
bool					is_diagonal_gap(t_parsed_data *pd,
							t_bpos from, t_bpos to);
bool					try_axis_moves(t_enemy *enemy,
							t_parsed_data *pd, double nx, double ny);
bool					attempt_one_step(t_enemy *enemy,
							t_parsed_data *pd, t_bpos dir, t_move_ctx *ctx);
bool					perform_move_steps(t_enemy *enemy,
							t_parsed_data *pd, t_bpos dir, double speed);
bool					move_towards_target(t_enemy *enemy,
							t_parsed_data *pd, t_bpos target, double speed);
void					handle_patrol_attempt(t_enemy *enemy, t_parsed_data *pd,
							t_bpos target, int *stuck_counter);
void					handle_patrol_state(t_enemy_ctx *ctx);
bool					try_alternative_directions(t_enemy *enemy,
							t_parsed_data *pd, t_bpos direction, double speed);
bool					choose_random_patrol_target(t_enemy *enemy,
							t_parsed_data *pd);
void					set_death_frame(t_enemy *enemy);
int						calculate_new_direction(int current_dir_index);
void					setup_door_stepping(t_door_column *dc);
mlx_texture_t			*get_door_texture(t_parsed_data *pd);
int						medkit_drop_chance(t_enemy_type type);
bool					should_drop_medkit(t_enemy_type type);
void					sort_medkits_by_distance(t_medkit_draw_data *draw_data,
							int draw_count);
void					print_death_message(t_parsed_data *pd,
							t_enemy *killer, bool deceptive);

# define FLOOR 0x876D46FF
# define WALL_SIDE 0xCC9D44FF
# define WALL 0xA37D36FF
# define FLOOR_FALLOF 0.0065
# define ROOF_FALLOF 0.0042
# define WALLS_FALLOF 0.35
# define SHIFT_FLOOR_SHADE 100

# define SKIN_WALKER_HEALTH 42
# define MEMORY_LEAK_HEALTH 70
# define SEGV_HEALTH 101

# define SKIN_WALKER_DAMAGE 15
# define MEMORY_LEAK_DAMAGE 20
# define SEGV_DAMAGE 37

# define SKIN_WALKER_PATROL_SPEED 0.04
# define MEMORY_LEAK_PATROL_SPEED 0.08
# define SEGV_PATROL_SPEED 0.1

# define SKIN_WALKER_CHASE_SPEED 0.06
# define MEMORY_LEAK_CHASE_SPEED 0.1
# define SEGV_CHASE_SPEED 0.12

# define COLLISION_RADIUS 0.25
# define PATROL_TARGET_RADIUS 3.0 
# define PATROL_REACHED_EPS 0.35 
# define M_PI 3.14159265358979323846

#endif
