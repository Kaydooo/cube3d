#include "cub3d.h"

/* Checks the first argument which is supppoesed to be the configuration file path */
void	check_map_name(t_data *data, int argc, char **argv)
{
	if(argc != 2)
		print_error(data, "Wrong number of args!");
	if(ft_strrchr(argv[1], '.'))
	{
		if(ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 5) || ft_strlen(argv[1]) == 4)
			print_error(data, "Wrong Input file!");
	}
	else
		print_error(data, "Wrong Input file!\n");
	data->config_fd = open(argv[1], O_RDWR);
	if(data->config_fd < 0)
		print_error(data, strerror(errno));
}

int		handle_color(t_data *data, char **split_line)
{
	int		color[3];
	char	**color_split;

	if(!strncmp(split_line[0], "F", 2))
	{
		color_split = ft_split(split_line[1], ',');
		color[0] = color_atoi(ft_strtrim(color_split[0], " \n"));
		color[1] = color_atoi(ft_strtrim(color_split[1], " \n"));
		color[2] = color_atoi(ft_strtrim(color_split[2], " \n"));
		if (color[0] == -1 || color[1] == -1 || color[2] == -1 )
		{
			free_2d(&color_split);
			return (1);
		}
		free_2d(&color_split);
		data->f_color = (0xFF << 24 | color[0] << 16 | color[1] << 8 | color[2]);
	}
	else if(!strncmp(split_line[0], "C", 2))
	{
		color_split = ft_split(split_line[1], ',');
		color[0] = color_atoi(ft_strtrim(color_split[0], " \n"));
		color[1] = color_atoi(ft_strtrim(color_split[1], " \n"));
		color[2] = color_atoi(ft_strtrim(color_split[2], " \n"));
		if (color[0] == -1 || color[1] == -1 || color[2] == -1 )
		{
			free_2d(&color_split);
			return (1);
		}
		free_2d(&color_split);
		data->c_color = (0xFF << 24 | color[0] << 16 | color[1] << 8 | color[2]);
	}
	else
		return (1);
	return (0);
}

int	handle_elements(t_data *data, char **split_line)
{ 
	if(ft_strlen_2d(split_line) != 2)
		return (1);
	if(ft_strlen(split_line[0]) == 2)
	{
		if(!strncmp(split_line[0], "NO", 3))
			data->no_path = ft_strdup(split_line[1]);
		else if(!strncmp(split_line[0], "SO", 3))
			data->so_path = ft_strdup(split_line[1]);
		else if(!strncmp(split_line[0], "WE", 3))
			data->we_path = ft_strdup(split_line[1]);
		else if(!strncmp(split_line[0], "EA", 3))
			data->ea_path = ft_strdup(split_line[1]);
		else
			return (1);
	}
	else if(ft_strlen(split_line[0]) == 1)
		return(handle_color(data, split_line));
	else
		return (1);
	return (0);
}

void	check_elements(t_data *data)
{
	char	*line;
	char	**split_line;
	char	*temp;
	int i;

	i = 0;
	data->f_color = 0;
	data->c_color = 0;
	split_line = NULL;
	while(i < 6)
	{
		line = get_next_line(data->config_fd);
		if(!line)
			print_error(data, "Wrong Config File");
		if(line[0] == '\n')
		{
			free(line);
			continue;
		}
		temp = line;
		line = ft_strtrim(line, "\n");
		free(temp);
		split_line = ft_split(line,' ');
		if(handle_elements(data, split_line))
		{
			free_2d(&split_line);
			free(line);
			print_error(data, "Wrong Config File");
		}
		free_2d(&split_line);
		free(line);
		i++;
	}
	if(!data->f_color || !data->c_color || !data->no_path || !data->so_path || !data->we_path || !data->ea_path)
		print_error(data, "Wrong Config File");
}

int	check_if_no_more_map(t_data *data)
{
	char *line;

	while(1)
	{
		line = get_next_line(data->config_fd);
		if(!line)
			return (0);
		if(line[0] == '\n')
		{
			free(line);
			continue;
		}
		else
		{
			free(line);
			return (1);
		}
		free(line);
	}
}

void	calc_map_width_height(t_data *data)
{
	int	i;

	i = 0;
	data->map_width = 0;
	data->map_height= 0;
	data->map_width = ft_strlen(data->map[i]);
	while(data->map[i])
	{
		if((int)ft_strlen(data->map[i]) > data->map_width)
			data->map_width = ft_strlen(data->map[i]);
		i++;
	}
	data->map_height = i;
	data->player.rays = ft_calloc(WIDTH, sizeof(struct s_ray));
	if (!data->player.rays)
		print_error(data, "Malloc Error!");
	//clear_ray_obj(data, 1);
	/* this functions is causing leaks because rays are already
		initialized later on */
}

void	parse_map_contents(t_data *data)
{
	char *line;
	char *map_input;

	while(1)
	{
		line = get_next_line(data->config_fd);
		if(!line)
			print_error(data, "Wrong Config File7");
		if(line[0] == '\n')
		{
			free(line);
			continue;
		}
		else	
		{
			map_input = line;
			break;
		}
		free(line);
	}

	while(1)
	{
		line = get_next_line(data->config_fd);
		if(!line)
			break;
		if(line[0] == '\n')
		{
			free(line);
			if(check_if_no_more_map(data))
			{
				free(map_input);
				print_error(data, "Wrong Config File9");
			}
			break;
		}
		map_input = ft_strjoin(map_input, line);
		free(line);
	}
	data->map = ft_split(map_input, '\n');
	free(map_input);
	calc_map_width_height(data);

}

