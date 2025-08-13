/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_player_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 04:21:59 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 04:24:38 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./player.h"
#include "./mlx_hdler.h"
#include "../parser/pars_pub.h"
#include <stdlib.h>
#include <stdio.h>

/* Set_player's view_point.
 * 'view point' variable will be player's direction of where lookin at.
 */
static void	get_player_view_point(int x, int y)
{
	char	**map;

	map = get_map();
	if (map[y][x] == 'N')
		player()->view_point.y = player()->cord.y - (float)VIEW_DIST;
	else if (map[y][x] == 'S')
		player()->view_point.y = player()->cord.y + (float)VIEW_DIST;
	else
		player()->view_point.y = player()->cord.y;
	if (map[y][x] == 'W')
		player()->view_point.x = player()->cord.x - (float)VIEW_DIST;
	else if (map[y][x] == 'E')
		player()->view_point.x = player()->cord.x + (float)VIEW_DIST;
	else
		player()->view_point.x = player()->cord.x;
}

/* This function find player's location from '(char **)map'.
 * and set player's location on center of indexes of block.
 */
static void	get_start_location(float *fx, float *fy)
{
	char	**map;
	int		x;
	int		y;

	map = get_map();
	x = 0;
	y = 0;
	while (map[y])
	{
		while (!is_player(map[y][x]) && map[y][x])
			x++;
		if (is_player(map[y][x]))
			break ;
		x = 0;
		y++;
	}
	*fx = ((float)x) * SIZE_OF_BLOCK + (float)SIZE_OF_BLOCK / 2;
	*fy = ((float)y) * SIZE_OF_BLOCK + (float)SIZE_OF_BLOCK / 2;
	get_player_view_point(x, y);
}

extern t_player	*set_player(t_player *player);

void	player_init(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	set_player(player);
	player->ratio = ((float)get_minimap_ratio() / 3) / 3;
	player->view_point.x = 0;
	player->view_point.y = 0;
	player->map = get_map();
	get_start_location(&(player->cord.x), &(player->cord.y));
	player_get_step_point(player);
	printf("player info\n");
	printf("├─Location   : x=%f, y=%f\n", player->cord.x, player->cord.y);
	printf("├─view_point : x=%f, y=%f\n",
		player->view_point.x, player->view_point.y);
	printf("├─step_point : x=%f, y=%f\n",
		player->step_point.x, player->step_point.y);
	printf("├─Ratio      : %f\n", player->ratio);
	printf("└─(empty)\n");
}
