#include "./player.h"

void	player_rotate(t_player *player, float degree)
{
	player->view_point = rotate_point(player->cord, player->view_point, degree);
}

static int	get_step_routine(t_point point, t_point d, void *step_point)
{
	static int	player_step_def;

	if (player_step_def == 0)
		player_step_def = STEP_PER_PIXEL;
	if (--player_step_def)
	{
		((t_point *)step_point)->x = point.x;
		((t_point *)step_point)->y = point.y;
		return (1);
	}
	return (0);
}

void	get_player_step_point(void)
{
	shoot_ray(
			player()->cord,
			player()->view_point,
			&(player()->step_point),
			get_step_routine);
}
