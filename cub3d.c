/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:39:32 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/06 20:48:18 by mal-guna         ###   ########.fr       */
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

int		insdie_wall(t_data *data, int x, int y) 
{
	//printf("x = %d   y= %d \n",x , y);
	if(data->map[y][x] == 1)
		return 1;
	return 0;
}


void	check_line(t_data *data)
{

	double	dx;
	double	dy;
	int i = 0;
	while(i < NUMBER_OF_RAYS)
	{
		dx = data->player.rays[i].ray_x - data->player.x;
		dy = data->player.rays[i].ray_y - data->player.y;
		
		if(dx > 0 && dy >= 0)// next_point = d * factor + data->player.linex
			ray_se(data, dx, dy, i);
		else if(dx >= 0 && dy < 0)// next_point = d * factor + data->player.linex
			ray_ne(data, dx, dy, i);
		else if(dx < 0 && dy <= 0)// next_point = d * factor + data->player.linex
			ray_nw(data, dx, dy, i);
		else if(dx <= 0 && dy > 0)// next_point = d * factor + data->player.linex
			ray_sw(data, dx, dy, i);
		i++;
	}
	//printf("y = %f   content = %d  \n", data->player.liney/32 , data->map[((int)data->player.liney / 32)][((int)data->player.linex / 32)]);
}
void	init_rays_mag(t_data *data)
{

	int i = 0;

	while(i < NUMBER_OF_RAYS)
	{
		data->player.rays[i].ray_x = data->player.x + 0.1;
		data->player.rays[i].ray_y = data->player.y;
		data->player.rays[i].mag  = sqrt(pow(data->player.rays[i].ray_x - data->player.x, 2) + pow(data->player.rays[i].ray_y - data->player.y, 2));
		rotate(data,0, i);
		i++;
	}
}
void	draw_3d(t_data *data)
{
	int i;
	double height;
	int x;
	int y;
	int playerRay = NUMBER_OF_RAYS/2;
	double distance;
	i = 0;
	x = 24* 32;
	while(i < NUMBER_OF_RAYS)
	{
		if(i <= playerRay)
			distance = data->player.rays[i].mag * cos(data->player.rays[playerRay].rot - data->player.rays[i].rot);
		else
			distance = data->player.rays[i].mag * cos(data->player.rays[i].rot - data->player.rays[playerRay].rot);
		height = (BLOCK_SIZE * 768)/distance;
		if(height > 768)
			height = 768;
		y = 384 + (height/2);
		draw_rect(data, x, y, 2, height, data->player.rays[i].color);
		x += 2;
		i++;
	}
}
void	printMap(t_data *data)
{
	int x = 0;
	int y = 0;
	add_asset_to_image(data, 0, 0, 4);
	add_asset_to_image(data, 32*24, 0, 5);
	while(y < 24)
	{
		x = 0;
		while(x < 24)
		{
			if(data->map[y][x] == 2)
			{
				data->player.x = x * 32;
				data->player.y = y * 32;
				// data->player.linex = data->player.x + 50;
				// data->player.liney = data->player.y;
				init_rays_mag(data);
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
	int i = -1;
	while(++i < NUMBER_OF_RAYS)
		draw_line(data, data->player.x, data->player.rays[i].ray_x, data->player.y, data->player.rays[i].ray_y);
	draw_3d(data);
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

//119 for linux 13 for Mac w
//97 for linux 0 for Mac a
// 115 for linux 1 for Mac s
//100 for linux. 2 for Mac d
//65363 for linux. 124 for Mac r
// 65361 for linux 123 for Mac l
int	keyPress(int key, t_data *data)
{

	if(key == 119)//w
		data->player.move_fw = 1; 
	else if(key == 97)//a
		data->player.strafe_l= 1;
	else if (key == 115)//s
		data->player.move_bw = 1; 
	else if (key == 100)//d
		data->player.strafe_r = 1;
	else if (key == 65363)
		data->player.rotate_r = 1;
	else if (key == 65361)
		data->player.rotate_l = 1;
	//printf("keyp=%d\n", key);
	return (0);
}

int	keyRelease(int key, t_data *data)
{
	if(key == 119)//w
		data->player.move_fw = 0; 
	else if(key == 97)//a
		data->player.strafe_l = 0;
	else if (key == 115)//s
		data->player.move_bw = 0; 
	else if (key == 100)//d
		data->player.strafe_r = 0;
	else if (key == 65363)
		data->player.rotate_r = 0;
	else if (key == 65361)
		data->player.rotate_l = 0;
	//printf("%d\n", key);
	return (0);
}

int	main(void)
{
	t_data	data;
	data_init(&data);
	printMap(&data);

	mlx_hook(data.win, 2, 1L<<0, keyPress, &data);
	mlx_hook(data.win, 3, 0x2, keyRelease, &data);
	// mlx_hook(data.win,  3, 0, movePlayer, &data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
}