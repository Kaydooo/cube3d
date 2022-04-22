#include "cub3d.h"

int		close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCESS);
}

// void	free_and_exit(t_data *data)
// {
// 	if(data)
	
// }