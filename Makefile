# $< "include one prerequisite"
# $@ "include target"
# $^ "include the full list of prerequisites)"

SRCS = cub3d.c draw_shapes.c ray_caster.c data_init.c move_player.c render.c draw.c utils.c	objects.c sprite.c

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

OS	= $(shell uname)
ifeq ($(OS), Linux)
	MLX_FLAGS = -Lmlx_linux -lmlx -Imlx_linux -lXext -lX11 -lm -lz
	MLX_PATH = mlx_linux
else
	MLX_FLAGS = -Lmlx_mac -lmlx -Imlx_mac -framework OpenGL -framework AppKit
	MLX_PATH = mlx_mac
endif


NAME = cub3d

all : $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_PATH)
	$(CC) $(OBJS) $(MLX_FLAGS) $(CFLAGS) -o $(NAME)

clean:
	$(MAKE) clean -C $(MLX_PATH)
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
	
re:	fclean all

.PHONY:	all clean fclean re