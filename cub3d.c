/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:39:32 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/01 16:16:19 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	void	*dst;

	dst = data->img[0].addr + (y * data->img[0].line_length + x * (data->img[0].bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	
}

void	add_asset_to_image(t_data *data, int x, int y, int asset)
{
	void	*dst;
	void	*dst2;
	int temp = x;
	int x2 = 0;
	int y2 = 0;
	
	while(y2 < data->img[asset].hieght - 1)
	{
		x2 = 0;
		x = temp;
		while(x2 < data->img[asset].width - 1)
		{
			dst = data->img[0].addr + (y * data->img[0].line_length + x * (data->img[0].bits_per_pixel / 8));
			dst2 = data->img[asset].addr + (y2 * data->img[asset].line_length + x2 * (data->img[asset].bits_per_pixel / 8));
			*(unsigned int*)(dst) = *(unsigned int*)(dst2);
			x2++;
			x++;
		}
		y2++;
		y++;
	}
}

int		insdie_wall(t_data *data, int dir)
{

	//printf("index y = %050f index x = %f    content = %d\n",data->player.liney / 32 -1, data->player.linex, data->map[((int)data->player.liney / 32) - 1][((int)data->player.linex / 32) ]);
	if(dir == 1) // North East
	{
	//printf("index y = %.50f index x = %.50f  \n",data->player.liney, data->player.linex);	
		if(data->map[(((int)(data->player.liney+0.001) )/ 32) - 1][((int)(data->player.linex + 0.001) / 32)] == 1)
			return 1;
	}
	else if(dir == 2) // Sorth East
	{
		if(data->map[((int)data->player.liney / 32) ][((int)data->player.linex / 32) ] == 1)
			return 1;
	}
	else if(dir == 3) // North West
	{
		if(data->map[((int)data->player.liney / 32) - 1][((int)data->player.linex / 32) - 1] == 1)
			return 1;
	}
	else if(dir == 4) // South West
	{
		if(data->map[((int)data->player.liney / 32) ][((int)data->player.linex / 32)  - 1] == 1)
			return 1;
	}
	else if(dir == 5) // South West
	{
		if(data->map[(((int)(data->player.liney+0.001) )/ 32)][((int)(data->player.linex + 0.001) / 32)] == 1)
			return 1;
	}
	return 0;
}


void	check_line(t_data *data)
{

	double dx = data->player.linex - data->player.x;
	double dy = data->player.liney - data->player.y;
	
	if(dx >= 0 && dy >= 0)// next_point = d * factor + data->player.linex
		ray_se(data, dx, dy);
	else if(dx >= 0 && dy < 0)// next_point = d * factor + data->player.linex
		ray_ne(data, dx, dy);
	else if(dx < 0 && dy <= 0)// next_point = d * factor + data->player.linex
		ray_nw(data, dx, dy);
	else if(dx < 0 && dy >= 0)// next_point = d * factor + data->player.linex
		ray_ne(data, dx, dy);
	//printf("y = %f   content = %d  \n", data->player.liney/32 , data->map[((int)data->player.liney / 32)][((int)data->player.linex / 32)]);
}

void	printMap(t_data *data)
{
	int x = 0;
	int y = 0;
	add_asset_to_image(data, 0, 0, 4);
	while(y < 24)
	{
		x = 0;
		while(x < 24)
		{
			if(data->map[y][x] == 2)
			{
				data->player.x = x * 32;
				data->player.y = y * 32;
				data->player.linex = data->player.x + 50;
				data->player.liney = data->player.y;
				data->player.mag  = sqrt(pow(data->player.linex-data->player.x, 2) + pow(data->player.liney-data->player.y, 2));
				data->map[y][x] = 0;
			}
			if(data->map[y][x] != 2)
				add_asset_to_image(data, x *32, y*32, data->map[y][x] + 1);

			x++;
		}
		y++;
	}
	draw_circle(data, data->player.x, data->player.y, 20);
	check_line(data);
	draw_line(data, data->player.x, data->player.linex, data->player.y, data->player.liney);
	mlx_put_image_to_window(data->mlx, data->win, data->img[0].img,0, 0);
}

/*
w = 119
a = 97
s = 115
d = 100
r =65363
l =65361
d =65364
u =65362
*/
void	rotate(t_data *data, int dir)
{	
	//double PI = 3.14159265359;
	// double x1 = data->player.x + 10;
	// double y1 = data->player.y + 10;
	// double	dist;
	if(dir == 1 || dir == -1)
		data->player.rot += (dir * 0.01);
	// else if ( dir == -1)
	// 	data->player.rot -= (dir * 0.1);
	// double s = sin(data->player.rot);
  	// double c = cos(data->player.rot);
	//data->player.mag = 50;
	// data->player.linex = data->player.mag *cos(data->player.rot) + data->player.x;
	// data->player.liney = data->player.mag *sin(data->player.rot) + data->player.x;
	data->player.linex = data->player.mag * cos(data->player.rot) + data->player.x;
	data->player.liney = data->player.mag * sin(data->player.rot) + data->player.y;
	//printf("mag = %f\n", data->player.mag);
	// data->player.linex = c * (data->player.linex-data->player.x) +  s *(data->player.liney - data->player.y) + data->player.x;
	// data->player.liney = s * (data->player.linex-data->player.x) -  c *(data->player.linex - data->player.y) + data->player.y;
	//my_mlx_pixel_put(data, data->player.linex, data->player.liney, 0x00FF0000);
	//mlx_put_image_to_window(data->mlx, data->win, data->img[0].img, 0, 0);
	// dist = hypot(data->player.linex, data->player.liney);
	// data->player.linex /= dist;
	// data->player.liney /= dist;
	//printf("new x = %f , new y = %f \n", data->player.linex, data->player.liney);

	
	
}
int	movePlayer(int key, t_data *data)
{

	if(key == 119)
	{
		data->player.y -= 5;
		//data->player.liney -= 5;

	}
	else if(key == 97)
	{
		data->player.x -= 5;
		//data->player.linex -=5;
	}
	else if (key == 115)
	{
		data->player.y += 5;
		//data->player.liney +=5;
	}
	else if (key == 100)
	{
		data->player.x += 5;
	//	data->player.linex +=5;
	}
	
	// data->player.linex = data->player.x + 10;
	// data->player.liney = data->player.y + 10;	
	if (key == 65363)
	{	
		rotate(data, 1); // 1 for right
	}
	if (key == 65361)
	{
		rotate(data, -1); // -1 for left
	}

	//if(key == 199 || key ==97 || key == 115 || key ==100  || key == 65363)
	printMap(data);
	printf("key =%d\n",key);
	return (0);
}
int	main(void)
{
	t_data	data;
	int mapp[24][24]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
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
	data.player.rot = 0;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 24 * 32, 24*32, "Cub3d");
	data.img[0].img = mlx_new_image(data.mlx, 24*32, 24*32);
	data.img[0].addr = mlx_get_data_addr(data.img[0].img, &data.img[0].bits_per_pixel, &data.img[0].line_length, &data.img[0].endian);
	data.img[1].img = mlx_xpm_file_to_image(data.mlx, "assets/black32.xpm", &data.img[1].width, &data.img[1].hieght);
	data.img[1].addr = mlx_get_data_addr(data.img[1].img, &data.img[1].bits_per_pixel, &data.img[1].line_length, &data.img[1].endian);
	data.img[2].img = mlx_xpm_file_to_image(data.mlx, "assets/white32.xpm", &data.img[2].width, &data.img[2].hieght);
	data.img[2].addr = mlx_get_data_addr(data.img[2].img, &data.img[2].bits_per_pixel, &data.img[2].line_length, &data.img[2].endian);
	data.img[3].img = mlx_xpm_file_to_image(data.mlx, "assets/blue32.xpm", &data.img[3].width, &data.img[3].hieght);
	data.img[3].addr = mlx_get_data_addr(data.img[3].img, &data.img[3].bits_per_pixel, &data.img[3].line_length, &data.img[3].endian);
	data.img[4].img = mlx_xpm_file_to_image(data.mlx, "assets/greybk.xpm", &data.img[4].width, &data.img[4].hieght);
	data.img[4].addr = mlx_get_data_addr(data.img[4].img, &data.img[4].bits_per_pixel, &data.img[4].line_length, &data.img[4].endian);

	printMap(&data);

	// int a = 33;
	// for(i=0;i<a;i++)
	// {
	// 	my_mlx_pixel_put(&data,data.player.x+i,data.player.y,0X00FF0000);
	// 	my_mlx_pixel_put(&data,data.player.x,data.player.y-i,0X00FF0000);
	// mlx_put_image_to_window(data.mlx, data.win, data.img[0].img,0, 0);

	// }
	// for(i=0;i<=a;i++)
	// {
	// 	my_mlx_pixel_put(&data, data.player.x+i,data.player.y-a,0X00FF0000);
	// 	my_mlx_pixel_put(&data, data.player.x+a,data.player.y-i,0X00FF0000);

	// }
	mlx_hook(data.win, 2, 1L<<0, movePlayer, &data);
	//mlx_hook(data.win,  3, 0, movePlayer, &data);
	mlx_loop(data.mlx);
}