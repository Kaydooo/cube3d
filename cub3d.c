#include "cub3d.h"

void	set_view(t_vars *vars, t_img *image)
{
	double	dist; // distance from wall to camera plane
	double	pos[2]; // position along the camera plane relative to center of plane
	double	shift[2]; // increment along camera plane
	setvbuf(stdout, NULL, _IONBF, 0);

	// initialize image
	image->tmp_img = image->img;
	image->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	image->addr = mlx_get_data_addr(image->img, &(image->bits_per_pixel),
		&(image->line_length), &(image->endian));

	// set starting position and increment (+0.05) along camera plane
	pos[0] = vars->player->c_pos[0] - vars->player->c_dir[0];
	pos[1] = vars->player->c_pos[1] - vars->player->c_dir[1];
	shift[0] = vars->player->c_dir[0] == 0 ? 0
		: CAM / sqrt(1 + pow(vars->player->c_dir[1] / vars->player->c_dir[0], 2));
	if (vars->player->c_dir[0] < 0)
		shift[0] *= -1;
	shift[1] = vars->player->c_dir[1] == 0 ? 0
		: CAM / sqrt(1 + pow(vars->player->c_dir[0] / vars->player->c_dir[1], 2));
	if (vars->player->c_dir[1] < 0)
		shift[1] *= -1;

	// cast rays and draw within Field of View
	//printf("pos[0]: %f | pos[1]: %f\n", vars->player->c_pos[0] + vars->player->c_dir[0], vars->player->c_pos[1] + vars->player->c_dir[1]);
	while (!(shift[0] > 0.000 && pos[0] > (vars->player->c_pos[0] + vars->player->c_dir[0]) 
			|| shift[0] < 0.000 && pos[0] < (vars->player->c_pos[0] + vars->player->c_dir[0])
			|| shift[1] > 0.000 && pos[1] > (vars->player->c_pos[1] + vars->player->c_dir[1])
			|| shift[1] < 0.000 && pos[1] < (vars->player->c_pos[1] + vars->player->c_dir[1])))
	{
		dist = raycast(vars, vars->player, pos);
		//printf("x: %f | y: %f | dist: %f\n", pos[0], pos[1], dist);
		draw_image(image, vars->player, dist, pos);
		pos[0] += shift[0];
		pos[1] += shift[1];
		if (pos[0] < 0 || pos[0] >= vars->m_wt
			|| pos[1] < 0 || pos[1] >= vars->m_ht)
			break ;
	/*	if (shift[0] > 0.000 && pos[0] > (vars->player->c_pos[0] + vars->player->c_dir[0]) 
			|| shift[0] < 0.000 && pos[0] < (vars->player->c_pos[0] + vars->player->c_dir[0])
			|| shift[1] > 0.000 && pos[1] > (vars->player->c_pos[1] + vars->player->c_dir[1])
			|| shift[1] < 0.000 && pos[1] < (vars->player->c_pos[1] + vars->player->c_dir[1]))
			break ;		*/
	}
	mlx_put_image_to_window(vars->mlx, vars->win, image->img, 0, 0);
	if (image->tmp_img)
		mlx_destroy_image(vars->mlx, image->tmp_img);
}

void set_camera(t_player *player)
{
	int mag = 1; // do not change

	// set camera  starting position,
	// which is midpoint of camera plane
	player->c_pos[0] = player->pos[0] + player->dir[0];
	player->c_pos[1] = player->pos[1] + player->dir[1];
	
	// set camera direction, which is a 
	// rightward line from camera position of length $mag
	player->c_dir[0] = player->dir[1] == 0 ? 0
		: CAM_MAG / sqrt((1 + pow(player->dir[0] / player->dir[1], 2)));
	player->c_dir[1] = player->dir[0] == 0 ? 0
		: CAM_MAG / sqrt((1 + pow(player->dir[1] / player->dir[0], 2)));
	if (player->dir[0] >= 0.000 && player->dir[1] >= 0.000)
		player->c_dir[0] *= -1;
	if (player->dir[0] < 0.000 && player->dir[1] > 0.000)
	{
		player->c_dir[0] *= -1;
		player->c_dir[1] *= -1;
	}
	if (player->dir[0] <= 0.000 && player->dir[1] <= 0.000)
		player->c_dir[1] *= -1;
}

