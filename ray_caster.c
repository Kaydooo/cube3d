#include "cub3d.h"

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

void ray_se(t_data *data, double dx, double dy, int i)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
<<<<<<< HEAD
	data->player.mag = 1;
	rotate(data, 0);
	while(!insdie_wall(data, 2))
=======
	double  p1;
	double	p2;
	data->player.rays[i].mag = 0.1;
	rotate(data, 0, i);

	while(1)
>>>>>>> Moatasem
	{
		dx = data->player.rays[i].ray_x - data->player.x;
		dy = data->player.rays[i].ray_y - data->player.y;
		p1 = (data->player.rays[i].ray_x + 0.00001) / 32  + 1;
		p2 = (data->player.rays[i].ray_y + 0.00001) / 32  + 1;
		next_xpoint = (int) p1 * 32;
		next_ypoint = (int) p2 * 32;

		if(next_ypoint > data->map_height * 32 || next_xpoint > data->map_width * 32 || next_ypoint < 0 || next_xpoint < 0)
			break ;
		factorx = 1 + ((next_xpoint - data->player.rays[i].ray_x)) / dx;
		factory = 1 + ((next_ypoint - data->player.rays[i].ray_y)) / dy;
		if(factorx <= factory)
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factorx;
			rotate(data, 0, i);
			data->player.rays[i].direction = WEST_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_y) % data->img[WEST_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32), (((int)(data->player.rays[i].ray_y+0.000001) )/ 32)))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			rotate(data, 0, i);
			data->player.rays[i].direction = NORTH_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_x) % data->img[NORTH_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32), (((int)(data->player.rays[i].ray_y+0.000001) )/ 32)))
				break;
		}
	}
}

void ray_ne(t_data *data, double dx, double dy, int i)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
	data->player.rays[i].mag = 1;
	
	rotate(data, 0, i);
	while(1)
	{
		dx = data->player.rays[i].ray_x - data->player.x;
		dy = data->player.rays[i].ray_y - data->player.y;
		next_xpoint =(((int)(data->player.rays[i].ray_x + 0.00001) / 32) + 1) * 32;
		next_ypoint =(((int)(data->player.rays[i].ray_y + 0.00001) / 32) - 1) * 32;
		if(data->player.rays[i].ray_y - (double) next_ypoint > 32)
			next_ypoint += 32;
		if(data->player.rays[i].ray_x - (double) next_xpoint > 32)
			next_xpoint += 32;
		if(next_ypoint > data->map_height * 32 || next_xpoint > data->map_width * 32 || next_ypoint < 0 || next_xpoint < 0)
			break ;
		factorx = 1 + ((next_xpoint - data->player.rays[i].ray_x)) / dx;
		factory = 1 + ((next_ypoint - data->player.rays[i].ray_y)) / dy;
		if(factorx <= factory)
		{
			if(factorx == factory)
				printf("oho\n");
			data->player.rays[i].mag = data->player.rays[i].mag * factorx;
			rotate(data, 0, i);
			data->player.rays[i].direction = WEST_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_y) % data->img[WEST_TEXT].width;
			if(insdie_wall(data, next_xpoint/32, (((int)(data->player.rays[i].ray_y) )/ 32)))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			rotate(data, 0, i);
			data->player.rays[i].direction = SOUTH_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_x) % data->img[SOUTH_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x) / 32), (next_ypoint/32)-1))
				break;
		}
	}
}


void ray_nw(t_data *data, double dx, double dy, int i)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
	data->player.rays[i].mag = 1;
	rotate(data, 0, i);
	//printf("3\n");
	while(1)
	{
		dx = data->player.rays[i].ray_x - data->player.x;
		dy = data->player.rays[i].ray_y - data->player.y;
		next_xpoint =(((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1) * 32;
		next_ypoint =(((int)(data->player.rays[i].ray_y + 0.00001) / 32) - 1) * 32;
		if(data->player.rays[i].ray_y - (double) next_ypoint > 32)
			next_ypoint += 32;
		if(data->player.rays[i].ray_x - (double) next_xpoint > 32)
			next_xpoint += 32;
		if(next_ypoint > data->map_height * 32 || next_xpoint > data->map_width * 32 || next_ypoint < 0 || next_xpoint < 0)
			break ;
		factorx = 1 + ((next_xpoint - data->player.rays[i].ray_x)) / dx;
		factory = 1 + ((next_ypoint - data->player.rays[i].ray_y)) / dy;
		if(factorx <= factory)
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factorx;
			rotate(data, 0, i);
			data->player.rays[i].direction = EAST_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_y) % data->img[EAST_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1, (((int)(data->player.rays[i].ray_y+0.00001) )/ 32)))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			rotate(data, 0, i);
			data->player.rays[i].direction = SOUTH_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_x) % data->img[SOUTH_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32), (((int)(data->player.rays[i].ray_y+0.00001) )/ 32) -1))
				break;

		}
	}
}

void ray_sw(t_data *data, double dx, double dy, int i)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
	//printf("4\n");
	data->player.rays[i].mag = 1;
	rotate(data, 0, i);

	while(1)
	{
		dx = data->player.rays[i].ray_x - data->player.x;
		dy = data->player.rays[i].ray_y - data->player.y;
		next_xpoint =(((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1) * 32;
		next_ypoint =(((int)(data->player.rays[i].ray_y + 0.00001) / 32) + 1) * 32;
		if(data->player.rays[i].ray_y - (double) next_ypoint > 32)
			next_ypoint += 32;
		if(data->player.rays[i].ray_x - (double) next_xpoint > 32)
			next_xpoint += 32;
		if(next_ypoint > data->map_height * 32 || next_xpoint > data->map_width * 32 || next_ypoint < 0 || next_xpoint < 0)
			break ;
		factorx = 1 + ((next_xpoint - data->player.rays[i].ray_x)) / dx;
		factory = 1 + ((next_ypoint - data->player.rays[i].ray_y)) / dy;
		if(factorx <= factory)
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factorx;
			rotate(data, 0, i);
			data->player.rays[i].direction = EAST_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_y) % data->img[EAST_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1, (((int)(data->player.rays[i].ray_y+0.00001) )/ 32)))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			rotate(data, 0, i);
			data->player.rays[i].direction = NORTH_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_x) % data->img[NORTH_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32), (((int)(data->player.rays[i].ray_y+0.00001) )/ 32)))
				break;
		}
	}
}