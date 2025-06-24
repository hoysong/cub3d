#include "./player.h"
#include <stdio.h>

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

void	player_move(t_player *player)
{
	player_get_step_point(player);
	printf("player cord: x=%f | y=%f\n",
			player->cord.x,
			player->cord.y);
	printf("player step: x=%f | y=%f\n",
			player->step_point.x,
			player->step_point.y);
	printf("calculate  : x=%f | y=%f\n",
			player->step_point.x - player->cord.x,
			player->step_point.y - player->cord.y
	);
	player->view_point.x += -(player->cord.x - player->step_point.x);
	player->view_point.y += -(player->cord.y - player->step_point.y);
	player->cord.x = player->step_point.x;
	player->cord.y = player->step_point.y;
	printf("after player_cord: x=%f | y=%f\n", player->cord.x, player->cord.y);
}