int	move(int key, t_vars *vars)
{
	double speed = 0.1;
	double rotate = 0.0174533; // in radians (1)
	if (key == 119) // up (w)
	{
		if (is_wall(vars, vars->player->pos[0] + (speed * vars->player->dir[0]),
			vars->player->pos[1] + (speed * vars->player->dir[1]), NULL))
			return (key);
		vars->player->pos[0] += (speed * vars->player->dir[0]);
		vars->player->pos[1] += (speed * vars->player->dir[1]);
		set_camera(vars->player);
		set_view(vars, vars->img);
	}
	if (key == 115) // down (s)
	{
		if (is_wall(vars, vars->player->pos[0] - (speed * vars->player->dir[0]),
			vars->player->pos[1] - (speed * vars->player->dir[1]), NULL))
			return (key);
		vars->player->pos[0] -= (speed * vars->player->dir[0]);
		vars->player->pos[1] -= (speed * vars->player->dir[1]);
		set_camera(vars->player);
		set_view(vars, vars->img);	
	}
	if (key == 97) // left (a)
	{
		if (is_wall(vars, vars->player->pos[0] + (speed * vars->player->dir[1]),
			vars->player->pos[1] - (speed * vars->player->dir[0]), NULL))
			return (key);
		vars->player->pos[0] += (speed * vars->player->dir[1]);
		vars->player->pos[1] -= (speed * vars->player->dir[0]);
		set_camera(vars->player);
		set_view(vars, vars->img);	
	}
	if (key == 100) // right (d)
	{
		if (is_wall(vars, vars->player->pos[0] - (speed * vars->player->dir[1]),
			vars->player->pos[1] + (speed * vars->player->dir[0]), NULL))
			return (key);
		vars->player->pos[0] -= (speed * vars->player->dir[1]);
		vars->player->pos[1] += (speed * vars->player->dir[0]);
		set_camera(vars->player);
		set_view(vars, vars->img);
	}
	// https://stackoverflow.com/questions/11773889/how-to-calculate-a-vector-from-an-angle-with-another-vector-in-2d)
	if (key == 65361 || key == 65363) // rotate left/right
	{
		//printf("1\n");
		if (key == 65363)
			rotate *= -1;
		double temp_x = (vars->player->dir[0] * cos(rotate)) + (vars->player->dir[1] * sin(rotate));
		double temp_y = (-1 * vars->player->dir[0] * sin(rotate)) + (vars->player->dir[1] * cos(rotate));
		vars->player->dir[0] = temp_x;
		vars->player->dir[1] = temp_y;
		set_camera(vars->player);
		set_view(vars, vars->img);
	}
	return (key);
}

int	main(void)
{
	t_vars		vars;
	t_player	player;
	t_img		image;

	// initialize map
	vars.map = calloc(5, sizeof(char *));
	vars.map[0] =  strdup("111111111111111111111111");
	vars.map[1] =  strdup("100000000000000001111111");
	vars.map[2] =  strdup("100000000000000000000001");
	vars.map[3] =  strdup("100000000000000000000001");
	vars.map[4] =  strdup("100000000000000000000001");
	vars.map[5] =  strdup("100000000000000000000001");
	vars.map[6] =  strdup("100001111111000000000001");
	vars.map[7] =  strdup("100001000001000000001001");
	vars.map[8] =  strdup("100001011111000000001001");
	vars.map[9] =  strdup("100001010001000010001001");
	vars.map[10] = strdup("100001010000000000000001");
	vars.map[11] = strdup("100001010000000000000001");
	vars.map[12] = strdup("100001010000000000000001");
	vars.map[13] = strdup("100001010000000000000001");
	vars.map[14] = strdup("100001010000000000000001");
	vars.map[15] = strdup("100001010000000000000001");
	vars.map[16] = strdup("100001010000000000000001");
	vars.map[17] = strdup("100000000000000000000001");
	vars.map[18] = strdup("100000000000000000000001");
	vars.map[19] = strdup("100000N00000000000000001");
	vars.map[20] = strdup("100000100100000000000001");
	vars.map[21] = strdup("100000000000000000000001");
	vars.map[22] = strdup("100000000000000000000001");
	vars.map[23] = strdup("111111111111111111111111");
	vars.m_wt = 24; vars.m_ht = 24; // needs to be hard coded

	// initialize player
	player.pos[0] = 7.5; player.pos[1] = 19; // needs to be hard coded
	player.dir[0] = 0; player.dir[1] = -1;	// needs to be hard coded
	set_camera(&player);
	vars.player = &player;
/*	printf("c_pos x: %f\nc_pos y: %f\nc_dir x: %f\nc_dir y: %f\n", 
		vars.player->c_pos[0], vars.player->c_pos[1], vars.player->c_dir[0], vars.player->c_dir[1]); */
	
	// initialize window
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "cub3d");
	image.img = NULL;
	set_view(&vars, &image);
	vars.img = &image;

	mlx_hook(vars.win, 2, 1L<<0, move, &vars);
	mlx_loop(vars.mlx);
}