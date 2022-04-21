#include "cub3d.h"

void	init_map(t_data *data)
{
	// closed door (3) | open door (4) | 
	int mapp[24][24]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1},
	{1,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,3,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	

	int i = 0;
	int j = 0;
	while(i < data->map_width)
	{
		j = 0;
		while (j < data->map_height)
		{
			data->map[i][j] = mapp[i][j];
			j++;
		}
		i++;
	}
}

void	init_imgs(t_data *data)
{
	// Consolidation note1: init address through a while loop like below
	// Consolidation note2: create separate functions for img and addr that take in params
	data->img[0].img = mlx_new_image(data->mlx, data->map_width * 32, data->map_height * 32);
	data->img[0].addr = mlx_get_data_addr(data->img[0].img, &data->img[0].bits_per_pixel, &data->img[0].line_length, &data->img[0].endian);
	data->img[1].img = mlx_xpm_file_to_image(data->mlx, "assets/black32.xpm", &data->img[1].width, &data->img[1].hieght);
	data->img[1].addr = mlx_get_data_addr(data->img[1].img, &data->img[1].bits_per_pixel, &data->img[1].line_length, &data->img[1].endian);
	data->img[2].img = mlx_xpm_file_to_image(data->mlx, "assets/white32.xpm", &data->img[2].width, &data->img[2].hieght);
	data->img[2].addr = mlx_get_data_addr(data->img[2].img, &data->img[2].bits_per_pixel, &data->img[2].line_length, &data->img[2].endian);
	data->img[4].img = mlx_xpm_file_to_image(data->mlx, "assets/blbk.xpm", &data->img[4].width, &data->img[4].hieght);
	data->img[4].addr = mlx_get_data_addr(data->img[4].img, &data->img[4].bits_per_pixel, &data->img[4].line_length, &data->img[4].endian);
	data->img[5].img = mlx_xpm_file_to_image(data->mlx, "assets/blackbk768*768.xpm", &data->img[5].width, &data->img[5].hieght);
	data->img[5].addr = mlx_get_data_addr(data->img[5].img, &data->img[5].bits_per_pixel, &data->img[5].line_length, &data->img[5].endian);
	
	data->img[NORTH_TEXT].img = mlx_xpm_file_to_image(data->mlx, "assets/North.xpm", &data->img[NORTH_TEXT].width, &data->img[NORTH_TEXT].hieght);
	data->img[NORTH_TEXT].addr = mlx_get_data_addr(data->img[NORTH_TEXT].img, &data->img[NORTH_TEXT].bits_per_pixel, &data->img[NORTH_TEXT].line_length, &data->img[NORTH_TEXT].endian);
	data->img[SOUTH_TEXT].img = mlx_xpm_file_to_image(data->mlx, "assets/South.xpm", &data->img[SOUTH_TEXT].width, &data->img[SOUTH_TEXT].hieght);
	data->img[SOUTH_TEXT].addr = mlx_get_data_addr(data->img[SOUTH_TEXT].img, &data->img[SOUTH_TEXT].bits_per_pixel, &data->img[SOUTH_TEXT].line_length, &data->img[SOUTH_TEXT].endian);
	data->img[WEST_TEXT].img = mlx_xpm_file_to_image(data->mlx, "assets/West.xpm", &data->img[WEST_TEXT].width, &data->img[WEST_TEXT].hieght);
	data->img[WEST_TEXT].addr = mlx_get_data_addr(data->img[WEST_TEXT].img, &data->img[WEST_TEXT].bits_per_pixel, &data->img[WEST_TEXT].line_length, &data->img[WEST_TEXT].endian);
	data->img[EAST_TEXT].img = mlx_xpm_file_to_image(data->mlx, "assets/East.xpm", &data->img[EAST_TEXT].width, &data->img[EAST_TEXT].hieght);
	data->img[EAST_TEXT].addr = mlx_get_data_addr(data->img[EAST_TEXT].img, &data->img[EAST_TEXT].bits_per_pixel, &data->img[EAST_TEXT].line_length, &data->img[EAST_TEXT].endian);

	data->img[DOOR_CLOS].img = mlx_xpm_file_to_image(data->mlx, "assets/door1.xpm", &data->img[DOOR_CLOS].width, &data->img[DOOR_CLOS].hieght);
	data->img[DOOR_CLOS + 1].img = mlx_xpm_file_to_image(data->mlx, "assets/door2.xpm", &data->img[DOOR_CLOS + 1].width, &data->img[DOOR_CLOS + 1].hieght);
	data->img[DOOR_CLOS + 2].img = mlx_xpm_file_to_image(data->mlx, "assets/door3.xpm", &data->img[DOOR_CLOS + 2].width, &data->img[DOOR_CLOS + 2].hieght);
	data->img[DOOR_OPEN].img = mlx_xpm_file_to_image(data->mlx, "assets/door4.xpm", &data->img[DOOR_OPEN].width, &data->img[DOOR_OPEN].hieght);
	
	data->img[FLAME_FRST].img = mlx_xpm_file_to_image(data->mlx, "assets/flame1.xpm", &data->img[FLAME_FRST].width, &data->img[FLAME_FRST].hieght);
	data->img[FLAME_FRST + 1].img = mlx_xpm_file_to_image(data->mlx, "assets/flame2.xpm", &data->img[FLAME_FRST + 1].width, &data->img[FLAME_FRST + 1].hieght);
	data->img[FLAME_FRST + 2].img = mlx_xpm_file_to_image(data->mlx, "assets/flame3.xpm", &data->img[FLAME_FRST + 2].width, &data->img[FLAME_FRST + 2].hieght);
	data->img[FLAME_FRST + 3].img = mlx_xpm_file_to_image(data->mlx, "assets/flame4.xpm", &data->img[FLAME_FRST + 3].width, &data->img[FLAME_FRST + 3].hieght);
	data->img[FLAME_FRST + 4].img = mlx_xpm_file_to_image(data->mlx, "assets/flame5.xpm", &data->img[FLAME_FRST + 4].width, &data->img[FLAME_FRST + 4].hieght);
	data->img[FLAME_FRST + 5].img = mlx_xpm_file_to_image(data->mlx, "assets/flame6.xpm", &data->img[FLAME_FRST + 5].width, &data->img[FLAME_FRST + 5].hieght);
	data->img[FLAME_FRST + 6].img = mlx_xpm_file_to_image(data->mlx, "assets/flame7.xpm", &data->img[FLAME_FRST + 6].width, &data->img[FLAME_FRST + 6].hieght);
	data->img[FLAME_FRST + 7].img = mlx_xpm_file_to_image(data->mlx, "assets/flame8.xpm", &data->img[FLAME_FRST + 7].width, &data->img[FLAME_FRST + 7].hieght);
	data->img[FLAME_FRST + 8].img = mlx_xpm_file_to_image(data->mlx, "assets/flame9.xpm", &data->img[FLAME_FRST + 8].width, &data->img[FLAME_FRST + 8].hieght);
	data->img[FLAME_FRST + 9].img = mlx_xpm_file_to_image(data->mlx, "assets/flame10.xpm", &data->img[FLAME_FRST + 9].width, &data->img[FLAME_FRST + 9].hieght);
	data->img[FLAME_FRST + 10].img = mlx_xpm_file_to_image(data->mlx, "assets/flame11.xpm", &data->img[FLAME_FRST + 10].width, &data->img[FLAME_FRST + 10].hieght);
	data->img[FLAME_FRST + 11].img = mlx_xpm_file_to_image(data->mlx, "assets/flame12.xpm", &data->img[FLAME_FRST + 11].width, &data->img[FLAME_FRST + 11].hieght);
	data->img[FLAME_FRST + 12].img = mlx_xpm_file_to_image(data->mlx, "assets/flame13.xpm", &data->img[FLAME_FRST + 12].width, &data->img[FLAME_FRST + 12].hieght);
	data->img[FLAME_FRST + 13].img = mlx_xpm_file_to_image(data->mlx, "assets/flame14.xpm", &data->img[FLAME_FRST + 13].width, &data->img[FLAME_FRST + 13].hieght);
	data->img[FLAME_FRST + 14].img = mlx_xpm_file_to_image(data->mlx, "assets/flame15.xpm", &data->img[FLAME_FRST + 14].width, &data->img[FLAME_FRST + 14].hieght);
	data->img[FLAME_FRST + 15].img = mlx_xpm_file_to_image(data->mlx, "assets/flame16.xpm", &data->img[FLAME_FRST + 15].width, &data->img[FLAME_FRST + 15].hieght);
	data->img[FLAME_FRST + 16].img = mlx_xpm_file_to_image(data->mlx, "assets/flame17.xpm", &data->img[FLAME_FRST + 16].width, &data->img[FLAME_FRST + 16].hieght);
	data->img[FLAME_LAST].img = mlx_xpm_file_to_image(data->mlx, "assets/flame18.xpm", &data->img[FLAME_LAST].width, &data->img[FLAME_LAST].hieght);

	int i = DOOR_CLOS - 1;
	while (++i <= FLAME_LAST)	
		data->img[i].addr = mlx_get_data_addr(data->img[i].img,
			&data->img[i].bits_per_pixel, &data->img[i].line_length,
				&data->img[i].endian);
}
void	init_rays(t_data *data)
{
	int	i;

	i = -1;
	double angel = 0.0;
	while(++i < NUMBER_OF_RAYS)
	{
		data->player.rays[i].rot = angel;
		data->player.rays[i].obj_direction = calloc(1, sizeof(int));
		data->player.rays[i].obj_hit_point = calloc(1, sizeof(int));
		data->player.rays[i].obj_mag = calloc(1, sizeof(int));
		data->player.rays[i].obj_x = calloc(1, sizeof(int));
		data->player.rays[i].obj_y = calloc(1, sizeof(int));
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
	data->map_width =24;
	data->map_height =24;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->map_width * BLOCK_SIZE, data->map_height * BLOCK_SIZE, "Cub3d");
	init_map(data);//temp
	init_rays(data);
	init_imgs(data);
	init_vars(data);
}