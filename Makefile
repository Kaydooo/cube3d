# $< "include one prerequisite"
# $@ "include target"
# $^ "include the full list of prerequisites)"

SRCS = src/cub3d.c src/draw_shapes.c src/ray_caster.c src/data_init.c src/move_player.c src/render.c src/draw.c src/utils.c	src/objects.c src/parser.c \
       src/draw_utils.c src/exit.c src/sprite.c src/interaction.c src/rotate.c src/parser_utils.c src/map_elements.c src/parse_map.c src/map_contents.c src/validate_map.c

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

OS	= $(shell uname)
LIBFT = libs/libft/libft.a
GNL = libs/gnl/gnl.a
LIBFT_PATH = libs/libft
GNL_PATH = libs/gnl

ifeq ($(OS), Linux)
	MLX_FLAGS = -Llibs/mlx_linux -lmlx -Ilibs/mlx_linux -lXext -lX11 -lm -lz
	MLX_PATH = libs/mlx_linux
else
	MLX_FLAGS = -Llibs/mlx_mac -lmlx -Ilibs/mlx_mac -framework OpenGL -framework AppKit
	MLX_PATH = libs/mlx_mac
endif

NAME = cub3D

all : $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_PATH)
	$(MAKE) -C $(LIBFT_PATH)
	$(MAKE) -C $(GNL_PATH)
	$(CC) $(OBJS) $(MLX_FLAGS) $(GNL) $(LIBFT)  $(CFLAGS) -o $(NAME)

clean:
	$(MAKE) clean -C $(MLX_PATH)
	$(MAKE) clean -C $(LIBFT_PATH)
	$(MAKE) clean -C $(GNL_PATH)
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)
	$(MAKE) fclean -C $(GNL_PATH)
re:	fclean all

.PHONY:	all clean fclean re