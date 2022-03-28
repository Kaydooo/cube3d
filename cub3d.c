#include <mlx.h>
#include <unistd.h>
#include <stdio.h>

typedef	struct s_player{
	int x;
	int y;

}t_player;
typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int 	width;
	int		hieght;
}				t_image;

typedef	struct s_data{
	void	*mlx;
	void	*win;
	struct s_image img[20];
	struct s_player player;
	int map[24][24];

}t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img[0].addr + (y * data->img[0].line_length + x * (data->img[0].bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void	printMap(t_data *data)
{
	int x = 0;
	int y = 0;
	while(y < 24)
	{
		x = 0;
		while(x < 24)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->img[data->map[y][x]].img, x*32, y*32);
			if(data->map[y][x] == 2)
			{
				data->player.x = x;
				data->player.y = y;
			}
			x++;
		}
		y++;
	}
}

/*
w = 119
a = 97
s = 115
d = 100
*/
int	movePlayer(int key, t_data *data)
{

	if(key == 119)
	{
		data->map[data->player.y][data->player.x] = 0;
		data->player.y -= 1;
		data->map[data->player.y][data->player.x] = 2;
		printMap(data);
	}
	else if(key == 97)
	{
		data->map[data->player.y][data->player.x] = 0;
		data->player.x -= 1;
		data->map[data->player.y][data->player.x] = 2;
		printMap(data);
	}
	else if (key == 115)
	{
		data->map[data->player.y][data->player.x] = 0;
		data->player.y += 1;
		data->map[data->player.y][data->player.x] = 2;
		printMap(data);
	}
	else if (key == 100)
	{
		data->map[data->player.y][data->player.x] = 0;
		data->player.x += 1;
		data->map[data->player.y][data->player.x] = 2;
		printMap(data);
	}
	if (data)
		{}
	printf("%d\n", key);

	return (0);
}
int	main(void)
{
	t_data	data;
	int mapp[24][24]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	int i = 0;
	int j = 0;
	while(i<24)
	{
		j = 0;
		while (j < 24)
		{
			data.map[i][j] = mapp[i][j];
			j++;
		}
		i++;
	}


	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 24 * 32, 24*32, "Cub3d");
	data.img[0].img = mlx_xpm_file_to_image(data.mlx, "assets/black32.xpm", &data.img[0].width, &data.img[0].hieght);
	data.img[1].img = mlx_xpm_file_to_image(data.mlx, "assets/white32.xpm", &data.img[1].width, &data.img[1].hieght);
	data.img[2].img = mlx_xpm_file_to_image(data.mlx, "assets/blue32.xpm", &data.img[2].width, &data.img[2].hieght);


	printMap(&data);
	mlx_hook(data.win, 2, 1L<<0, movePlayer, &data);
	//mlx_hook(data.win,  3, 0, movePlayer, &data);
	mlx_loop(data.mlx);
}