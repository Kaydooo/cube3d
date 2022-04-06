#include "cub3d.h"

void	init_map(t_data *data)
{
	int mapp[24][24]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	int i = 0;
	int j = 0;
	while(i<24)
	{
		j = 0;
		while (j < 24)
		{
			data->map[i][j] = mapp[i][j];
			j++;
		}
		i++;
	}
}

void	init_imgs(t_data *data)
{
	data->img[0].img = mlx_new_image(data->mlx, 48*32, 24*32);
	data->img[0].addr = mlx_get_data_addr(data->img[0].img, &data->img[0].bits_per_pixel, &data->img[0].line_length, &data->img[0].endian);
	data->img[1].img = mlx_xpm_file_to_image(data->mlx, "assets/black32.xpm", &data->img[1].width, &data->img[1].hieght);
	data->img[1].addr = mlx_get_data_addr(data->img[1].img, &data->img[1].bits_per_pixel, &data->img[1].line_length, &data->img[1].endian);
	data->img[2].img = mlx_xpm_file_to_image(data->mlx, "assets/white32.xpm", &data->img[2].width, &data->img[2].hieght);
	data->img[2].addr = mlx_get_data_addr(data->img[2].img, &data->img[2].bits_per_pixel, &data->img[2].line_length, &data->img[2].endian);
	data->img[3].img = mlx_xpm_file_to_image(data->mlx, "assets/blue32.xpm", &data->img[3].width, &data->img[3].hieght);
	data->img[3].addr = mlx_get_data_addr(data->img[3].img, &data->img[3].bits_per_pixel, &data->img[3].line_length, &data->img[3].endian);
	data->img[4].img = mlx_xpm_file_to_image(data->mlx, "assets/blbk.xpm", &data->img[4].width, &data->img[4].hieght);
	data->img[4].addr = mlx_get_data_addr(data->img[4].img, &data->img[4].bits_per_pixel, &data->img[4].line_length, &data->img[4].endian);
	data->img[5].img = mlx_xpm_file_to_image(data->mlx, "assets/blackbk768*768.xpm", &data->img[5].width, &data->img[5].hieght);
	data->img[5].addr = mlx_get_data_addr(data->img[5].img, &data->img[5].bits_per_pixel, &data->img[5].line_length, &data->img[5].endian);
}
void	init_rays(t_data *data)
{
	int	i;

	i = -1;
	double angel = -30.0 * 0.0174533;
	while(++i < NUMBER_OF_RAYS)
	{
		data->player.rays[i].rot = angel;
		angel +=OneDegreeRad;
	}
}
void	init_vars(t_data *data)
{
	data->player.rotate_r = 0;
	data->player.rotate_l = 0;
	data->player.move_fw = 0;
	data->player.move_bw = 0;
	data->player.strafe_l = 0;
	data->player.strafe_r = 0;
}
void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 48 * 32, 24 * 32, "Cub3d");
	init_map(data);//temp
	init_rays(data);
	init_imgs(data);
	init_vars(data);
}