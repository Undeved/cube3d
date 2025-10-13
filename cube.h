/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:29:41 by oimzilen          #+#    #+#             */
/*   Updated: 2025/10/13 15:47:40 by oukhanfa         ###   ########.fr       */
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
# define MINI_MAP_SIZE 300
# define MINI_MAP_Y 20
# define MINI_MAP_X (WIDTH - MINI_MAP_SIZE - MINI_MAP_Y)
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
# define SPEED 0.155;
# define STRAFE_SPEED 0.095
# define ROT_SPEED 0.12
# define NUDGE_FROM_WALL 0.5
# define MOUSE_SENSITIVITY 0.00088
# define PI 3.14159
# define PITCH_SPEED 30
# define MAX_PITCH  (HEIGHT / 2) - 330
# define MIN_PITCH  (-HEIGHT / 2) + 490
# define SCALER 0.3
# define FOV 60

// player stats
# define PLAYER_HEALTH 100


# define COLLISION 0.1

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

# define TRN_OFST 30

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
# define VIGNETTE "textures/ui/in_game/vignette.png"
# define GAME_OVER "textures/ui/in_game/game_over.png"

// door texture
# define DOOR_TEXTURE "textures/wall_textures/door.png"

// Gun textures -----------------------------------------------------------
# define GUN_JESSE_IDLE "textures/ui/in_game/gun/gun_idle.png"
# define GUN_JESSE_AIM "textures/ui/in_game/gun/gun_aim.png"

// Gun shoot anim
# define GUN_JESSE_SHOOT_1 "textures/ui/in_game/gun/gun_aim_shoot_anim/gun_aim_shoot_1.png"
# define GUN_JESSE_SHOOT_2 "textures/ui/in_game/gun/gun_aim_shoot_anim/gun_aim_shoot_2.png"
# define GUN_JESSE_SHOOT_3 "textures/ui/in_game/gun/gun_aim_shoot_anim/gun_aim_shoot_3.png"
# define GUN_JESSE_SHOOT_4 "textures/ui/in_game/gun/gun_aim_shoot_anim/gun_aim_shoot_4.png"
# define GUN_SHOOT_FRMS 4

// Gun reload anim
# define GUN_JESSE_RELOAD_1 "textures/ui/in_game/gun/gun_reload_anim/gun_reload_1.png"
# define GUN_JESSE_RELOAD_2 "textures/ui/in_game/gun/gun_reload_anim/gun_reload_2.png"
# define GUN_JESSE_RELOAD_3 "textures/ui/in_game/gun/gun_reload_anim/gun_reload_3.png"
# define GUN_JESSE_RELOAD_4 "textures/ui/in_game/gun/gun_reload_anim/gun_reload_4.png"
# define GUN_JESSE_RELOAD_5 "textures/ui/in_game/gun/gun_reload_anim/gun_reload_5.png"
# define GUN_JESSE_RELOAD_6 "textures/ui/in_game/gun/gun_reload_anim/gun_reload_6.png"
# define GUN_RELOAD_FRMS 6

