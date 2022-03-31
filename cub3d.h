/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:44:28 by mal-guna          #+#    #+#             */
/*   Updated: 2022/03/31 14:35:09 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "mlx_linux/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>

typedef	struct s_player{
	double x;
	double y;
	double linex;
	double liney;
	double mag;
	double rot;

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
	struct s_image img[20];
	struct s_player player;
	int map[24][24];

}t_data;

/* draw_shapes.c */
void	draw_circle(t_data *data, int r);
void	draw_square(t_data *data);
void	draw_line(t_data *data, double x1, double x2, double y1, double y2);

/* cub3d.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	add_asset_to_image(t_data *data, int x, int y, int asset);
void	printMap(t_data *data);
int		movePlayer(int key, t_data *data);
void	rotate(t_data *data, int dir);
int		insdie_wall(t_data *data, int dir);

/* ray_caster.c */
void ray_se(t_data *data, double dx, double dy);
void ray_ne(t_data *data, double dx, double dy);
void ray_nw(t_data *data, double dx, double dy);
void ray_sw(t_data *data, double dx, double dy);

#endif