#include "cub3d.h"

/* Checks the first argument which is supppoesed to be the configuration file path */
void	check_map_name(t_data *data, int argc, char **argv)
{
	if(data)
	{}
	if(argc != 2)
		print_error("Wrong number of args!");
	if(ft_strrchr(argv[1], '.'))
	{
		if(ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 5) || ft_strlen(argv[1]) == 4)
			print_error("Wrong Input file!");
	}
	else
		print_error("Wrong Input file!\n");
	data->config_fd = open(argv[1], O_RDWR);
	if(data->config_fd < 0)
		print_error(strerror(errno));
}

void	handle_color(t_data *data, char **split_line)
{
	int		color[3];
	char	**color_split;

	if(!strncmp(split_line[0], "F", 2))
	{
		color_split = ft_split(split_line[1], ',');
		color[0] = color_atoi(ft_strtrim(color_split[0], " \n"));
		color[1] = color_atoi(ft_strtrim(color_split[1], " \n"));
		color[2] = color_atoi(ft_strtrim(color_split[2], " \n"));
		data->f_color = (0xFF << 24 | color[0] << 16 | color[1] << 8 | color[2]);
	}
	else if(!strncmp(split_line[0], "C", 2))
	{
		color_split = ft_split(split_line[1], ',');
		color[0] = color_atoi(ft_strtrim(color_split[0], " \n"));
		color[1] = color_atoi(ft_strtrim(color_split[1], " \n"));
		color[2] = color_atoi(ft_strtrim(color_split[2], " \n"));
		data->c_color = (0xFF << 24 | color[0] << 16 | color[1] << 8 | color[2]);
	}
	else
		print_error("Wrong Config File!3");
}

void	handle_elements(t_data *data, char **split_line)
{ 
	if(ft_strlen_2d(split_line) != 2)
		print_error("Wrong Config File!1");
	if(ft_strlen(split_line[0]) == 2)
	{
		if(!strncmp(split_line[0], "NO", 3))
			data->NO_PATH = split_line[1];
		else if(!strncmp(split_line[0], "SO", 3))
			data->SO_PATH = split_line[1];
		else if(!strncmp(split_line[0], "WE", 3))
			data->WE_PATH = split_line[1];
		else if(!strncmp(split_line[0], "EA", 3))
			data->EA_PATH = split_line[1];
		else
			print_error("Wrong Config File!2");
	}
	else if(ft_strlen(split_line[0]) == 1)
		handle_color(data, split_line);
	else
		print_error("Wrong Config File!4");
}

void	check_elements(t_data *data)
{
	char *line;
	char **split_line;
	int i;

	i = 0;
	data->f_color = 0;
	data->c_color = 0;
	split_line = NULL;
	while(i < 6)
	{
		line = get_next_line(data->config_fd);
		if(!line)
			print_error("Wrong Config File5");
		if(line[0] == '\n')
			continue;
		line = ft_strtrim(line, "\n");
		split_line = ft_split(line,' ');
		handle_elements(data, split_line);
		i++;
	}
	if(!data->f_color || !data->c_color || !data->NO_PATH || !data->SO_PATH || !data->WE_PATH || !data->EA_PATH)
		print_error("Wrong Config File6");
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
			continue;
		else
			return (1);
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
	data->no_rays = BLOCK_SIZE * data->map_width;
	data->player.rays = malloc(sizeof(struct s_ray) * data->no_rays);
	if (!data->player.rays)
		print_error("Malloc Error!");
	printf("%d   %d \n",data->map_height, data->map_width);
}

void	parse_map_contents(t_data *data)
{
	char *line;
	char *map_input;

	map_input = ft_strdup("");
	while(1)
	{
		line = get_next_line(data->config_fd);
		if(!line)
			print_error("Wrong Config File7");
		if(line[0] == '\n')
			continue;
		else
			break;
	}
	map_input = ft_strjoin(map_input, line);
	while(1)
	{
		line = get_next_line(data->config_fd);
		if(!line)
			break;
		if(line[0] == '\n')
		{
			if(check_if_no_more_map(data))
				print_error("Wrong Config File9");
			break;
		}
		map_input = ft_strjoin(map_input, line);
	}
	data->map = ft_split(map_input, '\n');
	calc_map_width_height(data);
	int i = 0;
	while(data->map[i])
	{
		ft_putstr_fd(data->map[i], 2);
		ft_putchar_fd('\n', 2);
		i++;
	}
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
			if(c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != '2' && c != ' ' && c != '3' && c != '5')
				{
					printf("|%c|\n", c);
					print_error("Map Includes Not-allowed chars232!");
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
		print_error("Map Includes Non or more than 1 starting pos!");
}

char	*create_spaces(int number)
{
	char	*res;
	int		i;

	i = 0;
	if(number > 0)
	{
		res = malloc(sizeof(char) * (number + 1));
		if(!res)
			print_error("Malloc Error!");
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
	char	*temp;

	i = 0;
	while(data->map[i])
	{
		width = ft_strlen(data->map[i]);
		if(width < data->map_width)
		{
			temp = data->map[i];
			data->map[i] = ft_strjoin(data->map[i], create_spaces(data->map_width - width));
			free(temp);
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
			print_error("Map Not Closed by walls!");
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
						print_error("Map Not Closed by walls4!");
				if(i - 1 >= 0)
					if(data->map[i - 1][j] != ' ' && data->map[i - 1][j] != '1')
						print_error("Map Not Closed by walls5!");
				if(j + 1 < data->map_width)
					if(data->map[i][j + 1] != ' ' && data->map[i][j + 1] != '1')
						print_error("Map Not Closed by walls6!");
				if(j - 1 >= 0)
					if(data->map[i][j - 1] != ' ' && data->map[i][j - 1] != '1')
						print_error("Map Not Closed by walls7!");
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
	
	i = 0;
	while(data->map[i])
	{
		j = 0;
		temp = data->map[i];
		while(data->map[i][j])
		{
			if(temp[j] == '3')
				if(!((data->map[i + 1][j] == '1' && data->map[i - 1][j] == '1') || (data->map[i][j + 1] == '1' && data->map[i][j + 1] == '1')))
					print_error("Wrong Door Postion!");
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