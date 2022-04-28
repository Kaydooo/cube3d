#include "cub3d.h"

void	draw_obj(t_data *data, int i, int obj_index)
{
	double	height;
	int		draw[2];
	double	inc;
	double	tex_pos;

	height = (BLOCK_SIZE * HEIGHT) / get_ray_distance(data, i, obj_index);
	draw[0] = -height / 2 + (HEIGHT / 2);
	if (draw[0] < 0)
		draw[0] = 0;
	draw[1] = (height / 2) + (HEIGHT / 2);
	inc = (float)data->img[data->player.rays[i].obj_direction[obj_index]].hieght
		/ height;
	tex_pos = (draw[0] - HEIGHT / 2 + height / 2) * inc;
	while (draw[0] < draw[1] && draw[0] < HEIGHT)
	{
		my_mlx_pixel_put(data, i, draw[0]++,
			img_color(data, i, (int)tex_pos, obj_index));
		tex_pos += inc;
	}
}

void	draw_3d(t_data *data, int i)
{
	double	height;
	int		draw[3];
	double	inc;
	double	tex_pos;

	height = (BLOCK_SIZE * HEIGHT) / get_ray_distance(data, i, -1);
	draw[0] = -height / 2 + (HEIGHT / 2);
	if (draw[0] < 0)
		draw[0] = 0;
	draw[1] = (height / 2) + (HEIGHT / 2);
	inc = (float)data->img[data->player.rays[i].direction].hieght / height;
	tex_pos = (draw[0] - HEIGHT / 2 + height / 2) * inc;
	while (draw[0] < draw[1] && draw[0] < HEIGHT)
	{
		my_mlx_pixel_put(data, i, draw[0]++,
			img_color(data, i, (int)tex_pos, -1));
		tex_pos += inc;
	}
	draw[2] = data->player.rays[i].obj_num;
	while (draw[2]-- > 0)
		draw_obj(data, i, draw[2]);
}

void	draw_floor_cel(t_data *data)
{
	draw_rect(data, 0, 0, WIDTH, HEIGHT / 2, data->c_color);
	draw_rect(data, 0, HEIGHT / 2, WIDTH, HEIGHT / 2, data->f_color);
}

void	draw_minimap(t_data *data, int i)
{
	int	pos[2];
	int	start_draw[2];

	start_draw[X] = 0;
	start_draw[Y] = 0;
	pos[Y] = i;
	pos[X] = -1;
	if (!(abs(pos[Y] - (int)data->player.y / BLOCK_SIZE) <= MM_HEIGHT / 2))
		return ;
	start_draw[Y] = MM_HEIGHT / 2 + (pos[Y] - (int)data->player.y / BLOCK_SIZE);
	while (data->map[pos[Y]][++pos[X]])
	{
		if (!(abs(pos[X] - (int)data->player.x / BLOCK_SIZE) < MM_WIDTH / 2))
			continue ;
		start_draw[X] = MM_WIDTH / 2 + (pos[X] - (int)data->player.x / BLOCK_SIZE);
		if (data->map[pos[Y]][pos[X]] == '0')
			draw_rect(data, start_draw[X] * 4, start_draw[Y] * 4, 4, 4, MM_GROUND);
		if (data->map[pos[Y]][pos[X]] == '1')
			draw_rect(data, start_draw[X] * 4, start_draw[Y] * 4, 4, 4, MM_WALL);
		if (data->map[pos[Y]][pos[X]] == '3')
			draw_rect(data, start_draw[X] * 4, start_draw[Y] * 4, 4, 4, MM_DOOR);
		if (data->map[pos[Y]][pos[X]] == '5')
			draw_rect(data, start_draw[X] * 4, start_draw[Y] * 4, 4, 4, MM_FLAME);
	}
}

void	printMap(t_data *data)
{
	int	i;

	mlx_clear_window(data->mlx, data->win);
	draw_floor_cel(data);
	check_line(data);
	i = -1;
	while (++i < WIDTH)
		draw_3d(data, i);
	i = -1;
	draw_rect(data, 0, 0, (MM_WIDTH + 3) * 4, (MM_HEIGHT + 3) * 4, MM_BORDER);
	draw_rect(data, 3, 3, (MM_WIDTH + 1) * 4, (MM_HEIGHT + 1) * 4, MM_BKGRND);
	while (data->map[++i])
		draw_minimap(data, i);
	draw_rect(data, MM_WIDTH * 4 / 2, MM_HEIGHT * 4 / 2, 4, 4, 0x00FFEEFF);
	mlx_put_image_to_window(data->mlx, data->win, data->img[0].img, 0, 0);
}
