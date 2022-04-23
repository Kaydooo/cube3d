#include "cub3d.h"

/*static int get_length(double *pos1, int *pos2)
{	
	return ((int) sqrt(pow(pos1[0] - pos2[0], 2) 
		+ pow(pos1[1] - pos2[1], 2)));
}*/

/*static int gradient_match(double *pos, int *mid, double *gradient)
{
	double pos_grad[2];
	double diff1;
	double diff2;
	double diff;

	pos_grad[Y] = pos[Y] - mid[Y];
	pos_grad[X] = pos[X] - mid[X];
	if (pos_grad[Y] == 0.000 || gradient[Y] == 0.000)
	{
		if (pos_grad[Y] == gradient[Y])
			return (1);
		return (0);
	} 
	if (pos_grad[X] == 0.000 || gradient[X] == 0.000)
	{
		if (pos_grad[X] == gradient[X])
			return (1);
		return (0);
	}
	diff1 = pos_grad[Y] / pos_grad[X];
	diff2 = (gradient[Y] / gradient[X]) * -1;
	if (diff1 < 0)
		diff1 *= -1;
	if (diff2 < 0)
		diff2 *= -1;
	diff = round(diff1 - diff2);
	if (diff <= 0.0001 && diff >= -0.0001)
		return (1);
	return (0);
}

void	sprite_next_point(double *ray_pos, int *nxt_pt, int *dir)
{
	nxt_pt[Y] = (int) (ray_pos[Y] + 1);
	nxt_pt[X] = (int) (ray_pos[X] + 1);
	if (dir[1] == WEST_TEXT && dir[0] == SOUTH_TEXT)
		nxt_pt[Y] = (int) (ray_pos[Y] - 1);
	else if (dir[1] == EAST_TEXT && dir[0] == SOUTH_TEXT)
	{
		nxt_pt[Y] = (int) (ray_pos[Y] - 1);
		nxt_pt[X] = (int) (ray_pos[X] - 1);
	}
	else if (dir[1] == EAST_TEXT && dir[0] == NORTH_TEXT)
		nxt_pt[X] = (int) (ray_pos[X] - 1);
	if (dir[1] == WEST_TEXT && dir[0] == NORTH_TEXT)
		return ;
	if (ray_pos[Y] - (double) (nxt_pt)[Y] > 32)
		(nxt_pt)[Y] += 1;
	if (ray_pos[X] - (double) (nxt_pt)[X] > 32)
		(nxt_pt)[X] += 1;
}

void	raycast_sprite(t_data *data, int i, int *pos, int *dir)
{
	double	ray_pos[2];
	int		ray_next[2];
	double	factor[2];
	int		sprite_mid[2];
	double	sprite_slope[2];
	double	mag;
	int		len;


	// 1. Identify mid point of sprite and perpendicular
	// plane from midpoint to player position
	sprite_mid[Y] = (pos[Y] * 32) + 16;
	sprite_mid[X] = (pos[X] * 32) + 16;
	sprite_slope[Y] = sprite_mid[X] - data->player.x;
	sprite_slope[X] = sprite_mid[Y] - data->player.y;

	mag = data->player.rays[i].mag;
	while (!gradient_match(ray_pos, sprite_mid, sprite_slope)) 
	{
		// 2. Identify next pixel point along the x and y path
		ray_pos[Y] = data->player.rays[i].ray_y;
		ray_pos[X] = data->player.rays[i].ray_x;
		sprite_next_point(ray_pos, ray_next, dir);
		factor[Y] = 1 + ((ray_next[Y] - ray_pos[Y])) 
			/ (ray_pos[Y] - data->player.y);
		factor[X] = 1 + ((ray_next[X] - ray_pos[X]))
			/ (ray_pos[X] - data->player.x);

		// 3. Once side of pixel is found, readjust values
		int j = factor[X] <= factor[Y];
		mag *= factor[j];
		ray_pos[Y] = mag * sin(data->player.rays[i].rot) + data->player.y;
		ray_pos[X] = mag * cos(data->player.rays[i].rot) + data->player.x;
		len = get_length(ray_pos, sprite_mid);
	//	printf("%d\n | ", len);
	//	write(1, "1\n", 2);
		if (len > 23)
			return ;
	}
	if (len > 16)
		return ;
	//printf("len: %d | x: %f | y: %f| midx: %d | midy: %d\n", len, ray_pos[X], ray_pos[Y], sprite_mid[X], sprite_mid[Y]);
	int index = data->player.rays[i].obj_num++;
	data->player.rays[i].obj_direction[index] = obj_status(data, pos[X], pos[Y], 2);
	if (len == 0)
		data->player.rays[i].obj_hit_point[index] = 16;
	else if (ray_pos[Y] * ray_pos[X] < sprite_mid[Y] * sprite_mid[X])
		data->player.rays[i].obj_hit_point[index] = abs(len - 16);
	else
		data->player.rays[i].obj_hit_point[index] = abs(len + 16);
	data->player.rays[i].obj_mag[index] = mag;
	data->player.rays[i].obj_x[index] = ray_pos[X];
	data->player.rays[i].obj_y[index] = ray_pos[Y];
	int new_size = sizeof(int) * (index + 2);
	data->player.rays[i].obj_direction = realloc(data->player.rays[i].obj_direction, new_size);
	data->player.rays[i].obj_hit_point = realloc(data->player.rays[i].obj_hit_point, new_size);
	data->player.rays[i].obj_mag = realloc(data->player.rays[i].obj_mag, new_size);
	data->player.rays[i].obj_x = realloc(data->player.rays[i].obj_x, new_size);
	data->player.rays[i].obj_y = realloc(data->player.rays[i].obj_y, new_size);
}*/

