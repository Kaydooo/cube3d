/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:39:32 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/09 13:00:54 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int		insdie_wall(t_data *data, int x, int y) 
{
	//printf("x = %d   y= %d \n",x , y);
	if(data->map[y][x] == 1)
		return 1;
	return 0;
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

int	keyPress(int key, t_data *data)
{
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