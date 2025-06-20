#ifndef PLAYER_H
# define PLAYER_H
# define Player_FOV	90
# include "./line_algorithm/my_algorithm.h"
//# include "./mlx_hdler.h"

typedef struct s_player
{
	t_point	cord;
//	float	x;
//	float	y;
	float	degree;
	t_point	view_point;
	float	ratio;
//	t_img	img;
}t_player;

void		player_init(void);
t_player	*player(void);

#endif
