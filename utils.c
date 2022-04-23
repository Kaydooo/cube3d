#include "cub3d.h"

int	color_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	num = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] \
	== '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		sign = -1;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if(i > 5 || num > 255 || sign < 0)
		print_error("Wrong Color!");
	
	return ((int)(num * sign));
}


int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_2d(char ***str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i])
			free((*str)[i++]);
		free(*str);
		*str = NULL;
	}
}
void	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

void	clear_ray_obj(t_data *data, int reinit)
{
	int i = -1;

	while (++i < data->no_rays)
	{
		data->player.rays[i].obj_num = 0;
 		free (data->player.rays[i].obj_direction);
		free (data->player.rays[i].obj_hit_point);
		free (data->player.rays[i].obj_mag);
		free (data->player.rays[i].obj_x);
		free (data->player.rays[i].obj_y);
		if (!reinit)
			continue;		
		data->player.rays[i].obj_direction = calloc(1, sizeof(int));
		data->player.rays[i].obj_hit_point = calloc(1, sizeof(int));
		data->player.rays[i].obj_mag = calloc(1, sizeof(int));
		data->player.rays[i].obj_x = calloc(1, sizeof(int));
		data->player.rays[i].obj_y = calloc(1, sizeof(int));
	}
}