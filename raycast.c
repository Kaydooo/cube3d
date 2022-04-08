#include "cub3d.h"

int is_wall(t_vars *vars, double x, double y, double *diff)
{
	int y1 = (int) y;
	int x1 = (int) x;

	if (!diff && !(y == y1 && x == x1)) // check whether starting point on camera plane is wall
	{
		if (y != y1 && x != x1 && vars->map[y1][x1] == '1')
			return (1);
		if (y == y1 && (vars->map[y1][x1] == '1' || (x1 > 0 && vars->map[y1][x1-1] == '1')))
			return (1);
		if (x == x1 && (vars->map[y1][x1] == '1' || (y1 > 0 && vars->map[y1-1][x1-1] == '1')))
			return (1);
	}
	else if (y == y1 && x == x1) // check for corner
	{

		if (vars->map[y1][x1] == '1')
			return (1);
		if (x1 > 0 && vars->map[y1][x1-1] == '1')
			return (1);
		if (y1 > 0 && vars->map[y1-1][x1] == '1')
			return (1);
		if (x1 > 0 && y1 > 0 && vars->map[y1-1][x1-1] == '1')
			return (1);
	}
	else 					// check for sides
	{
		if (diff[0] >= 0.000 && diff[1] >= 0.000 && vars->map[y1][x1] == '1')
			return (1);
		if (diff[0] < 0.000 && diff[1] > 0.000 && y == y1 && vars->map[y1][x1] == '1')
			return (1);
		if (diff[1] < 0.000 && diff[0] > 0.000 && x == x1 && vars->map[y1][x1] == '1')
			return (1);
		if (diff[1] < 0.000 && y == y1 && y1 > 0 && vars->map[y1-1][x1] == '1')
			return (1);
		if (diff[0] < 0.000 && x == x1 && x1 > 0 && vars->map[y1][x1-1] == '1')
			return (1);
	}
	return (0);
}

double	raycast(t_vars *vars, t_player *player, double *pos)
{
	double	diff[2];
	double	unit_dist[2];
	double	total_dist[1];
	int		move_pos[2]; // the x and y values we increment along by 1 unit
	double	match_pos[2]; // the corresponding x and y valyes to the increments

	// first check if point on camera plane intersects with a wall
	if (is_wall(vars, pos[0], pos[1], NULL))
		return (0);

	diff[0] = pos[0] - player->pos[0]; // calculates dx
	diff[1] = pos[1] - player->pos[1]; // calculates dy

	// calculate distance along ray for per unit of x and y
	unit_dist[0] = diff[0] == 0 ? 0 : sqrt(1 + pow((diff[1]) / (diff[0]), 2)); // per x
	unit_dist[1] = diff[1] == 0 ? 0 : sqrt(1 + pow((diff[0]) / (diff[1]), 2)); // per y

	// set starting point of ray so that it's on a side of a unit
	move_pos[0] = pos[0]; move_pos[1] = pos[1];
	if (pos[0] != (int) pos[0] && diff[0] != 0.000)
		move_pos[0] = diff[0] < 0.000 ? (int) pos[0] : (int) pos[0] + 1;
	if (pos[1] != (int) pos[1] && diff[1] != 0.000)
		move_pos[1] = diff[1] < 0.000 ? (int) pos[1] : (int) pos[1] + 1;
	if (diff[0] != 0.000)
		match_pos[1] = pos[1] + ((diff[1] / diff[0]) * (move_pos[0] - pos[0]));
	if (diff[1] != 0.000)
		match_pos[0] = pos[0] + ((diff[0] / diff[1]) * (move_pos[1] - pos[1]));

	/* possible improvement: merge the movement along unit x and unit y rather
		than doing separately. This will probably increase speed */
	
	// calculate distance allong x increment
	while (move_pos[0] >= 0 && move_pos[0] < vars->m_wt 
		&& match_pos[1] >= 0.000 && match_pos[1] < vars->m_ht
		&& diff[0] != 0.000 && !is_wall(vars, move_pos[0], match_pos[1], diff))
	{
		move_pos[0] += diff[0] < 0.000 ? -1 : 1;
		match_pos[1] += diff[0] >= 0.000 ? (diff[1] / diff[0]) : (diff[1] / diff[0]) * -1;
	}
	total_dist[0] = unit_dist[0] * ((double) move_pos[0] - pos[0]);
	total_dist[0] *= total_dist[0] < 0.000 ? -1 : 1;
	//printf("x: %d | y: %f | dist: %f\n", move_pos[0], match_pos[1], total_dist[0]);

	// calculate distance allong y increment
	while (move_pos[1] >= 0 && move_pos[1] < vars->m_ht 
		&& match_pos[0] >= 0.000 && match_pos[0] < vars->m_wt
		&& diff[1] != 0.000 && !is_wall(vars, match_pos[0], move_pos[1], diff))
	{
		move_pos[1] += diff[1] < 0.000 ? -1 : 1;
		match_pos[0] += diff[1] >= 0.000 ? (diff[0] / diff[1]) : (diff[0] / diff[1]) * -1;
	}
	total_dist[1] = unit_dist[1] * ((double) move_pos[1] - pos[1]);
	total_dist[1] *= total_dist[1] < 0.000 ? -1 : 1;
	//printf("x: %f | y: %d | dist: %f\n", match_pos[0], move_pos[1], total_dist[1]);

	// return shortest length
	if (total_dist[0] < total_dist[1])
		return (total_dist[0]);
	return (total_dist[1]);
}