// Chorus gun textures
# define GUN_CHORUS_IDLE "textures/ui/in_game/gun_chorus/gun_idle.png"
# define GUN_CHORUS_AIM "textures/ui/in_game/gun_chorus/gun_aim.png"
# define GUN_CHORUS_SHOOT_1 "textures/ui/in_game/gun_chorus/gun_aim_shoot_anim/gun_aim_shoot_1.png"
# define GUN_CHORUS_SHOOT_2 "textures/ui/in_game/gun_chorus/gun_aim_shoot_anim/gun_aim_shoot_2.png"
# define GUN_CHORUS_SHOOT_3 "textures/ui/in_game/gun_chorus/gun_aim_shoot_anim/gun_aim_shoot_3.png"
# define GUN_CHORUS_SHOOT_4 "textures/ui/in_game/gun_chorus/gun_aim_shoot_anim/gun_aim_shoot_4.png"
# define GUN_CHORUS_RELOAD_1 "textures/ui/in_game/gun_chorus/gun_reload_anim/gun_reload_1.png"
# define GUN_CHORUS_RELOAD_2 "textures/ui/in_game/gun_chorus/gun_reload_anim/gun_reload_2.png"
# define GUN_CHORUS_RELOAD_3 "textures/ui/in_game/gun_chorus/gun_reload_anim/gun_reload_3.png"
# define GUN_CHORUS_RELOAD_4 "textures/ui/in_game/gun_chorus/gun_reload_anim/gun_reload_4.png"          
# define GUN_CHORUS_RELOAD_5 "textures/ui/in_game/gun_chorus/gun_reload_anim/gun_reload_5.png"
# define GUN_CHORUS_RELOAD_6 "textures/ui/in_game/gun_chorus/gun_reload_anim/gun_reload_6.png"
// Oussmac gun textures
# define GUN_OUSSMAC_IDLE "textures/ui/in_game/gun_oussmac/gun_idle.png"
# define GUN_OUSSMAC_AIM "textures/ui/in_game/gun_oussmac/gun_aim.png"
# define GUN_OUSSMAC_SHOOT_1 "textures/ui/in_game/gun_oussmac/gun_aim_shoot_anim/gun_aim_shoot_1.png"
# define GUN_OUSSMAC_SHOOT_2 "textures/ui/in_game/gun_oussmac/gun_aim_shoot_anim/gun_aim_shoot_2.png"
# define GUN_OUSSMAC_SHOOT_3 "textures/ui/in_game/gun_oussmac/gun_aim_shoot_anim/gun_aim_shoot_3.png"
# define GUN_OUSSMAC_SHOOT_4 "textures/ui/in_game/gun_oussmac/gun_aim_shoot_anim/gun_aim_shoot_4.png"
# define GUN_OUSSMAC_RELOAD_1 "textures/ui/in_game/gun_oussmac/gun_reload_anim/gun_reload_1.png"
# define GUN_OUSSMAC_RELOAD_2 "textures/ui/in_game/gun_oussmac/gun_reload_anim/gun_reload_2.png"
# define GUN_OUSSMAC_RELOAD_3 "textures/ui/in_game/gun_oussmac/gun_reload_anim/gun_reload_3.png"
# define GUN_OUSSMAC_RELOAD_4 "textures/ui/in_game/gun_oussmac/gun_reload_anim/gun_reload_4.png"          
# define GUN_OUSSMAC_RELOAD_5 "textures/ui/in_game/gun_oussmac/gun_reload_anim/gun_reload_5.png"
# define GUN_OUSSMAC_RELOAD_6 "textures/ui/in_game/gun_oussmac/gun_reload_anim/gun_reload_6.png"

// Health_UI textures
# define HEALTH_BAR "textures/ui/in_game/health/health_bar.png"
// health backgrounds
# define HP_JESSE "textures/ui/in_game/health/jesse_health_bar.png"
# define HP_CHORUS "textures/ui/in_game/health/chorus_health_bar.png"
# define HP_OUSSMAC "textures/ui/in_game/health/oussmac_health_bar.png"

# define HBAR_X 1625
# define HBAR_Y 342
# define HBAR_BG_X 1592
# define HBAR_BG_Y 298


# define SKIN_WALKER_DFL "textures/enemy_textures/animation_enemy/x/Himp-IDLE.png"
# define MEMORY_LEAK_DFL "textures/enemy_textures/animation_enemy/y/CacoDemon-Walk1.png"
# define SEGV_DFL "textures/enemy_textures/animation_enemy/z/Reaper-Walk1.png"

# define GUN_X 767
# define GUN_Y 432
# define GUN_AIM_X 383
# define GUN_AIM_Y 431
# define AMMO 30
# define DAMAGE 10

# define MAX_ENEMIES 20


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
    mlx_texture_t   *txtr;
    mlx_image_t     *img;
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

// point object [x, y].
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

typedef struct s_plane
{
    t_bpos  pos;
    t_bdir  dir;
}   t_plane;

