/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:39:32 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/09 13:03:33 by mal-guna         ###   ########.fr       */
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
	//printf("index y = %f index x = %f    content = %d\n",data->player.liney / 32 -1, data->player.linex, data->map[((int)data->player.liney / 32) - 1][((int)data->player.linex / 32) ]);
	if(dir == 1) // North East
	{
		if(data->map[((int)data->player.liney / 32) - 1][((int)data->player.linex / 32) ] == 1)
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
	
		int drawStart = -height/2 + (768 / 2);
		if(drawStart < 0) drawStart = 0;
		int drawEnd = (height/2) + (768 / 2);
		if(drawEnd >= 768) drawEnd = 768 - 1;
	  
			void	*dst;
			void	*dst2;
			double inc = (float)data->img[data->player.rays[i].direction].hieght/height;
			y = y - height;
			double texPos = (drawStart - 768/2 + height / 2) * inc;
			for(int yy = drawStart; yy<drawEnd; yy++)
			{
				int texY = (int)texPos & (data->img[data->player.rays[i].direction].hieght - 1);
        		texPos += inc;
				dst = data->img[0].addr + (yy * data->img[0].line_length + x * (data->img[0].bits_per_pixel / 8));
				dst2 = data->img[data->player.rays[i].direction].addr + ((int)texY * data->img[data->player.rays[i].direction].line_length + data->player.rays[i].hit_point * (data->img[data->player.rays[i].direction].bits_per_pixel / 8));
				*(unsigned int*)(dst) = *(unsigned int*)(dst2);
			}
		x += 1;
		i++;
	}
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
				init_rays_mag(data);
				data->map[y][x] = 0;
			}
			if(data->map[y][x] != 2)
				add_asset_to_image(data, x *32, y*32, data->map[y][x] + 1);

			x++;
		}
		y++;
	}
	draw_circle(data, 20);
	check_line(data);
	draw_line(data, data->player.x, data->player.linex, data->player.y, data->player.liney);
	mlx_put_image_to_window(data->mlx, data->win, data->img[0].img,0, 0);
}


int	keyPress(int key, t_data *data)
{
	if(key == KEY_W)//w
		data->player.move_fw = 1; 
	else if(key == KEY_A)//a
		data->player.strafe_l= 1;
	else if (key == KEY_S)//s
		data->player.move_bw = 1; 
	else if (key == KEY_D)//d
		data->player.strafe_r = 1;
	else if (key == KEY_RIGHT)
		data->player.rotate_r = 1;
	else if (key == KEY_LEFT)
		data->player.rotate_l = 1;
	return (0);
}

int	keyRelease(int key, t_data *data)
{
	if(key == KEY_W)//w
		data->player.move_fw = 0; 
	else if(key == KEY_A)//a
		data->player.strafe_l= 0;
	else if (key == KEY_S)//s
		data->player.move_bw = 0; 
	else if (key == KEY_D)//d
		data->player.strafe_r = 0;
	else if (key == KEY_RIGHT)
		data->player.rotate_r = 0;
	else if (key == KEY_LEFT)
		data->player.rotate_l = 0;
	//printf("%d\n", key);
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
	mlx_hook(data.win, 2, 1L<<0, keyPress, &data);
	mlx_hook(data.win, 3, 0x2, keyRelease, &data);
	// mlx_hook(data.win,  3, 0, movePlayer, &data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
}