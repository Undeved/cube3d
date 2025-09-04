CC= cc
FLAGS= -Wall -Werror -Wextra

INCLUDES= -Iinclude
LIBS= MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

HEADER= cube.h

SRC= main.c input_arguments/printers.c input_arguments/evaluate_input.c

OBJ=$(SRC:.c=.o)

NAME= cub3D

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBS) $(INCLUDES) -o $@

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJ)

re: fclean all

.PHONY: clean