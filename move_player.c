#include "cub3d.h"

void	rotate(t_data *data, int dir, int i)
{	
	int	j;

	if (dir == 0)
	{
		data->player.rays[i].ray_x = data->player.rays[i].mag
			* cos(data->player.rays[i].rot) + data->player.x;
		data->player.rays[i].ray_y = data->player.rays[i].mag
			* sin(data->player.rays[i].rot) + data->player.y;
		return ;
	}
	j = -1;
	while (++j < WIDTH)
	{
		data->player.rays[j].rot += (dir * ROTATION_SPEED);
		data->player.rays[j].ray_x = data->player.rays[j].mag
			* cos(data->player.rays[j].rot) + data->player.x;
		data->player.rays[j].ray_y = data->player.rays[j].mag
			* sin(data->player.rays[j].rot) + data->player.y;
	}
}

// NORMINETTED MOVE()
/*static void	set_pos(t_data *data, int dir, double *unit, int max_index)
{
	int	cordinate[2];

	if (abs(dir) == 1)
	{
		cordinate[Y] = max_index & ((int) round(data->player.y
					+ unit[Y] * 15 * SPEED * dir) / BLOCK_SIZE);
		cordinate[X] = max_index & ((int) round(data->player.x
					+ unit[X] * 15 * SPEED * dir) / BLOCK_SIZE);
		if ((data->map[cordinate[Y]][cordinate[X]] - '0') % 2 != 1)
		{
			data->player.x += dir * unit[X] * SPEED;
			data->player.y += dir * unit[Y] * SPEED;
		}
		return ;
	}
	cordinate[Y] = max_index & ((int) round(data->player.y
				- unit[X] * 15 * SPEED * (dir / -2)) / BLOCK_SIZE);
	cordinate[X] = max_index & ((int) round(data->player.x
				- unit[Y] * 15 * SPEED * (dir / 2)) / BLOCK_SIZE);
	if ((data->map[cordinate[Y]][cordinate[X]] - '0') % 2 != 1)
	{
		data->player.x -= (dir / 2) * unit[Y] * SPEED;
		data->player.y -= (dir / -2) * unit[X] * SPEED;
	}
}

void	move(t_data *data, int dir)
{
	double	unit[2];
	int		max_index;

	max_index = data->map_width * BLOCK_SIZE - 1;
	unit[X] = (data->player.rays[WIDTH / 2].ray_x - data->player.x)
		/ (data->player.rays[WIDTH / 2].mag);
	unit[Y] = (data->player.rays[WIDTH / 2].ray_y - data->player.y)
		/ (data->player.rays[WIDTH / 2].mag);
	set_pos(data, dir, unit, max_index);
	if (data->player.x < 0)
		data->player.x = 0;
	if (data->player.x >= (data->map_width) * BLOCK_SIZE)
		data->player.x = (data->map_width - 1) * BLOCK_SIZE;
	if (data->player.y < 0)
		data->player.y = 0;
	if (data->player.y >= (data->map_height) * BLOCK_SIZE)
		data->player.y = (data->map_height - 1) * BLOCK_SIZE;
	init_rays_mag(data);
}*/

void	move(t_data *data, int dir)
{
	double unit_x;
	double unit_y;	
	int max_index;

	max_index = data->map_width * BLOCK_SIZE - 1;	
	unit_x = (data->player.rays[WIDTH/2].ray_x - data->player.x)/(data->player.rays[WIDTH/2].mag);
	unit_y = (data->player.rays[WIDTH/2].ray_y - data->player.y)/(data->player.rays[WIDTH/2].mag);
	if(dir == 1 && (data->map[((int)round(data->player.y + unit_y*15 * SPEED)/BLOCK_SIZE) & max_index][((int)round(data->player.x + unit_x*15 * SPEED)/BLOCK_SIZE ) & max_index] - '0') % 2 != 1)
	{
			data->player.x += unit_x * SPEED;
			data->player.y += unit_y * SPEED;
	}
	else if(dir == -1 && (data->map[((int)round(data->player.y - unit_y*15 * SPEED)/BLOCK_SIZE) & max_index][((int)round(data->player.x - unit_x*15 * SPEED)/BLOCK_SIZE) & max_index] - '0') % 2 != 1)
	{
		data->player.x -= unit_x * SPEED;
		data->player.y -= unit_y * SPEED;
	}
	else if(dir == 2 && (data->map[((int)round(data->player.y - -unit_x*15 * SPEED)/BLOCK_SIZE) & max_index][((int)round(data->player.x - unit_y*15 * SPEED)/BLOCK_SIZE) & max_index] - '0') % 2 != 1)
	{
		data->player.x -= unit_y * SPEED;
		data->player.y -= -unit_x * SPEED;
	}
	else if(dir == -2 && (data->map[((int)round(data->player.y - unit_x*15 * SPEED)/BLOCK_SIZE) & max_index][((int)round(data->player.x - - unit_y*15 * SPEED)/BLOCK_SIZE) & max_index] - '0') % 2 != 1)
	{
		data->player.x -= -unit_y * SPEED;
		data->player.y -= unit_x * SPEED;
	}
	
	if(data->player.x < 0)
		data->player.x = 0;
	if(data->player.x >= (data->map_width) * BLOCK_SIZE)
		data->player.x = (data->map_width-1) * BLOCK_SIZE;
	if(data->player.y < 0)
		data->player.y = 0;
	if(data->player.y >= (data->map_height) * BLOCK_SIZE)
		data->player.y = (data->map_height-1) * BLOCK_SIZE;
	init_rays_mag(data);
}
