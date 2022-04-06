#include "cub3d.h"

void	check_movement(t_data *data)
{
	if(data->player.move_fw)
		move(data, 1);
	if(data->player.move_bw)
		move(data, -1);
	if(data->player.strafe_r)
		move(data, 2);
	if(data->player.strafe_l)
		move(data, -2);
	if(data->player.rotate_r)
		rotate(data, 1, 0);
	if(data->player.rotate_l)
		rotate(data, -1, 0);
}
int	render(t_data *data)
{

	check_movement(data);
	printMap(data);
	return (0);
}