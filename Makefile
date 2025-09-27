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
	game_loop/draw_minimap.c game_loop/player_input.c game_loop/raycast/raycast_rendring.c \
	game_loop/main_menu/main_menu.c game_loop/main_menu/init_menu.c \
	game_loop/main_menu/ui_input.c game_loop/characters_ui/character_menu.c \
	game_loop/characters_ui/init_characters_ui.c game_loop/raycast/raycast_system.c \
	game_loop/raycast/raycast_data.c game_loop/main_menu/menu_cursor/setup_mouse.c \
	game_loop/main_menu/menu_cursor/handle_mouse_input.c \
	game_loop/main_menu/menu_cursor/handle_mouse_click.c game_loop/game_ui/game_ui.c \
	game_loop/raycast/shading.c game_loop/radar_map/render_radar.c \
	game_loop/radar_map/init_radar.c game_loop/radar_map/render_player_icon.c \
	game_loop/game_ui/init_game_ui.c

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