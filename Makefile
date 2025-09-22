CC= cc
SANITIZE= #-fsanitize=address -g3
FLAGS= -Wall -Werror -Wextra

INCLUDES= -Iinclude -I$(HOME)/local/include
LIBS= MLX42/build/libmlx42.a -L$(HOME)/local/lib -lglfw3 -ldl -pthread -lm

HEADER= cube.h

SRC= simple_raycaster.c game_loop/basic_gl.c helpers.c main.c input_arguments/printers.c input_arguments/evaluate_input.c \
	parse_map/parse_map.c parse_map/parse_utils.c mind_allocater/mind_allocater.c \
	parse_map/gnl/gnl.c parse_map/gnl/gnl_utils.c parse_map/validate_map.c \
	parse_map/validate_map_utils.c parse_map/tab_split.c parse_map/split_tools.c \
	parse_map/floor_roof.c parse_map/floor_roof_utils.c

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