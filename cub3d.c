/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:39:32 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/23 12:10:14 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*static int get_length(double *pos1, double *pos2)
{
	return ((int) round(sqrt(pow(pos1[0] - pos2[0], 2)
		+ pow(pos1[1] - pos2[1], 2))));
}

static int gradient_match(double *pos, double *mid, double *gradient)
{
	double pos_grad[2];
	double diff;

	pos_grad[0] = pos[0] - mid[0];
	pos_grad[1] = pos[1] - mid[1];
	if ((pos_grad[0] == 0.000 || gradient[0] == 0.000) 
		&& pos_grad[0] == gradient[0])
		return (1);
	if ((pos_grad[1] == 0.000 || gradient[1] == 0.000) 
		&& pos_grad[1] == gradient[1])
		return (1);
	if ((pos_grad[0] == 0.000 || gradient[0] == 0.000) 
		&& pos_grad[0] != gradient[0])
		return (0);
	if ((pos_grad[1] == 0.000 || gradient[1] == 0.000) 
		&& pos_grad[1] != gradient[1])
		return (0);
	diff = (pos_grad[0] / pos_grad[1]) - (gradient[0] / gradient[1]);
	if (diff <= 0.00001 && diff >= -0.00001)
		return (1);
	return (0);
}

static void	calc_sprite_val(t_data *data, int i, int x, int y)
{
	double	ray_temp[2];
	double 	ray_slope[2];
	double	ray_shift[2];
	double 	mid[2];
	double	sprite_slope[2];

	mid[0] = (y * 32) + 16;
	mid[1] = (x * 32) + 16;
	sprite_slope[0] = mid[1] - data->player.x;
	sprite_slope[1] = mid[0] - data->player.y;

	ray_temp[0] = data->player.rays[i].ray_y;
	ray_temp[1] = data->player.rays[i].ray_x;
	
	ray_slope[0] = ray_temp[0] - data->player.y;
	ray_slope[1] = ray_temp[0] - data->player.x;
	// problem may lie in how shift is calc. Try raycaster
	ray_shift[0] = 0;
	if (ray_slope[0] != 0)
		ray_shift[0] = 1 / sqrt(1 + pow(ray_slope[1] / ray_slope[0], 2));
	if (ray_slope[0] < 0)
		ray_shift[0] *= -1;
	ray_shift[1] = 0;
	if (ray_slope[1] != 0)
		ray_shift[1] = 1 / sqrt(1 + pow(ray_slope[0] / ray_slope[1], 2));
	if (ray_slope[1] < 0)
		ray_shift[1] *= -1;
	while (!gradient_match(ray_temp, mid, sprite_slope))
	{
		ray_temp[0] += ray_shift[0];
		ray_temp[1] += ray_shift[1];
		if (get_length(ray_temp, mid) > 23)
			return ;
	}
	int len = get_length(ray_temp, mid);
	if (len > 16)
		return ;
	int index = data->player.rays[i].obj_num++;
	data->player.rays[i].obj_direction[index] = obj_status(data, x, y, 2);
	if (len == 0)
		data->player.rays[i].obj_hit_point[index] = 16;
	else if (ray_temp[0] * ray_temp[1] < mid[0] * mid[1])
		data->player.rays[i].obj_hit_point[index] = abs(len - 16);
	else
		data->player.rays[i].obj_hit_point[index] = abs(len + 16);
	double cur_pos[2]; cur_pos[0] = data->player.y; cur_pos[1] = data->player.x;
	data->player.rays[i].obj_mag[index] = get_length(ray_temp, cur_pos);
	data->player.rays[i].obj_x[index] = x;
	data->player.rays[i].obj_y[index] = y;
	int new_size = sizeof(int) * (index + 2);
	data->player.rays[i].obj_direction = realloc(data->player.rays[i].obj_direction, new_size);
	data->player.rays[i].obj_hit_point = realloc(data->player.rays[i].obj_hit_point, new_size);
	data->player.rays[i].obj_mag = realloc(data->player.rays[i].obj_mag, new_size);
	data->player.rays[i].obj_x = realloc(data->player.rays[i].obj_x, new_size);
	data->player.rays[i].obj_y = realloc(data->player.rays[i].obj_y, new_size);
}*/

