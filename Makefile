CC= cc
SANITIZE= -fsanitize=address -g3
FLAGS= -Wall -Werror -Wextra

INCLUDES= -Iinclude
LIBS= MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

HEADER= cube.h

SRC= main.c input_arguments/printers.c input_arguments/evaluate_input.c \
	parse_map/parse_map.c parse_map/parse_utils.c mind_allocater/mind_allocater.c

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