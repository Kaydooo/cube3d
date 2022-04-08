#ifndef CUB3D_H
# define CUB3D_H

# include "mlx_linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# define WIDTH 1024		// width of window
# define HEIGHT 500		// height of window
# define CAM 0.001 		// lower the value, the more clear image will be
# define CAM_MAG 0.5

typedef struct	s_img {
	void	*img;
	void	*tmp_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_player {
	double	pos[2]; 	// player position 0:x | 1:y
	double	dir[2];		// player direction 0:x | 1:y
	double	c_pos[2];	// camera position 0:x | 1:y
	double	c_dir[2];	// camera drrection 0:x | 1:y
}				t_player;

typedef struct s_vars {
	void		*mlx;
	void		*win;
	t_img		*img;
	t_player	*player;
	char		**map;
	int			m_ht;
	int			m_wt;
}				t_vars;

double	raycast(t_vars *vars, t_player *player, double *pos);
void	draw_image(t_img *image, t_player *player, double dist, double *pos);
int 	is_wall(t_vars *vars, double x, double y, double *diff);

#endif