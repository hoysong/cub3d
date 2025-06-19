#ifndef PLAYER_H
# define PLAYER_H
# define Player_FOV	90
//# include "./mlx_hdler.h"

typedef struct s_player
{
	float	x;
	float	y;
	float	degree;
//	t_img	img;
}t_player;

void		player_init(void);
t_player	*player(void);

#endif