int		insdie_wall(t_data *data, int x, int y, int i) 
{
	int index;
	int new_size;

	if(y >= data->map_height)
		y = data->map_height - 1;
	if( y < 0)
		y = 0;
	if(x >= data->map_width)
		x = data->map_width - 1;
	if( x < 0)
		x = 0;
	if (data->map[y][x] - '0' >= DOOR_MAP_C)
	{
		index = data->player.rays[i].obj_num++;
		data->player.rays[i].obj_direction[index] = obj_status(data, x, y, 2);
		data->player.rays[i].obj_hit_point[index] = data->player.rays[i].hit_point;
		data->player.rays[i].obj_mag[index] = data->player.rays[i].mag;
		data->player.rays[i].obj_x[index] = x;
		data->player.rays[i].obj_y[index] = y;
		new_size = sizeof(int) * (index + 2);
		data->player.rays[i].obj_direction = realloc(data->player.rays[i].obj_direction, new_size);
		data->player.rays[i].obj_hit_point = realloc(data->player.rays[i].obj_hit_point, new_size);
		data->player.rays[i].obj_mag = realloc(data->player.rays[i].obj_mag, new_size);
		data->player.rays[i].obj_x = realloc(data->player.rays[i].obj_x, new_size);
		data->player.rays[i].obj_y = realloc(data->player.rays[i].obj_y, new_size);
	}
	if(data->map[y][x] == '1')
		return (1);
	return (0);
}

void	init_rays_mag(t_data *data)
{

	int i = 0;

	while(i < data->no_rays)
	{
		data->player.rays[i].ray_x = data->player.x + 0.1;
		data->player.rays[i].ray_y = data->player.y;
		data->player.rays[i].mag  = sqrt(pow(data->player.rays[i].ray_x - data->player.x, 2) + pow(data->player.rays[i].ray_y - data->player.y, 2));
		rotate(data,0, i);
		i++;
	}
}

int	keyPress(int key, t_data *data)
{
	if (key == ESC)
		close_window(data);
	if(key == KEY_W)//w
		data->player.move_fw = 1; 
	else if(key == KEY_A)
		data->player.strafe_l= 1;
	else if (key == KEY_S)
		data->player.move_bw = 1; 
	else if (key == KEY_D)
		data->player.strafe_r = 1;
	else if (key == KEY_RIGHT)
		data->player.rotate_r = 1;
	else if (key == KEY_LEFT)
		data->player.rotate_l = 1;
	return (0);
}

int	keyRelease(int key, t_data *data)
{
	if(key == KEY_W)
		data->player.move_fw = 0; 
	else if(key == KEY_A)
		data->player.strafe_l= 0;
	else if (key == KEY_S)
		data->player.move_bw = 0; 
	else if (key == KEY_D)
		data->player.strafe_r = 0;
	else if (key == KEY_RIGHT)
		data->player.rotate_r = 0;
	else if (key == KEY_LEFT)
		data->player.rotate_l = 0;
	else if (key == DOORS)
		door_status(data);
	return (0);
}

int mouse_enter(t_data *data)
{
	//printf("enter\n");
	mouse_move(data, 1);
	return (0);
}

int mouse_leave(t_data *data)
{
	//printf("leave\n");
	mouse_move(data, 0);
	return (0);
}

void	find_player(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while(data->map[y])
	{
		x = 0;
		while(data->map[y][x])
		{
			if(data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x] == 'W' || data->map[y][x] == 'E')
			{
				data->player.x = x * BLOCK_SIZE;
				data->player.y = y * BLOCK_SIZE;
				init_rays_mag(data);
				data->map[y][x] = '0';
				break;
			}
			x++;
		}
		y++;
	}	
}

int	main(int argc, char **argv)
{
	t_data	*data;
	data = malloc(sizeof(t_data));
	if (!data)
		print_error(data, "Malloc Error!");
	init_vars(data);
	if(parse_map(data, argc, argv))
		return (1);
	data_init(data);
	find_player(data);
	change_door_status(data, 5);
	change_flame_status(data, 2);
	printMap(data, 0);
	mlx_hook(data->win, 2, 1L<<0, keyPress, data);
	mlx_hook(data->win, 3, 0x2, keyRelease, data);
	mlx_hook(data->win, 7, 1L<<4, mouse_enter, data);
	mlx_hook(data->win, 8, 1L<<5, mouse_leave, data);
	mlx_hook(data->win, 17, 0, close_window, data); // close by x
	// mlx_hook(data.win,  3, 0, movePlayer, &data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
}