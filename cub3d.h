/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:44:28 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/09 14:01:12 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "mlx_linux/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

/* Game Settings */
#define NUMBER_OF_RAYS 768
#define ROTATION_SPEED 0.02
#define OneDegreeRad 0.0174533/10//0.0174533
#define BLOCK_SIZE 32
#define SPEED 2

/* Texture Indices */
#define NORTH_TEXT 6
#define SOUTH_TEXT 7
#define WEST_TEXT 8
#define EAST_TEXT 9

/* Door sprite */
#define DOOR_CLOS 10 // img index
#define DOOR_OPEN 13 // img index
#define DOOR_MAP_C 3 // map index
#define DOOR_MAP_O 4 // map index

/* Flame sprite */
#define FLAME_FRST 14 // img index of first sprite
#define FLAME_LAST 31 // img index of last sprite
#define FLAME_MAP_F 5 // map index
#define FLAME_MAP_L 7 // map index

/* Linux Keys */
#define KEY_RIGHT 65363
#define KEY_LEFT 65361
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define DOORS 112

/* Mac Keys */
// #define KEY_RIGHT 124
// #define KEY_LEFT 123
// #define KEY_W 13
// #define KEY_S 1
// #define KEY_A 0
// #define KEY_D 2
// #define DOORS ?   <-- Define!


typedef	struct s_ray
{
	double	ray_x;
	double	ray_y;
	double	mag;
	double	rot;
	int		color;
	int		hit_point;
	int		direction;
	int		obj_num;
	int		*obj_hit_point;
	int		*obj_direction;
	int		*obj_mag;
	int		*obj_x;
	int		*obj_y;
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
	struct s_image img[32];
	struct s_player player;
	int		map_width;
	int		map_height;
	int map[24][24];

}t_data;

/* draw_shapes.c */
void	draw_player(t_data *data, int x, int y, int r);
void	draw_rect(t_data *data, int x, int y, int width, int height, int color);
void	draw_line(t_data *data, double x1, double x2, double y1, double y2);

/* cub3d.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	add_asset_to_image(t_data *data, int x, int y, int asset);
int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
int		insdie_wall(t_data *data, int x, int y, int i);
void	init_rays_mag(t_data *data);

/* ray_caster.c */
void	check_line(t_data *data);
void ray_se(t_data *data, double dx, double dy, int i);
void ray_ne(t_data *data, double dx, double dy, int i);
void ray_nw(t_data *data, double dx, double dy, int i);
void ray_sw(t_data *data, double dx, double dy, int i);


/* render.c */
int		render(t_data *data);
void	door_status(t_data *data);
void 	mouse_move(t_data *data, int input);

/* data_init.c */
void	data_init(t_data *data);
void	init_map(t_data *data);
void	init_imgs(t_data *data);
void	init_rays(t_data *data);

/* move_player.c */
void	rotate(t_data *data, int dir, int i);
void	move(t_data *data, int dir);

/* draw.c */
void	draw_3d(t_data *data);
void	printMap(t_data *data, int count);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	add_asset_to_image(t_data *data, int x, int y, int asset);

/* objectc.c */
int 	obj_status(t_data *data, int x, int y, int to_do);
void	change_door_status(t_data *data, int count);
void	change_flame_status(t_data *data, int count);

/* utils.c */
void	clear_ray_obj(t_data *data, int reinit);

#endif