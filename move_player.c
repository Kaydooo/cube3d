#include "cub3d.h"

void	rotate(t_data *data, int dir, int i)
{	
	int j;

	j = -1;
	if(dir == 1 || dir == -1)
	{
		while(++j < NUMBER_OF_RAYS)
		{
			data->player.rays[j].rot += (dir * ROTATION_SPEED);
			data->player.rays[j].ray_x = data->player.rays[j].mag * cos(data->player.rays[j].rot) + data->player.x;
			data->player.rays[j].ray_y = data->player.rays[j].mag * sin(data->player.rays[j].rot) + data->player.y;
		}
	}
	else
	{
		data->player.rays[i].ray_x = data->player.rays[i].mag * cos(data->player.rays[i].rot) + data->player.x;
		data->player.rays[i].ray_y = data->player.rays[i].mag * sin(data->player.rays[i].rot) + data->player.y;
	}
}

void	move(t_data *data, int dir)
{
	double unit_x;
	double unit_y;	
	unit_x = (data->player.rays[NUMBER_OF_RAYS/2].ray_x - data->player.x)/(data->player.rays[NUMBER_OF_RAYS/2].mag);
	unit_y = (data->player.rays[NUMBER_OF_RAYS/2].ray_y - data->player.y)/(data->player.rays[NUMBER_OF_RAYS/2].mag);
	if(dir == 1 && data->map[((int)round(data->player.y + unit_y*4.5 * SPEED)/32) & 31][((int)round(data->player.x + unit_x*4.5 * SPEED)/32) & 31] == 0)
	{
			data->player.x += unit_x * SPEED;
			data->player.y += unit_y * SPEED;
	}
	else if(dir == -1 && data->map[((int)round(data->player.y - unit_y*4.5 * SPEED)/32) & 31][((int)round(data->player.x - unit_x*4.5 * SPEED)/32) & 31] == 0)
	{
		data->player.x -= unit_x * SPEED;
		data->player.y -= unit_y * SPEED;
	}
	else if(dir == 2 && data->map[((int)round(data->player.y - -unit_x*4.5 * SPEED)/32) & 31][((int)round(data->player.x - unit_y*4.5 * SPEED)/32) & 31] == 0)
	{
		data->player.x -= unit_y * SPEED;
		data->player.y -= -unit_x * SPEED;
	}
	else if(dir == -2 && data->map[((int)round(data->player.y - unit_x*4.5 * SPEED)/32) & 31][((int)round(data->player.x - -unit_y*4.5 * SPEED)/32) & 31] == 0)
	{
		data->player.x -= -unit_y * SPEED;
		data->player.y -= unit_x * SPEED;
	}
	if(data->player.x < 0)
		data->player.x = 0;
	if(data->player.x > data->map_width * BLOCK_SIZE)
		data->player.x = data->map_width * BLOCK_SIZE;
	if(data->player.y < 0)
		data->player.y = 0;
	if(data->player.y > data->map_height * BLOCK_SIZE)
		data->player.y = data->map_height * BLOCK_SIZE;
	init_rays_mag(data);
}