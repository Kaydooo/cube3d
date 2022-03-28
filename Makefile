# $< "include one prerequisite"
# $@ "include target"
# $^ "include the full list of prerequisites)"

SRCS = cub3d.c

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

MLX_FLAGS = -Lmlx_linux -lmlx -Imlx_linux -lXext -lX11 -lm -lz

NAME = cub3d

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) $(CFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
	
re:	fclean all

.PHONY:	all clean fclean re