/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:39:28 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/22 06:51:37 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_data *data, int x, int y, int r)
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
			my_mlx_pixel_put(data, x + x1, y + y1, 0x00FF0000);
			i += 0.1;
		}
		r--;
	}
}
void	draw_rect(t_data *data, int x, int y, int width, int height, int color)
{

	int	i;
	int	j;

	i = 0;
	j = 0;
	while(j < height)
	{
		i = 0;
		while (i<width)//draw bottom line // change a to change width
		{
			my_mlx_pixel_put(data, x+i, y+j,color);
			i++;
		}	
		j++;
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