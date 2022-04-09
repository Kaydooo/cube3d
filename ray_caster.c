#include "cub3d.h"

void ray_se(t_data *data, double dx, double dy)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
	double  p1;
	double	p2;
	data->player.rays[i].mag = 0.1;
	rotate(data, 0, i);

	while(1)
	{
		dx = data->player.linex - data->player.x;
		dy = data->player.liney - data->player.y;
		next_xpoint =(( (int) data->player.linex / 32) + 1) * 32;
		next_ypoint =(( (int) data->player.liney / 32) + 1 ) * 32;
		factorx = 1 + (next_xpoint - data->player.linex) / dx;
		factory = 1 + (next_ypoint - data->player.liney) / dy;
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

void ray_ne(t_data *data, double dx, double dy)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
	data->player.rays[i].mag = 1;
	
	rotate(data, 0, i);
	while(1)
	{
		dx = data->player.linex - data->player.x;
		dy = data->player.liney - data->player.y;
		next_xpoint =(( (int) data->player.linex / 32) + 1) * 32;
		next_ypoint =(( (int) data->player.liney / 32) - 1) * 32;
		if(next_ypoint < 0)
			break;
		factorx = 1 + (next_xpoint - data->player.linex) / dx;
		factory = 1 + ((next_ypoint - data->player.liney) / dy);
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


void ray_nw(t_data *data, double dx, double dy)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
	data->player.mag = 1;
	rotate(data, 0);
	while(!insdie_wall(data, 3))
	{
		dx = data->player.linex - data->player.x;
		dy = data->player.liney - data->player.y;
		next_xpoint =(( (int) data->player.linex / 32) - 1) * 32;
		next_ypoint =(( (int) data->player.liney / 32) - 1) * 32;
		if(next_ypoint < 0 || next_xpoint < 0)
			break;
		factorx = 1 + ((next_xpoint - data->player.linex)) / dx;
		factory = 1 + ((next_ypoint - data->player.liney)) / dy;
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

void ray_sw(t_data *data, double dx, double dy)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
	data->player.mag = 1;
	rotate(data, 0);
	while(!insdie_wall(data, 4))
	{
		dx = data->player.linex - data->player.x;
		dy = data->player.liney - data->player.y;
		next_xpoint =(( (int) data->player.linex / 32) - 1) * 32;
		next_ypoint =(( (int) data->player.liney / 32) + 1) * 32;
		if(next_xpoint < 0)
			break;
		factorx = 1 + ((next_xpoint - data->player.linex)) / dx;
		factory = 1 + ((next_ypoint - data->player.liney)) / dy;
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