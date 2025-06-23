#ifndef PLAYER_H
# define PLAYER_H
# include "./algorithm/my_algorithm.h"
# include "./cub_defs.h"

typedef struct s_player
{
	t_point	cord;
	t_point	view_point;
	t_point	step_dist;
	float	ratio;
}t_player;

void		player_init(void);
t_player	*player(void);

#endif