typedef struct s_raw_img
{
    mlx_texture_t       *txtr;
    mlx_image_t     *img;
}   t_raw_img;

typedef struct s_button
{
    mlx_texture_t       *txtr;
    mlx_image_t         *img;
    bool            hoverd;
}   t_button;

typedef struct ui_anim
{
	t_raw_img   *frames;
	int         frame_count;

	// animation state
	int         current;
	bool        active;
	long        last_frame_time;
	int         frame_delay; // ms per frame
}	t_ui_anim;

typedef enum e_gun_type
{
    JESSE_SLINGER,
    CHORUS_MP42,
    OUSSMAC_37MM
}   gun_type;


typedef struct s_gun
{
    t_raw_img   idle;
    t_raw_img   aim;
    t_ui_anim   shoot;
    t_ui_anim   reload;
    bool        aiming;
    int         ammo;
    int         damage;
    gun_type      type;
}   t_gun;


typedef struct s_med_kit
{
    t_raw_img   img;
    t_bpos       pos;
    bool        picked;
    int         hp_trmat_oussmac;
    float       size_scale; 
    float       vertical_offset;
}   t_med_kit;

typedef struct s_player
{
    t_pos   pos;
    t_bpos  bpos;
    t_bdir  bdir;
    char    dir;
    t_bpos  new_pos;
    t_plane camera_plane;
    double  pitch;
    int     health;
    t_gun   gun;
    bool    is_shooting;
    t_character character;
    bool    is_dead;
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

typedef struct s_game_ui
{
    t_raw_img           vignette;
    t_raw_img           gun;
    t_raw_img           gun_aim;
    t_raw_img           health;
    t_raw_img           health_bg;
    t_raw_img           game_over;
}   t_game_ui;


// Enemy Objects [X]

// Enemy Types.
typedef enum e_enemy_type
{
    FT_SKIN_WALKER,
    MEMORY_LEAK,
    SEGV,
}   t_enemy_type;

#define CHASE_DISTANCE 4.0      // Distance at which enemy starts chasing
#define LOSE_DISTANCE 15.0      // Distance at which enemy gives up chase
#define ATTACK_DISTANCE 1.5     // Distance at which enemy can attack
#define ENEMY_ANIM_RATE 8   // ticks per frame (increase = slower animation)
#define SKIN_WALKER_W1 "textures/enemy_textures/animation_enemy/x/Himp-Walk1.png"
#define SKIN_WALKER_W2 "textures/enemy_textures/animation_enemy/x/Himp-Walk2.png"
#define SKIN_WALKER_W3 "textures/enemy_textures/animation_enemy/x/Himp-Walk3.png"
#define SKIN_WALKER_A1 "textures/enemy_textures/animation_enemy/x/HIMP-ATT1.png"
#define SKIN_WALKER_A2 "textures/enemy_textures/animation_enemy/x/HIMP-ATT2.png"
#define SKIN_WALKER_A3 "textures/enemy_textures/animation_enemy/x/HIMP-ATT3.png"
#define SKIN_WALKER_D1 "textures/enemy_textures/animation_enemy/x/Himp-Death1.png"
#define SKIN_WALKER_D2 "textures/enemy_textures/animation_enemy/x/Himp-Death2.png"
#define MEMORY_LEAK_W1 "textures/enemy_textures/animation_enemy/y/CacoDemon-Walk1.png"
#define MEMORY_LEAK_W2 "textures/enemy_textures/animation_enemy/y/CacoDemon-Walk2.png"
#define MEMORY_LEAK_W3 "textures/enemy_textures/animation_enemy/y/CacoDemon-Walk3.png"
#define MEMORY_LEAK_A1 "textures/enemy_textures/animation_enemy/y/CacoDemon-ATT1.png"
#define MEMORY_LEAK_A2 "textures/enemy_textures/animation_enemy/y/CacoDemon-ATT2.png"
#define MEMORY_LEAK_A3 "textures/enemy_textures/animation_enemy/y/CacoDemon-ATT3.png"
#define MEMORY_LEAK_D1 "textures/enemy_textures/animation_enemy/y/CacoDemon-Death1.png"
#define MEMORY_LEAK_D2 "textures/enemy_textures/animation_enemy/y/CacoDemon-Death2.png"
#define SEGV_W1 "textures/enemy_textures/animation_enemy/z/Reaper-Walk1.png"
#define SEGV_W2 "textures/enemy_textures/animation_enemy/z/Reaper-Walk2.png"
#define SEGV_W3 "textures/enemy_textures/animation_enemy/z/Reaper-Walk3.png"
#define SEGV_A1 "textures/enemy_textures/animation_enemy/z/Reaper-ATT1.png"
#define SEGV_A2 "textures/enemy_textures/animation_enemy/z/Reaper-ATT2.png"
#define SEGV_A3 "textures/enemy_textures/animation_enemy/z/Reaper-ATT3.png"
#define SEGV_D1 "textures/enemy_textures/animation_enemy/z/Reaper-Death1.png"
#define SEGV_D2 "textures/enemy_textures/animation_enemy/z/Reaper-Death2.png"
#define DEATH_ANIMATION_DURATION 61 // 3 seconds at 60FPS
#define HIGHLIGHT_FRAMES 3
// Enhanced enemy states
typedef enum e_enemy_state
{
    ENEMY_PATROL,
    ENEMY_CHASE,
    ENEMY_ATTACK,
    ENEMY_RETURN
}   t_enemy_state;

typedef struct s_enemy
{
    t_pos          pos;
    t_bpos          b_pos;
    t_bdir          dir;
    t_enemy_type    type;
    t_raw_img       skin;
    int             health;
    int             damage;
    bool            dead;
    t_enemy_state   state;           // Current behavior state
    t_bpos          patrol_origin;   // Original position to return to
    double          chase_speed;     // Speed when chasing
    double          patrol_speed;    // Speed when patrolling
    t_raw_img       walk1;
    t_raw_img       walk2;
    t_raw_img       walk3;
    t_raw_img       attack1;        // Add attack animation frames
    t_raw_img       attack2;
    t_raw_img       attack3;
    mlx_image_t     *anim_img;    // current image used when drawing (points to one of the imgs)
    int             anim_frame;   // 0..2
    int             anim_counter;
    int             attack_cooldown;
    bool            is_attacking;  // Track if currently in attack animation
    int             attack_anim_counter; // Separate counter for attack animation
    t_raw_img       death1;        // Add death animation frames
    t_raw_img       death2;
    bool            is_dying;      // Track if enemy is in death animation
    int             death_anim_frame;
    int             death_anim_counter;
    int             death_timer;
    bool            is_highlighted;    // true while enemy is highlighted (white)
    int             highlight_timer;
}   t_enemy;

// Structure to hold enemy drawing data for sorting
typedef struct s_enemy_draw_data
{
    t_enemy     *enemy;
    double      distance;
    bool        visible;
    t_bpos      transform;
    int         sprite_screen_x;
    int         sprite_height;
    int         sprite_width;
}   t_enemy_draw_data;

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
    t_game_ui       game_ui;
    int             ui_index;
    bool            mouse_clicked;
    t_pos           mouse;
    t_enemy         *enemies;
    uint8_t         enemy_count;
    t_raw_img       door_txt;
    t_med_kit       *medkits;        // Add this
    int             medkit_count;     // Add this
    int             max_medkits;  
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
char	*ft_itoa(int n);
void     extarct_floor_roof(char *str, t_cube *cube);
char    **trim_newlines(char **old_argv);
bool valid_grid_chars(char *str, int *player_count, bool map_grid);
void    extract_map(char **map_file, int *i, t_cube *cube);
void    closed_bounds(t_cube *cube);
void    get_level_data(t_cube *cube);
void    get_player_pos(char **map_grid, int *x, int *y, char *dir);
void    flood_fill(char **grid, t_pos pos, t_pos max);
char    **grid_dup(char **grid);
bool    is_door(char c);
bool    validate_door(t_parsed_data *pd, int x, int y);

// Game loop.
void    game_loop(t_parsed_data *pd);
void    game_render(void *param);
void    draw_minimap(t_parsed_data *pd);
void    handle_player_input(mlx_key_data_t keydata, void *param);
void    update_player_data(t_parsed_data *pd);
void    update_health_ui(t_parsed_data *pd);
void    interact_with_door(t_parsed_data *pd);

// Raycast
void    update_raycast_data(t_parsed_data *pd);
void    raycast_render(t_parsed_data *pd);

// UI
void    init_main_menu(t_parsed_data *pd);
void    main_menu(t_parsed_data *pd);
void    handle_ui_input(mlx_key_data_t keydata, t_parsed_data *pd);
void    ui_error(void);
void    init_characters_menu(t_parsed_data *pd);
void    characters_menu(t_parsed_data *pd);
void    setup_mouse(t_parsed_data *pd);
void    handle_mouse_input(double xpos, double ypos, void *param);
void    handle_mouse_click(mouse_key_t button, action_t action, modifier_key_t mods, void* param);
void    menu_trigger_click(t_parsed_data *pd);
void    characters_trigger_click(t_parsed_data *pd);
void    toggle_game_ui(t_parsed_data *pd);
void    init_radar(t_parsed_data *pd);
void    render_radar(t_parsed_data *pd);
void    render_player_icon(t_parsed_data *pd);
int     sqr(int x);
void    init_game_ui(t_parsed_data *pd);
void	update_ui_anim(t_ui_anim *anim);
void	render_gun(t_parsed_data *pd);
void    trigger_reload_anim(t_parsed_data *pd);
void    setup_character(t_parsed_data *pd);
void    setup_health_ui(t_parsed_data *pd);

typedef struct s_ray_dir_data
{
    t_player    *pl;
    t_plane        *cam;
    int        x;
    int        w;
    t_bdir        *ray_dir;
}    t_ray_dir_data;

typedef struct s_step_data
{
    t_bdir    ray_dir;
    t_bpos    delta_dist;
    t_pos    map;
    t_pos    *step;
    t_bpos    *side_dist;
}    t_step_data;

typedef struct s_dda_data
{
    t_parsed_data    *pd;
    t_pos        *map;
    t_bpos        *side_dist;
    t_bpos        delta_dist;
    t_pos        step;
    int        *side;
}    t_dda_data;

typedef struct s_perp_data
{
    t_pos    map;
    t_bpos    pos;
    t_pos    step;
    t_bdir    ray_dir;
    int    side;
}    t_perp_data;

typedef struct s_line_data
{
    int    height;
    int    draw_start;
    int    draw_end;
}    t_line_data;

typedef struct s_column_data
{
    t_parsed_data    *pd;
    int        x;
    int        h;
    double        perp_dist;
    t_bdir           ray_dir;      // add this
    t_bpos           player_pos;
    t_bpos           pos;
    int        side;
    t_pos        map;
}    t_column_data;

typedef struct s_ray_data
{
    t_bdir    ray_dir;
    t_bpos    player_pos;
    t_pos    map;
    t_bpos    delta_dist;
    t_pos    step;
    t_bpos    side_dist;
    int    side;
}    t_ray_data;

typedef struct s_texture_data
{
	mlx_texture_t	*texture;
	double		perp_dist;
	int		side;
	t_bdir		ray_dir;
	t_bpos		pos;
	int		tex_x;
	int		tex_y;
	double		step;
	double		tex_pos;
}	t_texture_data;

typedef struct s_draw_bounds
{
	int draw_start_y;
    int draw_end_y;
    int draw_start_x;
    int draw_end_x;
    int orig_draw_start_x;
    int orig_draw_start_y;
}   t_draw_bounds;

typedef struct s_draw_context
{
    t_parsed_data        *pd;
    t_enemy_draw_data    *curr;
    t_draw_bounds        *b;
}   t_draw_context;

/* Texture sample result returned by value so we avoid out-args */
typedef struct s_tex_sample
{
	uint32_t color;
    unsigned char alpha;
    int ok;
}   t_tex_sample;


/* small helper result to avoid many out-args */
typedef struct s_enemy_calc
{
	t_bpos rel_pos;
	t_bpos transform;
	double distance;
}   t_enemy_calc;

typedef struct s_enemy_ctx
{
	t_parsed_data   *pd;
	t_enemy         *enemy;
	int             index;
	double          distance;
	bool            visible;
}   t_enemy_ctx;

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

typedef struct
{
    t_med_kit *medkit;
    double distance;
    t_bpos transform;
    int sprite_screen_x;
    int sprite_height;
    int sprite_width;
    
    int v_offset_pixels;
    int draw_start_x;
    int draw_end_x;
    int draw_start_y;
    int draw_end_y;

    int stripe;
    int y;

    int tex_x;
    int tex_y;
    t_tex_sample tmp_sample;
} t_medkit_draw_data;

void draw_medkits(t_parsed_data *pd);
void spawn_medkit(t_parsed_data *pd, t_bpos pos, t_enemy_type type);
void check_medkit_pickup(t_parsed_data *pd);
void draw_medkits(t_parsed_data *pd);

void    get_enemies(t_cube *cube);
void    draw_enemies(t_parsed_data *pd);

// helpers test
void    print_argv(char **argv);

/* From enemy_line_of_sight.c */
bool	has_line_of_sight(t_parsed_data *pd, t_bpos start, t_bpos end);

/* From enemy_visibility.c */
int		collect_and_sort_enemies_small(t_parsed_data *pd, t_enemy_draw_data *draw_data);

/* From enemy_drawing.c */
void	draw_single_enemy(t_parsed_data *pd, t_enemy_draw_data *curr, int horizon);
t_tex_sample	sample_texture_pixel(mlx_image_t *img, int tx, int ty);

/* From enemy_combat.c */
void	handle_shooting_once(t_parsed_data *pd, t_enemy_draw_data *draw_data, int draw_count);
void	update_all_death_animations(t_parsed_data *pd);
// void	update_death_animation(t_enemy *enemy);
void update_death_animation(t_parsed_data *pd, t_enemy *enemy);

/* From enemy_movement.c */
void	change_enemy_direction(t_enemy *enemy);
void	calculate_direction_to_player(t_enemy *enemy, t_bpos player_pos, t_bpos *direction);
bool	is_valid_move_position(t_parsed_data *pd, int map_x, int map_y);

/* From enemy_ai.c */
void	set_alternative_directions(t_bpos alternatives[8], t_bpos direction);
bool	return_to_patrol(t_enemy *enemy, t_parsed_data *pd);

/* From enemy_pathfinding.c */
void	smart_chase_player(t_enemy *enemy, t_bpos player_pos, double speed, t_parsed_data *pd);
double	calculate_distance_to_player(t_enemy *enemy, t_parsed_data *pd);
void	perform_patrol_movement(t_enemy *enemy, t_parsed_data *pd);
void	handle_patrol_state(t_enemy_ctx *ctx);

/* From enemy_states.c */
void	handle_enemy_state(t_enemy_ctx *ctx);
void	update_attack_animation(t_enemy *enemy);

/* From enemy_animation.c */
void	update_walk_animation(t_enemy *enemy);


//--------------------------------------------------------------------------------------



/* wall_drawing.h */
void		draw_wall(t_parsed_data *pd, int x, t_line_data *line, uint32_t wall_col);
mlx_texture_t	*get_wall_texture(t_parsed_data *pd, int side, t_bdir ray_dir);
uint32_t	darken_color(uint32_t c);
void		draw_ceiling(t_parsed_data *pd, int x, int draw_start, int horizon);
void		draw_floor(t_parsed_data *pd, int x, int draw_end, int horizon);

/* texture_rendering.h */
void		init_texture_column(t_texture_column *tc);
void		setup_texture_stepping(t_texture_column *tc);
uint32_t	get_pixel_color(t_texture_column *tc, int tex_y);
void		draw_texture_pixels(t_texture_column *tc);
void		draw_textured_column(t_parsed_data *pd, t_column_data *col, t_line_data *line);

/* door_rendering.h */
mlx_texture_t	*get_door_texture(t_parsed_data *pd);
void		init_door_column(t_door_column *dc);
void		setup_door_stepping(t_door_column *dc);
uint32_t	get_door_pixel_color(t_door_column *dc, int tex_y);
void		draw_door_pixels(t_door_column *dc);
void		draw_door_column(t_parsed_data *pd, t_column_data *col, t_line_data *line);

/* dda_calculations.h */
void		compute_delta_dist(t_bdir ray_dir, t_bpos *delta_dist);
void		set_x_step(t_bpos pos, t_pos map, t_bdir ray_dir, t_step_data *data);
void		set_y_step(t_bpos pos, t_pos map, t_bdir ray_dir, t_step_data *data);
void		init_step_and_sidedist(t_bpos player, t_step_data *data);
void		update_x_side(t_dda_data *data);
void		update_y_side(t_dda_data *data);

/* ray_utils.h */
bool		is_wall_hit(t_parsed_data *pd, t_pos map);
void		perform_dda(t_parsed_data *pd, t_dda_data *data);
double		calc_x_perp_dist(t_pos map, t_bpos pos, t_pos step, t_bdir ray_dir);
double		calc_y_perp_dist(t_pos map, t_bpos pos, t_pos step, t_bdir ray_dir);
double		compute_perp_wall_dist(t_perp_data *data);

/* line_calculations.h */
void		calc_line_params(int h, double perp_dist, t_line_data *line, t_parsed_data *pd);
void		draw_column(t_parsed_data *pd, t_column_data *col);

/* ray_casting.h */
void		set_ray_dir(t_ray_dir_data *data);
void		init_ray_data(t_ray_data *ray, t_player *pl, int x, int w);
void		init_dda_data(t_parsed_data *pd, t_ray_data *ray, t_dda_data *dda_data);
void		init_perp_and_col_data(t_parsed_data *pd, int x, t_ray_data *ray, t_perp_data *perp_data, t_column_data *col_data);
void		cast_single_ray(t_parsed_data *pd, int x);
void		raycast_render(t_parsed_data *pd);

/* External from enemies */
void		draw_enemies(t_parsed_data *pd);
// ----------------------------------------------------------------------------------------

// Raycast Light engine
uint32_t    shade_color(uint32_t base_col, double dist, double magnitude);
void    update_enemies(t_parsed_data *pd);


# define CEILING 0xB5AB6BFF
# define FLOOR 0x876D46FF
# define WALL_SIDE 0xCC9D44FF
# define WALL 0xA37D36FF
# define FLOOR_FALLOF 0.0065
# define ROOF_FALLOF 0.0042
# define WALLS_FALLOF 0.35
# define SHIFT_FLOOR_SHADE 100

//--------------------------------------------------------------------------//


// enemy  health macros
# define SKIN_WALKER_HEALTH 42
# define MEMORY_LEAK_HEALTH 70
# define SEGV_HEALTH 101

// enemy damage macros
# define SKIN_WALKER_DAMAGE 15
# define MEMORY_LEAK_DAMAGE 20
# define SEGV_DAMAGE 37

// enemy patrol macros 
# define SKIN_WALKER_PATROL_SPEED 0.1
# define MEMORY_LEAK_PATROL_SPEED 0.2
# define SEGV_PATROL_SPEED 0.25

// enemy chase macros
# define SKIN_WALKER_CHASE_SPEED 0.2
# define MEMORY_LEAK_CHASE_SPEED 0.3
# define SEGV_CHASE_SPEED 0.35


///////////////////////////////////////////////////////////////////////////

#endif
