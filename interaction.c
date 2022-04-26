#include "cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		close_window(data);
	if (key == KEY_W)
		data->player.move_fw = 1;
	else if (key == KEY_A)
		data->player.strafe_l = 1;
	else if (key == KEY_S)
		data->player.move_bw = 1;
	else if (key == KEY_D)
		data->player.strafe_r = 1;
	else if (key == KEY_RIGHT)
		data->player.rotate_r = 1;
	else if (key == KEY_LEFT)
		data->player.rotate_l = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == KEY_W)
		data->player.move_fw = 0;
	else if (key == KEY_A)
		data->player.strafe_l = 0;
	else if (key == KEY_S)
		data->player.move_bw = 0;
	else if (key == KEY_D)
		data->player.strafe_r = 0;
	else if (key == KEY_RIGHT)
		data->player.rotate_r = 0;
	else if (key == KEY_LEFT)
		data->player.rotate_l = 0;
	else if (key == DOORS)
		door_status(data);
	return (0);
}

int	mouse_enter(t_data *data)
{
	mouse_move(data, 1);
	return (0);
}

int	mouse_leave(t_data *data)
{
	mouse_move(data, 0);
	return (0);
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
