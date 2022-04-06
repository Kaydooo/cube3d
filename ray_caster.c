#include "cub3d.h"

void ray_se(t_data *data, double dx, double dy, int i)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
	double  p1;
	double	p2;
	data->player.rays[i].mag = 0.1;
	rotate(data, 0, i);
	//printf("1\n");

	while(1)
	{
		dx = data->player.rays[i].ray_x - data->player.x;
		dy = data->player.rays[i].ray_y - data->player.y;
		p1 = (data->player.rays[i].ray_x + 0.00001) / 32  + 1;
		p2 = (data->player.rays[i].ray_y + 0.00001) / 32  + 1;
		next_xpoint = (int) p1 * 32;
		next_ypoint = (int) p2 * 32;

		if(next_ypoint > 24*32 || next_xpoint > 24*32 || next_ypoint < 0 || next_xpoint < 0)
			break ;
		factorx = 1 + ((next_xpoint - data->player.rays[i].ray_x)) / dx;
		factory = 1 + ((next_ypoint - data->player.rays[i].ray_y)) / dy;
		if(factorx <= factory)
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factorx;
			data->player.rays[i].color = 0x00FF0000;
			rotate(data, 0, i);
		//	draw_circle(data, data->player.rays[i].ray_x, data->player.rays[i].ray_y, 1);
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32), (((int)(data->player.rays[i].ray_y+0.000001) )/ 32)))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			data->player.rays[i].color = 0x00FFFF00;
			rotate(data, 0, i);
		//	draw_circle(data, data->player.rays[i].ray_x, data->player.rays[i].ray_y, 1);
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
	//printf("2\n");
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
		if(next_ypoint > 24*32 || next_xpoint > 24*32 || next_ypoint < 0 || next_xpoint < 0)
			break ;
		factorx = 1 + ((next_xpoint - data->player.rays[i].ray_x)) / dx;
		factory = 1 + ((next_ypoint - data->player.rays[i].ray_y)) / dy;
		if(factorx <= factory)
		{
			if(factorx == factory)
				printf("oho\n");
			data->player.rays[i].mag = data->player.rays[i].mag * factorx;
			data->player.rays[i].color = 0x00FF0000;
			rotate(data, 0, i);
			//draw_circle(data, data->player.rays[i].ray_x, data->player.rays[i].ray_y, 1);
			if(insdie_wall(data, next_xpoint/32, (((int)(data->player.rays[i].ray_y) )/ 32)))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			data->player.rays[i].color = 0x00FFFF00;
			rotate(data, 0, i);
			//draw_circle(data, data->player.rays[i].ray_x, data->player.rays[i].ray_y, 2);
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
		if(next_ypoint > 24*32 || next_xpoint > 24*32 || next_ypoint < 0 || next_xpoint < 0)
			break ;
		factorx = 1 + ((next_xpoint - data->player.rays[i].ray_x)) / dx;
		factory = 1 + ((next_ypoint - data->player.rays[i].ray_y)) / dy;
		if(factorx <= factory)
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factorx;
			data->player.rays[i].color = 0x00FF0000;
			rotate(data, 0, i);
			//draw_circle(data, data->player.rays[i].ray_x, data->player.rays[i].ray_y, 1);
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1, (((int)(data->player.rays[i].ray_y+0.00001) )/ 32)))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			data->player.rays[i].color = 0x00FFFF00;
			rotate(data, 0, i);
			//draw_circle(data, data->player.rays[i].ray_x, data->player.rays[i].ray_y, 1);
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
		if(next_ypoint > 24*32 || next_xpoint > 24*32 || next_ypoint < 0 || next_xpoint < 0)
			break ;
		factorx = 1 + ((next_xpoint - data->player.rays[i].ray_x)) / dx;
		factory = 1 + ((next_ypoint - data->player.rays[i].ray_y)) / dy;
		if(factorx <= factory)
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factorx;
			data->player.rays[i].color = 0x00FF0000;
			rotate(data, 0, i);
			//draw_circle(data, data->player.rays[i].ray_x, data->player.rays[i].ray_y, 1);
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1, (((int)(data->player.rays[i].ray_y+0.00001) )/ 32)))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			data->player.rays[i].color = 0x00FFFF00;
			rotate(data, 0, i);
			//draw_circle(data, data->player.rays[i].ray_x, data->player.rays[i].ray_y, 1);
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32), (((int)(data->player.rays[i].ray_y+0.00001) )/ 32)))
				break;

		}
	}
}