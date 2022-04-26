#include "cub3d.h"

void	door_status(t_data *data)
{	
	int	door;
	int	x;
	int	y;

	door = -1;
	while (++door < data->player.rays[WIDTH / 2].obj_num)
	{
		if (data->player.rays[WIDTH / 2].obj_direction[door] != DOOR_CLOS
			&& data->player.rays[WIDTH / 2].obj_direction[door] != DOOR_OPEN)
			continue ;
		x = data->player.rays[WIDTH / 2].obj_x[door];
		y = data->player.rays[WIDTH / 2].obj_y[door];
		if (data->player.rays[WIDTH / 2].obj_direction[door] == DOOR_CLOS)
			data->map[y][x] = DOOR_MAP_O + '0';
		else if (data->player.rays[WIDTH / 2].obj_direction[door] == DOOR_OPEN)
			data->map[y][x] = DOOR_MAP_C + '0';
		return ;
	}
}

void	check_movement(t_data *data)
{
	if (data->player.move_fw)
		move(data, 1);
	if (data->player.move_bw)
		move(data, -1);
	if (data->player.strafe_r)
		move(data, 2);
	if (data->player.strafe_l)
		move(data, -2);
	if (data->player.rotate_r)
		rotate(data, 1, 0);
	if (data->player.rotate_l)
		rotate(data, -1, 0);
}

void	mouse_move(t_data *data, int input)
{
	int			x;
	int			y;
	int			mag;
	static int	mouse;

	if (input != -1)
		mouse = input;
	mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
	if (!mouse || x < 1 || x >= WIDTH || y < 1
		|| y >= data->map_height * BLOCK_SIZE)
		return ;
	mag = 4;
	while (--mag > 0)
		if (x > (WIDTH / 2) + ((mag * WIDTH) / 8)
			|| x < (WIDTH / 2) - ((mag * WIDTH) / 8))
			break ;
	if (x < WIDTH / 2)
		mag *= -1;
	if (mag)
		rotate(data, mag, 0);
}

int	render(t_data *data)
{
	static int	count;

	clear_ray_obj(data, 1);
	mouse_move(data, -1);
	check_movement(data);
	printMap(data, count);
	change_door_status(data, count);
	change_flame_status(data, count);
	if (count++ == 1001)
		count = 0;
	return (0);
}
