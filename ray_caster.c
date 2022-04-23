#include "cub3d.h"

static int check_wall(t_data *data, int side, int i, int *dir, int *nxt_pt)
{
	int x;
	int y;

	x = (int)(data->player.rays[i].ray_x + 0.00001) / 32;
	y = (int)(data->player.rays[i].ray_y + 0.00001) / 32;
	if (dir[0] == SOUTH_TEXT && dir[1] == WEST_TEXT)
	{
		x = (int)(data->player.rays[i].ray_x) / 32;
		y = (nxt_pt[0] / 32) - 1;
		if (side)
		{
			x = nxt_pt[1] / 32;
			y = (int)(data->player.rays[i].ray_y) / 32;
		}
	}
	else if (dir[0] == SOUTH_TEXT && dir[1] == EAST_TEXT && !side)
		y -= 1;
	else if (dir[1] == EAST_TEXT && side)
		x -= 1;
	if (data->map[y][x] >= FLAME_MAP_F)
	{
		int pos[2]; pos[Y] = y; pos[X] = x;
		raycast_sprite(data, i, pos, dir);
		return (0);
	}
	return (insdie_wall(data, x, y, i));
}

void	get_next_point(t_data *data, int i, int *nxt_pt, int *dir)
{
	(nxt_pt)[1] = (int)(((data->player.rays[i].ray_x + 0.00001) / 32) + 1) * 32;
	(nxt_pt)[0] = (int)(((data->player.rays[i].ray_y + 0.00001) / 32) + 1) * 32;
	if (dir[1] == WEST_TEXT && dir[0] == SOUTH_TEXT)
		(nxt_pt)[0] = (((int)(data->player.rays[i].ray_y + 0.00001) / 32) - 1) * 32;
	else if (dir[1] == EAST_TEXT && dir[0] == SOUTH_TEXT)
	{
		(nxt_pt)[0] = (((int)(data->player.rays[i].ray_y + 0.00001) / 32) - 1) * 32;
		(nxt_pt)[1] = (((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1) * 32;
	}
	else if (dir[1] == EAST_TEXT && dir[0] == NORTH_TEXT)
		(nxt_pt)[1] = (((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1) * 32;
	if (dir[1] == WEST_TEXT && dir[0] == NORTH_TEXT)
		return ;
	if (data->player.rays[i].ray_y - (double) (nxt_pt)[0] > 32)
		(nxt_pt)[0] += 32;
	if (data->player.rays[i].ray_x - (double) (nxt_pt)[1] > 32)
		(nxt_pt)[1] += 32;
}

void raycast(t_data *data, double *diff, int i, int *dir)
{
	double	factor[2];
	int		nxt_pt[2];
	int		j;

	while (1)
	{
		diff[1] = data->player.rays[i].ray_x - data->player.x;
		diff[0] = data->player.rays[i].ray_y - data->player.y;
		get_next_point(data, i, nxt_pt, dir);
		if (nxt_pt[0] > data->map_height * 32 || nxt_pt[0] < 0 
			|| nxt_pt[1] > data->map_width * 32 || nxt_pt[1] < 0)
				break ;
		factor[1] = 1 + ((nxt_pt[1] - data->player.rays[i].ray_x)) / diff[1];
		factor[0] = 1 + ((nxt_pt[0] - data->player.rays[i].ray_y)) / diff[0]; 
		j = (factor[1] <= factor[0]);
		data->player.rays[i].mag = data->player.rays[i].mag * factor[j];
		rotate(data, 0, i);
		data->player.rays[i].direction = dir[j];
		data->player.rays[i].hit_point = (int)
			round(data->player.rays[i].ray_y) % data->img[dir[j]].width;
		if (j == 0)
			data->player.rays[i].hit_point = (int)
				round(data->player.rays[i].ray_x) % data->img[dir[j]].width;
		if (check_wall(data, j, i, dir, nxt_pt))
			break ;
	}
}

void	check_line(t_data *data)
{
	double	diff[2]; // y:0 x:1
	int		dir[2];  // y: N/S texture | x: W/E texture
	int		i;
	
	i = -1;
	while(++i < NUMBER_OF_RAYS)
	{
		diff[1] = data->player.rays[i].ray_x - data->player.x;
		diff[0] = data->player.rays[i].ray_y - data->player.y;
		data->player.rays[i].mag = 0.1;
		rotate(data, 0, i);
		dir[0] = NORTH_TEXT; // assuming SE
		dir[1] = WEST_TEXT;  // assuming SE
		if(diff[1] >= 0 && diff[0] < 0) 	 // NE
			dir[0] = SOUTH_TEXT;
		else if(diff[1] < 0 && diff[0] <= 0) // NW
		{
			dir[0] = SOUTH_TEXT;
			dir[1] = EAST_TEXT;
		}
		else if(diff[1] <= 0 && diff[0] > 0) // SW
			dir[1] = EAST_TEXT;
		raycast(data, diff, i, dir);
	}
}


/*void	check_line(t_data *data)
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
}
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

	while(1)
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
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32), (((int)(data->player.rays[i].ray_y+0.000001) )/ 32), i, data->player.rays[i].hit_point))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			rotate(data, 0, i);
			data->player.rays[i].direction = NORTH_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_x) % data->img[NORTH_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32), (((int)(data->player.rays[i].ray_y+0.000001) )/ 32), i, data->player.rays[i].hit_point))
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
	data->player.rays[i].mag = 0.1;
	
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
			if(insdie_wall(data, next_xpoint/32, (((int)(data->player.rays[i].ray_y) )/ 32), i, data->player.rays[i].hit_point))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			rotate(data, 0, i);
			data->player.rays[i].direction = SOUTH_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_x) % data->img[SOUTH_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x) / 32), (next_ypoint/32)-1, i, data->player.rays[i].hit_point))
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
	data->player.rays[i].mag = 0.1;
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
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1, (((int)(data->player.rays[i].ray_y+0.00001) )/ 32), i, data->player.rays[i].hit_point))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			rotate(data, 0, i);
			data->player.rays[i].direction = SOUTH_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_x) % data->img[SOUTH_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32), (((int)(data->player.rays[i].ray_y+0.00001) )/ 32) -1, i, data->player.rays[i].hit_point))
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
	data->player.rays[i].mag = 0.1;
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
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1, (((int)(data->player.rays[i].ray_y+0.00001) )/ 32), i, data->player.rays[i].hit_point))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			rotate(data, 0, i);
			data->player.rays[i].direction = NORTH_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_x) % data->img[NORTH_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32), (((int)(data->player.rays[i].ray_y+0.00001) )/ 32), i, data->player.rays[i].hit_point))
				break;
		}
	}
}
*/
