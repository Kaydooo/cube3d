/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:44:28 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/06 14:34:15 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "mlx_mac/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#define NUMBER_OF_RAYS 61
#define ROTATION_SPEED 0.001
#define OneDegreeRad 0.0174533
#define BLOCK_SIZE 32
#define SPEED 1
typedef	struct s_ray
{
	double	ray_x;
	double	ray_y;
	double	mag;
	double	rot;
	int		color;
}t_ray;

typedef	struct s_player{
	double x;
	double y;
	struct s_ray rays[NUMBER_OF_RAYS];
	int	rotate_r;
	int	rotate_l;
	int	move_fw;
	int	move_bw;
	int	strafe_l;
	int	strafe_r;
	// double linex;
	// double liney;
	// double mag;
	// double rot;

}t_player;

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int 	width;
	int		hieght;
}				t_image;

typedef	struct s_data{
	void	*mlx;
	void	*win;
	void	*game_win;
	struct s_image img[20];
	struct s_player player;
	int map[24][24];

}t_data;

/* draw_shapes.c */
void	draw_circle(t_data *data, int x, int y, int r);
void	draw_rect(t_data *data, int x, int y, int width, int height, int color);
void	draw_line(t_data *data, double x1, double x2, double y1, double y2);

/* cub3d.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	add_asset_to_image(t_data *data, int x, int y, int asset);
void	printMap(t_data *data);
int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
int		insdie_wall(t_data *data, int x, int y);
void	init_rays_mag(t_data *data);

/* ray_caster.c */
void ray_se(t_data *data, double dx, double dy, int i);
void ray_ne(t_data *data, double dx, double dy, int i);
void ray_nw(t_data *data, double dx, double dy, int i);
void ray_sw(t_data *data, double dx, double dy, int i);


/* render.c */
int	render(t_data *data);

/* data_init.c */
void	data_init(t_data *data);
void	init_map(t_data *data);
void	init_imgs(t_data *data);
void	init_rays(t_data *data);

/* move_player.c */
void	rotate(t_data *data, int dir, int i);
void	move(t_data *data, int dir);
#endif