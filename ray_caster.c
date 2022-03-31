#include "cub3d.h"

void ray_se(t_data *data, double dx, double dy)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
		data->player.mag = 1;
	rotate(data, 0);
	while(!insdie_wall(data, 2))
	{
		dx = data->player.linex - data->player.x;
		dy = data->player.liney - data->player.y;
		next_xpoint =(( (int) data->player.linex / 32) + 1) * 32;
		next_ypoint =(( (int) data->player.liney / 32) + 1 ) * 32;
		factorx = 1 + (next_xpoint - data->player.linex) / dx;
		factory = 1 + (next_ypoint - data->player.liney) / dy;
		if(factorx <= factory)
			data->player.mag = data->player.mag * factorx;
		else
			data->player.mag = data->player.mag * factory;
		rotate(data, 0);
	}
}

void ray_ne(t_data *data, double dx, double dy)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
	data->player.mag = 1;
	rotate(data, 0);
	while(!insdie_wall(data, 1))
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
			data->player.mag = data->player.mag * factorx;
		else
			data->player.mag = data->player.mag * factory;
		rotate(data, 0);
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
			data->player.mag = data->player.mag * factorx;
		else
			data->player.mag = data->player.mag * factory;
		rotate(data, 0);
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
			data->player.mag = data->player.mag * factorx;
		else
			data->player.mag = data->player.mag * factory;
		rotate(data, 0);
	}
}