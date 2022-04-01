/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:39:28 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/01 14:56:23 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(t_data *data, int x, int y, int r)
{
	static const double PI = 3.1415926535;
    double i, angle, x1, y1;
	
	while(r > 0)
	{
		i = 0.0;
		while(i < 360)
		{
			angle = i;
			x1 = r * cos(angle * PI / 180);
			y1 = r * sin(angle * PI / 180);
			my_mlx_pixel_put(data, x + x1, y + y1, 0xFF0000FF);
			i += 0.1;
		}
		r--;
	}
}
void	draw_square(t_data *data)
{
	int a = 32;
	int i = 0;
	while (i<a)
	{
		my_mlx_pixel_put(data,data->player.x+i,data->player.y,0X00FF0000);
		my_mlx_pixel_put(data,data->player.x,data->player.y-i,0X00FF0000);
		i++;
	}
	i = 0;
	while (i<=a)
	{
		my_mlx_pixel_put(data, data->player.x+i,data->player.y-a,0X00FF0000);
		my_mlx_pixel_put(data, data->player.x+a,data->player.y-i,0X00FF0000);
		i++;
	}
}

void	draw_line(t_data *data, double x1, double x2, double y1, double y2)
{
	double dy = y2 - y1;
	double dx = x2 - x1;
	double m = dy/dx;
	double b = y1 - m * x1;
	//printf("m = %f b = %f____%f __ %f __ %f __ %f\n", m, b, x1 ,x2, y1, y2);
	//y = mx + b
	// my_mlx_pixel_put(data, x1, y1, 0X000000FF);
	// my_mlx_pixel_put(data, x2, y2, 0X000000FF);
	if(x1 < x2)
	{
		while(x1 <= x2)
		{
			my_mlx_pixel_put(data, x1,m * x1 + b, 0X0000FF00);
			x1++;
		} 
	}
	else
	{
		while(x1 >= x2)
		{
			my_mlx_pixel_put(data, x1,m * x1 + b, 0X0000FF00);
			x1--;
		} 
	}
}