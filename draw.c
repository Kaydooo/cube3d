#include "cub3d.h"

void	pixel_put(t_img *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_image(t_img *image, t_player *player, double dist, double *pos)
{	
	// calculates position (x) along Field of View 
	double fov_pos = sqrt(pow(pos[0] - player->c_pos[0] + player->c_dir[0], 2) 
		+ pow(pos[1] - player->c_pos[1] + player->c_dir[1], 2));
	
	//printf("x_incr: %f ", x_increment);
	// establish length and width of line to be drawn
	int height = round(dist * 2.5) == 0 ? HEIGHT : (1 / (dist * 2.5)) * HEIGHT;
	int width = (WIDTH * CAM) / (CAM_MAG * 2); // the total length of Field of View is 1
	if (height > HEIGHT)
		height = HEIGHT;

	// establish starting points to draw
	int y = (HEIGHT / 2) - (height / 2);
	int x = (fov_pos * WIDTH) / (CAM_MAG * 2);
	
	while (height >= 0)
	{
		while (width >= 0)
		{
			if (height == 0 || width == 0 || height == y || width == x)
				pixel_put(image, x + width, y + height, 0x00FFFFFF);
			else
				pixel_put(image, x + width, y + height, 0x000000FF);
			width--;
		}
		width = (WIDTH * CAM) / (CAM_MAG * 2);
		height--;
	}
}