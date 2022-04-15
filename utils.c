#include "cub3d.h"

void	clear_ray_obj(t_data *data, int reinit)
{
	int i = -1;

	while (++i < NUMBER_OF_RAYS)
	{
		data->player.rays[i].obj_num = 0;
 		free (data->player.rays[i].obj_direction);
		free (data->player.rays[i].obj_hit_point);
		free (data->player.rays[i].obj_mag);
		free (data->player.rays[i].obj_x);
		free (data->player.rays[i].obj_y);
		if (!reinit)
			continue;		
		data->player.rays[i].obj_direction = calloc(1, sizeof(int));
		data->player.rays[i].obj_hit_point = calloc(1, sizeof(int));
		data->player.rays[i].obj_mag = calloc(1, sizeof(int));
		data->player.rays[i].obj_x = calloc(1, sizeof(int));
		data->player.rays[i].obj_y = calloc(1, sizeof(int));
	}
}