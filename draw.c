#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	void	*dst;

	dst = data->img[0].addr + (y * data->img[0].line_length + x * (data->img[0].bits_per_pixel / 8));
	*(unsigned int*)dst = color;	
}

void	add_asset_to_image(t_data *data, int x, int y, int asset)
{
	void	*dst;
	void	*dst2;
	int temp;
	int x2;
	int y2;
	
	temp = x;
	x2 = 0;
	y2 = 0;
	while(y2 < 4)
	{
		x2 = 0;
		x = temp;
		while(x2 < 4)
		{
			dst = data->img[0].addr + (y * data->img[0].line_length + x * (data->img[0].bits_per_pixel / 8));
			dst2 = data->img[asset].addr + (y2 * data->img[asset].line_length + x2 * (data->img[asset].bits_per_pixel / 8));
			*(unsigned int*)(dst) = *(unsigned int*)(dst2);
			x2++;
			x++;
		}
		y2++;
		y++;
	}
}
void	add_asset_to_image2(t_data *data, int x, int y, int asset)
{
	void	*dst;
	void	*dst2;
	int temp;
	int x2;
	int y2;
	
	temp = x;
	x2 = 0;
	y2 = 0;
	while(y2 < data->img[asset].width - 1)
	{
		x2 = 0;
		x = temp;
		while(x2 < data->img[asset].hieght - 1)
		{
			dst = data->img[0].addr + (y * data->img[0].line_length + x * (data->img[0].bits_per_pixel / 8));
			dst2 = data->img[asset].addr + (y2 * data->img[asset].line_length + x2 * (data->img[asset].bits_per_pixel / 8));
			*(unsigned int*)(dst) = *(unsigned int*)(dst2);
			x2++;
			x++;
		}
		y2++;
		y++;
	}
}

void	draw_3d(t_data *data)
{
	int i;
	double height;
	int x;
	int y;
	int playerRay = NUMBER_OF_RAYS/2;
	double distance;
	i = 0;
	x = 0; //24* 32;
	while(i < NUMBER_OF_RAYS)
	{
		if(i <= playerRay)
			distance = data->player.rays[i].mag * cos(data->player.rays[playerRay].rot - data->player.rays[i].rot);
		else
			distance = data->player.rays[i].mag * cos(data->player.rays[i].rot - data->player.rays[playerRay].rot);
		height = (BLOCK_SIZE * 768)/distance;
	
		int drawStart = -height/2 + (768 / 2);
		if(drawStart < 0) drawStart = 0;
		int drawEnd = (height/2) + (768 / 2);
		if(drawEnd >= 768) drawEnd = 768 - 1;
	  
			void	*dst;
			void	*dst2;
			double inc = (float)data->img[data->player.rays[i].direction].hieght/height;
			y = y - height;
			double texPos = (drawStart - 768/2 + height / 2) * inc;
			for(int yy = drawStart; yy<drawEnd; yy++)
			{
				int texY = (int)texPos & (data->img[data->player.rays[i].direction].hieght - 1);
        		texPos += inc;
				dst = data->img[0].addr + (yy * data->img[0].line_length + x * (data->img[0].bits_per_pixel / 8));
				dst2 = data->img[data->player.rays[i].direction].addr + ((int)texY * data->img[data->player.rays[i].direction].line_length + data->player.rays[i].hit_point * (data->img[data->player.rays[i].direction].bits_per_pixel / 8));
				*(unsigned int*)(dst) = *(unsigned int*)(dst2);
			}
		x += 1;
		i++;
	}
}

void	printMap(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	//add_asset_to_image(data, x*4, y*4, 4);
	add_asset_to_image2(data, 0, 0, 5);
	while(y < 24)
	{
		x = 0;
		while(x < 24)
		{
			if(data->map[y][x] == 2)
			{
				data->player.x = x * 32;
				data->player.y = y * 32;
				init_rays_mag(data);
				data->map[y][x] = 0;
			}
			if(data->map[y][x] != 2)
				add_asset_to_image(data, x*4, y*4, data->map[y][x] + 1);
			x++;
		}
		y++;
	}
	draw_player(data, data->player.x/8, data->player.y/8, 3);
	check_line(data);
	draw_3d(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img[0].img,0, 0);
}