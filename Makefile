CC		= cc

CFLAGS	= -Wall -Wextra -Werror

O		= -o

NAME	= cub3d

SOURCE	= cub3d.c	raycast.c	draw.c\

OBJ		= ${SOURCE:%.c=%.o}

%.o: %.c
	$(CC) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all