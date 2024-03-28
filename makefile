CC = cc
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux
NAME = fdf
BONUS = fdf_bonus
SRC_DIR = src/
SRC = fdf_utils.c errors.c frees.c build_stack.c read_file.c stack_to_mtx.c\
		rotations.c draw.c rasterization.c keys.c events.c view_settings.c main.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -O3 -c $< -o $@

all: libft $(NAME)

libft:
	make -C libft


$(NAME): $(OBJ)
	$(CC) -g $(OBJ) -Lminilibx-linux -lmlx_Linux \
	 			-L/usr/lib \
				-Iminilibx-linux \
				-lXext -lX11 -lm -lz \
				-Llibft -lft \
				-o $(NAME)

bonus: libft $(BONUS)

$(BONUS): $(OBJ)
	$(CC) -g $(OBJ) -Lminilibx-linux -lmlx_Linux \
	 			-L/usr/lib \
				-Iminilibx-linux \
				-lXext -lX11 -lm -lz \
				-Llibft -lft \
				-o $(BONUS)

clean:
	rm -f $(OBJ) $(NAME) $(BONUS)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(BONUS)
	make -C libft fclean

re: fclean
	make all

.PHONY: all clean fclean re libft bonus