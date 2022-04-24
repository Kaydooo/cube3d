/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:44:28 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/23 09:07:26 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "libs/mlx_linux/mlx.h"
#include "libs/libft/libft.h"
#include "libs/gnl/get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define Y 0
#define X 1

/* Game Settings */
#define NUMBER_OF_RAYS 768
#define ROTATION_SPEED 0.04
#define OneDegreeRad 0.0174533/10//0.0174533
#define BLOCK_SIZE 32
#define SPEED 1

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
#define ESC 65307

/* Mac Keys */
// #define KEY_RIGHT 124
// #define KEY_LEFT 123
// #define KEY_W 13
// #define KEY_S 1
// #define KEY_A 0
// #define KEY_D 2
// #define DOORS ?   <-- Define!
// #define ESC 53


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
	int	rotate_r;
	int	rotate_l;
	int	move_fw;
	int	move_bw;
	int	strafe_l;
	int	strafe_r;
	struct s_ray *rays;
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
	struct s_image img[32];
	struct s_player player;
	char	*NO_PATH;
	char	*SO_PATH;
	char	*WE_PATH;
	char	*EA_PATH;
	int 	c_color;
	int 	f_color;
	int		map_width;
	int		map_height;
	int		config_fd;
	int		no_rays;
	double	start_angle;
	//int map[24][24];
	char	**map;

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
void	init_imgs(t_data *data);
void	init_rays(t_data *data);
void	init_vars(t_data *data);

/* move_player.c */
void	rotate(t_data *data, int dir, int i);
void	move(t_data *data, int dir);

/* draw.c */
void	draw_3d(t_data *data);
void	printMap(t_data *data, int count);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	add_asset_to_image(t_data *data, int x, int y, int asset);

/* parser.c */
int		parse_map(t_data *data, int argc, char **argv);
void	check_map_name(t_data *data, int argc, char **argv);
int		handle_color(t_data *data, char **split_line);
int		handle_elements(t_data *data, char **split_line);
void	check_elements(t_data *data);
int		check_if_no_more_map(t_data *data);
void	calc_map_width_height(t_data *data);
void	parse_map_contents(t_data *data);
void	check_chars(t_data *data);
char	*create_spaces(t_data *data, int number);
void	resize_width(t_data *data);
int		contain_walls_or_spaces_only(char	*temp);
void	check_if_closed_by_walls(t_data *data);
void	print_map_array(t_data *data);
void	check_spaces_from_all_dir(t_data *data);
void	check_if_valid_doors(t_data *data);
void	validate_map_contents(t_data *data);

/* objectc.c */
int 	obj_status(t_data *data, int x, int y, int to_do);
void	change_door_status(t_data *data, int count);
void	change_flame_status(t_data *data, int count);

/* sprite.c */
void	raycast_sprite(t_data *data, int i, int *pos);

/* utils.c */
void	clear_ray_obj(t_data *data, int reinit);
void	print_error(t_data *data, char *msg);
void	free_2d(char ***str);
int		ft_strlen_2d(char **str);
int		color_atoi(const char *str);

/* exit.c */
int		close_window(t_data *data);
void	free_all(t_data *data);

#endif