double	gradient_diff(double *grad1, double *grad2)
{
	double gradient1;
	double gradient2;

	if (grad1[X] == 0)
		gradient1 = INT_MAX;
	else
		gradient1 = grad1[Y] / grad1[X];

	if (grad2[X] == 0)
		gradient2 = INT_MAX;
	else
		gradient2 = grad1[Y] / grad1[X];
	
	return (gradient1 - gradient2);
}

void	raycast_sprite(t_data *data, int i, int *pos, int *dir)
{
	int		sprite_mid[2];
	double	mid_slope[2];
	double	mid_dist;
	double	ray_slope[2];
	int		dist;
	double	angle;
	int		index;

	if (dir[0])
		dir[0] = dir[0];
	sprite_mid[Y] = (pos[Y] * 32) + 16;
	sprite_mid[X] = (pos[X] * 32) + 16;
	mid_slope[Y] = sprite_mid[Y] - data->player.y;
	mid_slope[X] = sprite_mid[X] - data->player.x;
	ray_slope[Y] = data->player.rays[i].ray_y - data->player.y;
	ray_slope[X] = data->player.rays[i].ray_x - data->player.x;

	mid_dist = sqrt(pow(mid_slope[Y], 2) + pow(mid_slope[X], 2));
	angle = acos(((mid_slope[Y] * ray_slope[Y]) + (mid_slope[X] * ray_slope[X]))
		/ (sqrt(pow(ray_slope[Y], 2) + pow(ray_slope[X], 2)) * mid_dist));
	dist = (int) round(mid_dist * tan(angle));
//	printf("angle: %f | dist: %f\n", angle, dist);

	if (dist > 16)
		return ;
	index = data->player.rays[i].obj_num++;
	data->player.rays[i].obj_direction[index] = obj_status(data, pos[X], pos[Y], 2);
	if (dist == 0)
		data->player.rays[i].obj_hit_point[index] = 16;
	else if (gradient_diff(ray_slope, mid_slope) < 0)
		data->player.rays[i].obj_hit_point[index] = abs(dist - 16);
	else	
		data->player.rays[i].obj_hit_point[index] = abs(dist + 16);
	data->player.rays[i].obj_mag[index] = data->player.rays[i].mag;
	data->player.rays[i].obj_x[index] = data->player.rays[i].ray_x;
	data->player.rays[i].obj_y[index] = data->player.rays[i].ray_y;
	int new_size = sizeof(int) * (index + 2);
	data->player.rays[i].obj_direction = realloc(data->player.rays[i].obj_direction, new_size);
	data->player.rays[i].obj_hit_point = realloc(data->player.rays[i].obj_hit_point, new_size);
	data->player.rays[i].obj_mag = realloc(data->player.rays[i].obj_mag, new_size);
	data->player.rays[i].obj_x = realloc(data->player.rays[i].obj_x, new_size);
	data->player.rays[i].obj_y = realloc(data->player.rays[i].obj_y, new_size);

/*	
	
	if (len == 0)
		data->player.rays[i].obj_hit_point[index] = 16;
	else if (ray_pos[Y] * ray_pos[X] < sprite_mid[Y] * sprite_mid[X])
		data->player.rays[i].obj_hit_point[index] = abs(len - 16);
	else
		data->player.rays[i].obj_hit_point[index] = abs(len + 16);
	data->player.rays[i].obj_mag[index] = mag;
	data->player.rays[i].obj_x[index] = ray_pos[X];
	data->player.rays[i].obj_y[index] = ray_pos[Y];
	int new_size = sizeof(int) * (index + 2);
	data->player.rays[i].obj_direction = realloc(data->player.rays[i].obj_direction, new_size);
	data->player.rays[i].obj_hit_point = realloc(data->player.rays[i].obj_hit_point, new_size);
	data->player.rays[i].obj_mag = realloc(data->player.rays[i].obj_mag, new_size);
	data->player.rays[i].obj_x = realloc(data->player.rays[i].obj_x, new_size);
	data->player.rays[i].obj_y = realloc(data->player.rays[i].obj_y, new_size);*/
}