#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	void	*dst;

	dst = data->img[0].addr + (y * data->img[0].line_length + x * (data->img[0].bits_per_pixel / 8));
	*(unsigned int*)dst = color;	
}

static int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

void	draw_obj(t_data *data, int i, int x)
{
	int obj_index = data->player.rays[i].obj_num;
	while (obj_index-- > 0)
	{
		double height;
		int playerRay = data->no_rays/2;
		double distance;

		if(i <= playerRay)
			distance = data->player.rays[i].obj_mag[obj_index] * cos(data->player.rays[playerRay].rot - data->player.rays[i].rot);
		else
			distance = data->player.rays[i].obj_mag[obj_index] * cos(data->player.rays[i].rot - data->player.rays[playerRay].rot);
		height = (BLOCK_SIZE * 768)/distance;
		int drawStart = -height/2 + (768 / 2);
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = (height/2) + (768 / 2);
		if(drawEnd >= 768)
			drawEnd = 768 - 1;
		void	*dst;
		void	*dst2;
		double inc = (float)data->img[data->player.rays[i].obj_direction[obj_index]].hieght/height;
		double texPos = (drawStart - 768/2 + height / 2) * inc;
		int y1 = drawStart;
		while(y1<drawEnd)
		{
			int texY = (int)texPos & (data->img[data->player.rays[i].obj_direction[obj_index]].hieght - 1);
			texPos += inc;
			dst = data->img[0].addr + (y1 * data->img[0].line_length + x * (data->img[0].bits_per_pixel / 8));
			dst2 = data->img[data->player.rays[i].obj_direction[obj_index]].addr + ((int)texY * data->img[data->player.rays[i].obj_direction[obj_index]].line_length + data->player.rays[i].obj_hit_point[obj_index] * (data->img[data->player.rays[i].obj_direction[obj_index]].bits_per_pixel / 8));
		
			if (!get_t(*(int *)dst2))
				*(unsigned int*)(dst) = *(unsigned int*)(dst2);
			y1++;
		}
	}
}

void	draw_3d(t_data *data)
{
	int i;
	double height;
	int x;
	int playerRay = data->no_rays/2;
	double distance;
	i = 0;
	x = 0;
	while(i < data->no_rays)
	{
		if(i <= playerRay)
			distance = data->player.rays[i].mag * cos(data->player.rays[i].rot - data->player.rays[playerRay].rot);
		else
			distance = data->player.rays[i].mag * cos(data->player.rays[playerRay].rot - data->player.rays[i].rot);
		height = (BLOCK_SIZE * BLOCK_SIZE*data->map_height)/distance;
	
		int drawStart = -height/2 + (data->map_height*BLOCK_SIZE / 2);
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = (height/2) + (data->map_height*BLOCK_SIZE / 2);
		if(drawEnd >= data->map_height*BLOCK_SIZE)
			drawEnd = data->map_height*BLOCK_SIZE - 1;
		void	*dst;
		void	*dst2;
		double inc = (float)data->img[data->player.rays[i].direction].hieght/height;
		double texPos = (drawStart - data->map_height*BLOCK_SIZE/2 + height / 2) * inc;
		int y1 = drawStart;
		while(y1<drawEnd)
		{
			int texY = (int)texPos & (data->img[data->player.rays[i].direction].hieght - 1);
			texPos += inc;
			dst = data->img[0].addr + (y1 * data->img[0].line_length + x * (data->img[0].bits_per_pixel / 8));
			dst2 = data->img[data->player.rays[i].direction].addr + ((int)texY * data->img[data->player.rays[i].direction].line_length + data->player.rays[i].hit_point * (data->img[data->player.rays[i].direction].bits_per_pixel / 8));
			*(unsigned int*)(dst) = *(unsigned int*)(dst2);
			y1++;
		}
		if (data->player.rays[i].obj_direction[0])
			draw_obj(data, i, x);
		x += 1;
		i++;
	}
}

void	draw_floor_cel(t_data *data)
{
	draw_rect(data, 0, 0, data->map_width*BLOCK_SIZE, data->map_height*BLOCK_SIZE/2, data->c_color);
	draw_rect(data, 0, data->map_height*BLOCK_SIZE/2, data->map_width*BLOCK_SIZE, data->map_height*BLOCK_SIZE/2, data->f_color);
}

void	printMap(t_data *data, int count)
{
	int x;
	int y;

	if (count)
		{}
	x = 0;
	y = 0;
	draw_floor_cel(data);
	check_line(data);
	draw_3d(data);
	while(data->map[y])
	{
		x = 0;
		while(data->map[y][x])
		{
			if(data->map[y][x] == '0')
				draw_rect(data, x*4, y*4, 4, 4, 0xFF000000);
			if(data->map[y][x] == '1')
				draw_rect(data, x*4, y*4, 4, 4, 0xFF154360);
			if(data->map[y][x] == '3')
				draw_rect(data, x*4, y*4, 4, 4, 0xFF9FE2BF);
			if(data->map[y][x] == '5')
				draw_rect(data, x*4, y*4, 4, 4, 0xFF8B0000);
			x++;
		}
		y++;
	}
	draw_rect(data,data->player.x/8, data->player.y/8, 3, 3, 0x00FF00FF);//player
	mlx_put_image_to_window(data->mlx, data->win, data->img[0].img,0, 0);
}