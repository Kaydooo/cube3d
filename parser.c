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

int	parse_map(t_data *data, int argc, char **argv)
{
	check_map_name(data, argc, argv);
	check_elements(data);
	return (0);
}