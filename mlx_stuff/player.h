/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 04:45:20 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 04:45:22 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "./cub_defs.h"
# include "./algorithm/my_algorithm.h"

typedef struct s_player
{
	t_point	cord;
	t_point	step_point;
	t_point	view_point;
	float	ratio;
	char	**map;
}t_player;

/*init player struct.*/
void		player_init(void);
/*returns player struct.*/
t_player	*player(void);
/*rotate players view point.*/
void		player_rotate(t_player *player, float degree);
/*change player's location.*/
void		player_move(t_player *player, float degree);
void		player_get_step_point(t_player *player);

#endif
