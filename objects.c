#include "cub3d.h"

int obj_status(t_data *data, int x, int y, int to_do)
{
	// codes for to_do
	// 1: free obj_map | 2: ignore insert | rest: insert data
	static int	**obj_map;
	int			i;

	if (!obj_map)
	{
		obj_map = calloc(data->map_height, sizeof(int *));
		i = 0;
		while (i < data->map_height)
			obj_map[i++] = calloc(data->map_width, sizeof(int));
	}
	if (to_do == 1)
	{
		i = -1;
		while (++i < data->map_height)
			if(obj_map[i])
				free(obj_map[i]);
		if(obj_map)
			free(obj_map);
		return (0);
	}
	if (to_do > 2)
		obj_map[y][x] = to_do;
	return (obj_map[y][x]);
}

void	change_door_status(t_data *data, int count)
{
	int y;
	int x;
	int	status;

	if (count % 5 != 0)
		return ;
	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			status = obj_status(data, x, y, 2);
			if (data->map[y][x] - '0' == DOOR_MAP_C && !status)
				obj_status(data, x, y, DOOR_CLOS);
			else if (data->map[y][x] - '0' == DOOR_MAP_C && status != DOOR_CLOS)
				obj_status(data, x, y, status - 1);
			else if (data->map[y][x] - '0' == DOOR_MAP_O && !status)
				obj_status(data, x, y, DOOR_OPEN);
			else if (data->map[y][x] - '0' == DOOR_MAP_O && status != DOOR_OPEN)
				obj_status(data, x, y, status + 1);
		}
	}
}

void	change_flame_status(t_data *data, int count)
{
	int y;
	int x;
	int	status;

	if (count % 2 != 0)
		return ;
	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			status = obj_status(data, x, y, 2);
			if (data->map[y][x] - '0' == FLAME_MAP_F && !status)
				obj_status(data, x, y, FLAME_FRST);
			else if (data->map[y][x] - '0' == FLAME_MAP_F && status < FLAME_LAST)
				obj_status(data, x, y, status + 1);				
			else if (data->map[y][x] - '0' == FLAME_MAP_F && status == FLAME_LAST)
				obj_status(data, x, y, FLAME_FRST);
		}
	}
}