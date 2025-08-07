#include "./player.h"
#include <math.h>

static int	get_step_routine(t_point point, t_point d, void *step_point)
{
	static int	player_step_def;

	if (player_step_def == 0)
		player_step_def = STEP_PER_PIXEL;
	if (--player_step_def == 0)
	{
		((t_point *)step_point)->x = point.x;
		((t_point *)step_point)->y = point.y;
		return (1);
	}
	return (0);
}

void	player_get_step_point(t_player *player)
{
	shoot_ray(
			player->cord,
			player->view_point,
			&(player->step_point),
			get_step_routine);
}

void	player_rotate(t_player *player, float degree)
{
	player->view_point = rotate_point(player->cord, player->view_point, degree);
}

static int	collision_check(t_point *dest, char **map)
{
	if (
		map [(int)TO_INDEX(floor(dest->y - PLAYER_SIZE))]
		[(int)TO_INDEX(floor(dest->x - PLAYER_SIZE))] == '1' ||
		map [(int)TO_INDEX(floor(dest->y + PLAYER_SIZE))]
		[(int)TO_INDEX(floor(dest->x - PLAYER_SIZE))] == '1' ||
		map [(int)TO_INDEX(floor(dest->y - PLAYER_SIZE))]
		[(int)TO_INDEX(floor(dest->x + PLAYER_SIZE))] == '1' ||
		map [(int)TO_INDEX(floor(dest->y + PLAYER_SIZE))]
		[(int)TO_INDEX(floor(dest->x + PLAYER_SIZE))] == '1'
		) 
		return (1);
	return (0);
}

void	player_move(t_player *player, float degree)
{
	t_point	dest;

	player_get_step_point(player);
	dest = rotate_point(player->cord, player->step_point, degree);
	if (collision_check(&dest, player->map))
		return ;
	player->view_point.x += -(player->cord.x - dest.x);
	player->view_point.y += -(player->cord.y - dest.y);
	player->cord.x = dest.x;
	player->cord.y = dest.y;
}