void	check_chars(t_data *data)
{
	int	i;
	int	j;
	int x;
	char c;

	i = 0;
	x = 0;
	while(data->map[i])
	{
		j = 0;
		while(data->map[i][j])
		{
			c = data->map[i][j];
			if(c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != ' ' && c != '3' && c != '5')
				{
					printf("|%c|\n", c);
					print_error(data, "Map Includes NON-allowed chars232!");
				}
			if(c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				x++;
				if(c == 'N')
					data->start_angle = -1.57080001;
				if(c == 'S')
					data->start_angle = 1.57080001;
				if(c == 'W')
					data->start_angle = 2.0 * 1.57080001;
			}
			j++;
		}
		i++;
	}
	if(x != 1)
		print_error(data, "Map Includes Non or more than 1 starting pos!");
}

char	*create_spaces(t_data *data, int number)
{
	char	*res;
	int		i;

	i = 0;
	if(number > 0)
	{
		res = malloc(sizeof(char) * (number + 1));
		if(!res)
			print_error(data, "Malloc Error!");
	}
	else
		return (NULL);
	while(i < number)
		res[i++] = ' ';
	res[i] = '\0';
	return (res);
		
}

void	resize_width(t_data *data)
{
	int		i;
	int		width;
	char	*spaces;

	i = 0;
	while(data->map[i])
	{
		width = ft_strlen(data->map[i]);
		if(width < data->map_width)
		{
			spaces = create_spaces(data, data->map_width - width);
			data->map[i] = ft_strjoin(data->map[i], spaces);
			free(spaces);
		}
		i++;
	}

}

int		contain_walls_or_spaces_only(char	*temp)
{
	int	j;

	j = 0;
	while(temp[j])
	{
		if(temp[j] != '1' && temp[j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

void	check_if_closed_by_walls(t_data *data)
{
	int		i;
	int		x;
	char	*temp;

	i = 0;
	x = 0;
	while(data->map[i])
	{
		temp = ft_strtrim(data->map[i], " ");
		if(temp[0] != '1' || temp[ft_strlen(temp) - 1] != '1')
				x = 1;
		if(i == 0)
			if(contain_walls_or_spaces_only(temp))
				x = 1;
		if(i == (data->map_height - 1))
			if(contain_walls_or_spaces_only(temp))
				x = 1;
		i++;
		free(temp);
		if (x == 1)
			print_error(data, "Map Not Closed by walls!");
	}
}

void	print_map_array(t_data *data)
{
	int i = 0;
	while(data->map[i])
	{
		ft_putchar_fd('|', 2);
		ft_putstr_fd(data->map[i], 2);
		ft_putchar_fd('|', 2);
		ft_putchar_fd('\n', 2);
		i++;
	}
}

void	check_spaces_from_all_dir(t_data *data)
{
	int		i;
	int		j;
	char	*temp;
	
	i = 0;
	while(data->map[i])
	{
		j = 0;
		temp = data->map[i];
		while(data->map[i][j])
		{
			if(temp[j] == ' ')
			{
				if(i + 1 < data->map_height)
					if(data->map[i + 1][j] != ' ' && data->map[i + 1][j] != '1')
						print_error(data, "Map Not Closed by walls4!");
				if(i - 1 >= 0)
					if(data->map[i - 1][j] != ' ' && data->map[i - 1][j] != '1')
						print_error(data, "Map Not Closed by walls5!");
				if(j + 1 < data->map_width)
					if(data->map[i][j + 1] != ' ' && data->map[i][j + 1] != '1')
						print_error(data, "Map Not Closed by walls6!");
				if(j - 1 >= 0)
					if(data->map[i][j - 1] != ' ' && data->map[i][j - 1] != '1')
						print_error(data, "Map Not Closed by walls7!");
			}
			j++;
		}
		i++;
	}
}

void	check_if_valid_doors(t_data *data)
{
	int		i;
	int		j;
	char	*temp;
	int		x;
	
	i = 0;
	while(data->map[i])
	{
		j = 0;
		temp = data->map[i];
		while(data->map[i][j])
		{
			x = 0;
			if(temp[j] == '3')
			{
				if(i + 1 < data->map_height && i - 1 >= 0)
					if(data->map[i + 1][j] == '1' && data->map[i - 1][j] == '1')
						x++;
				if(j + 1 < data->map_width && j - 1 >= 0)
					if(data->map[i][j + 1] == '1' && data->map[i][j - 1] == '1')		
						x++;
				if(x == 0)
					print_error(data, "Wrong Door Postion!");
			}
			j++;
		}
		i++;
	}
}

void	validate_map_contents(t_data *data)
{
	check_chars(data);
	resize_width(data);
	check_if_closed_by_walls(data);
	check_spaces_from_all_dir(data);
	check_if_valid_doors(data);
}

int	parse_map(t_data *data, int argc, char **argv)
{
	check_map_name(data, argc, argv);
	check_elements(data);
	parse_map_contents(data);
	validate_map_contents(data);
	return (0);
}