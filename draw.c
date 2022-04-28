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
		int playerRay = WIDTH/2;
		double distance;

		if(i <= playerRay)
			distance = data->player.rays[i].obj_mag[obj_index] * cos(data->player.rays[playerRay].rot - data->player.rays[i].rot);
		else
			distance = data->player.rays[i].obj_mag[obj_index] * cos(data->player.rays[i].rot - data->player.rays[playerRay].rot);
		height = (BLOCK_SIZE * HEIGHT)/distance;
		int drawStart = -height/2 + (HEIGHT / 2);
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = (height/2) + (HEIGHT / 2);
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		void	*dst;
		void	*dst2;
		double inc = (float)data->img[data->player.rays[i].obj_direction[obj_index]].hieght/height;
		double texPos = (drawStart - HEIGHT/2 + height / 2) * inc;
		int y1 = drawStart;
		while(y1<drawEnd)
		{
			int texY = (int)texPos & (data->img[data->player.rays[i].obj_direction[obj_index]].hieght - 1);
			texPos += inc;
			dst = data->img[0].addr + (y1 * data->img[0].line_length + x * (data->img[0].bits_per_pixel / 8));
			dst2 = data->img[data->player.rays[i].obj_direction[obj_index]].addr + ((int)texY * data->img[data->player.rays[i].obj_direction[obj_index]].line_length + data->player.rays[i].obj_hit_point[obj_index] * (data->img[data->player.rays[i].obj_direction[obj_index]].bits_per_pixel / 8));
			if (!(get_t(*(int *)dst2) || *(unsigned int*)(dst2) == 0x00000000))
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
	int playerRay = WIDTH/2;
	double distance;
	i = 0;
	x = 0;
	while(i < WIDTH)
	{
		if(i <= playerRay)
			distance = data->player.rays[i].mag * cos(data->player.rays[i].rot - data->player.rays[playerRay].rot);
		else
			distance = data->player.rays[i].mag * cos(data->player.rays[playerRay].rot - data->player.rays[i].rot);
		height = (BLOCK_SIZE * HEIGHT)/distance;
	
		int drawStart = -height/2 + (HEIGHT / 2);
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = (height/2) + (HEIGHT / 2);
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		void	*dst;
		void	*dst2;
		double inc = (float)data->img[data->player.rays[i].direction].hieght/height;
		double texPos = (drawStart - HEIGHT/2 + height / 2) * inc;
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
	draw_rect(data, 0, 0, WIDTH, HEIGHT/2, data->c_color);
	draw_rect(data, 0, HEIGHT/2, WIDTH, HEIGHT/2, data->f_color);
}

void	draw_minimap(t_data *data)
{
	int x;
	int y;
	int start_draw_x;
	int start_draw_y;

	start_draw_x = 0;
	start_draw_y = 0;
	y = 0;
	draw_rect(data, 0, 0, (MM_WIDTH+3) *4,(MM_HEIGHT+3) * 4, MM_BORDER);
	draw_rect(data, 3, 3, (MM_WIDTH+1) *4, (MM_HEIGHT+1) * 4, MM_BACKGROUND);
	while(data->map[y])
	{
		x = 0;
		if(abs(y - (int)data->player.y/BLOCK_SIZE) <= MM_HEIGHT/2)
		{
			if(y - data->player.y/BLOCK_SIZE <= 0)
				start_draw_y = MM_HEIGHT/2 - abs(y - (int)data->player.y/BLOCK_SIZE);
			else 
				start_draw_y = MM_HEIGHT/2 + abs(y - (int)data->player.y/BLOCK_SIZE);
			while(data->map[y][x])
			{
				if(abs(x - (int)data->player.x/BLOCK_SIZE) < MM_WIDTH/2)
				{
					if(x - data->player.x/BLOCK_SIZE < 0)
						start_draw_x = MM_WIDTH/2 - abs(x - (int)data->player.x/BLOCK_SIZE);
					else if(x - data->player.x/BLOCK_SIZE > 0)
						start_draw_x = MM_WIDTH/2 + abs(x - (int)data->player.x/BLOCK_SIZE);
					if(data->map[y][x] == '0')
						draw_rect(data, start_draw_x*4, start_draw_y*4, 4, 4, MM_GROUND);
					if(data->map[y][x] == '1')
						draw_rect(data, start_draw_x*4, start_draw_y*4, 4, 4, MM_WALL);
					if(data->map[y][x] == '3')
						draw_rect(data, start_draw_x*4, start_draw_y*4, 4, 4, MM_DOOR);
					if(data->map[y][x] == '5')
						draw_rect(data, start_draw_x*4, start_draw_y*4, 4, 4, MM_FLAME);
				}
				x++;
			}
		}
		y++;
	}
}

void	printMap(t_data *data)
{

	draw_floor_cel(data);
	check_line(data);
	draw_3d(data);
	draw_minimap(data);
	draw_rect(data,MM_WIDTH*4/2, MM_HEIGHT*4/2, 4, 4, 0x00FFEEFF);//player
	mlx_put_image_to_window(data->mlx, data->win, data->img[0].img,0, 0);
}