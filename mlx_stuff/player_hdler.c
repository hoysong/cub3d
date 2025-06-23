#include "./player.h"

void	player_rotate(t_player *player, float degree)
{
	player->view_point = rotate_point(player->cord, player->view_point, degree);
}
