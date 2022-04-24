#include "cub3d.h"

int		close_window(t_data *data)
{
	free_all(data);
	exit(EXIT_SUCCESS);
}

void	free_text(t_data *data)
{
	if (data->NO_PATH)
		free(data->NO_PATH);
	if (data->SO_PATH)
		free(data->SO_PATH);
	if (data->WE_PATH)
		free(data->WE_PATH);
	if (data->EA_PATH)
		free(data->EA_PATH);
}
void	free_imgs(t_data *data)
{
	int	i;

	i = 0;
	while(i<32)
	{
		if(data->img[i].img)
			mlx_destroy_image(data->mlx, data->img[i].img);
		i++;
	}
}

void	free_all(t_data *data)
{
	obj_status(data, 0, 0, 1);
	if(data)
	{
		if(data->player.rays)
		{
			clear_ray_obj(data, 0);
			free(data->player.rays);
		}
		if(data->win)
			mlx_destroy_window(data->mlx, data->win);
		if(data->map)
			free_2d(&(data->map));
		free_imgs(data);//destory imgs here
		free_text(data);//free texture paths here
		//.......
		if(data->mlx)
			free(data->mlx);
		free(data);
	}
	
}