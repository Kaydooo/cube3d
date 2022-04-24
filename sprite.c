#include "cub3d.h"

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

void	raycast_sprite(t_data *data, int i, int *pos)
{
	int		sprite_mid[2];
	double	mid_slope[2];
	double	mid_dist;
	double	ray_slope[2];
	int		dist;
	double	angle;
	int		index;

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
	if (dist > 16)
		return ;
	index = data->player.rays[i].obj_num++;
	data->player.rays[i].obj_direction[index] = obj_status(data, pos[X], pos[Y], 2);
	if (dist == 0)
		data->player.rays[i].obj_hit_point[index] = 16;
	else if (gradient_diff(ray_slope, mid_slope) < 0)
		data->player.rays[i].obj_hit_point[index] = abs(dist - 16);
	else	
		data->player.rays[i].obj_hit_point[index] = abs(dist + 16);;
	data->player.rays[i].obj_mag[index] = data->player.rays[i].mag;
	data->player.rays[i].obj_x[index] = data->player.rays[i].ray_x;
	data->player.rays[i].obj_y[index] = data->player.rays[i].ray_y;
	int new_size = sizeof(int) * (index + 2);
	data->player.rays[i].obj_direction = realloc(data->player.rays[i].obj_direction, new_size);
	data->player.rays[i].obj_hit_point = realloc(data->player.rays[i].obj_hit_point, new_size);
	data->player.rays[i].obj_mag = realloc(data->player.rays[i].obj_mag, new_size);
	data->player.rays[i].obj_x = realloc(data->player.rays[i].obj_x, new_size);
	data->player.rays[i].obj_y = realloc(data->player.rays[i].obj_y, new_size);

}