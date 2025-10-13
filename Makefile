CC= cc
SANITIZE= #-fsanitize=address -g3
FLAGS= #-Wall -Werror -Wextra

INCLUDES= -Iinclude -I$(HOME)/local/include
LIBS= MLX42/build/libmlx42.a -L$(HOME)/local/lib -lglfw -ldl -pthread -lm -Ofast -O3

HEADER= cube.h

SRC= helpers.c main.c input_arguments/printers.c input_arguments/evaluate_input.c \
	parse_map/parse_map.c parse_map/parse_utils.c mind_allocater/mind_allocater.c \
	parse_map/gnl/gnl.c parse_map/gnl/gnl_utils.c parse_map/validate_map.c \
	parse_map/validate_map_utils.c parse_map/tab_split.c parse_map/split_tools.c \
	parse_map/floor_roof.c parse_map/floor_roof_utils.c parse_map/validate_grid.c parse_map/closed_bounds.c \
	parse_map/level_data.c parse_map/flood_fill.c game_loop/game_loop.c game_loop/game_render.c \
	game_loop/draw_minimap.c game_loop/player_input.c \
	game_loop/main_menu/main_menu.c game_loop/main_menu/init_menu.c \
	game_loop/main_menu/ui_input.c game_loop/characters_ui/character_menu.c \
	game_loop/characters_ui/init_characters_ui.c \
	raycast/raycast_data.c game_loop/main_menu/menu_cursor/setup_mouse.c \
	game_loop/main_menu/menu_cursor/handle_mouse_input.c \
	game_loop/main_menu/menu_cursor/handle_mouse_click.c game_loop/game_ui/game_ui.c \
	raycast/shading.c game_loop/radar_map/render_radar.c \
	game_loop/radar_map/init_radar.c game_loop/radar_map/render_player_icon.c \
	game_loop/game_ui/init_game_ui.c parse_map/get_enemy_data.c  \
	game_loop/game_ui/ft_itoa.c game_loop/game_ui/setup_character.c \
	game_loop/game_ui/setup_health_ui.c game_loop/door_interaction.c \
	enemy/enemy_states.c enemy/enemy_line_of_sight.c enemy/enemy_pathfinding.c \
	enemy/enemy_ai.c enemy/enemy_animation.c enemy/enemy_visibility.c enemy/enemy_rendering.c \
	enemy/enemy_movement.c enemy/enemy_drawing.c enemy/enemy_combat.c \
	raycast/texture_rendering.c raycast/wall_drawing.c raycast/ray_utils.c\
	raycast/ray_casting.c raycast/line_calculations.c raycast/door_rendering.c\
	raycast/dda_calculations.c parse_map/validate_doors.c raycast/med_kit.c 

OBJ=$(SRC:.c=.o)

NAME= cub3D

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(SANITIZE) $(OBJ) $(LIBS) $(INCLUDES) -o $@

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) $(SANITIZE) -c $< -o $@

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJ)

re: fclean all

.PHONY: clean