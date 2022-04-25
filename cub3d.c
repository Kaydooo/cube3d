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
	if (data->map[y][x] >= FLAME_MAP_F + '0')
	{
		int pos[2]; pos[Y] = y; pos[X] = x;
		raycast_sprite(data, i, pos);
		return (0);
	}
	else if (data->map[y][x] - '0' >= DOOR_MAP_C)
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
	int i = -1;

	while(++i < WIDTH)
	{
		data->player.rays[i].ray_x = data->player.x + 0.1;
		data->player.rays[i].ray_y = data->player.y;
		data->player.rays[i].mag  = sqrt(pow(data->player.rays[i].ray_x 
			- data->player.x, 2) + pow(data->player.rays[i].ray_y 
				- data->player.y, 2));
		rotate(data,0, i);
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
				break; /* Might be better to use 'return' because 'break' will only exit the second while loop */
			}
			x++;
		}
		y++;
	}	
}

int	main(int argc, char **argv)
{
	t_data	*data;
	data = ft_calloc(1, sizeof(t_data));
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