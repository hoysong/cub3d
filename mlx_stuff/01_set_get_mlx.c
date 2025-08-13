/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_set_get_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 03:59:35 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 03:59:43 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_hdler.h"
#include "./player.h"
#include <stdlib.h>

/*get mlx struct.*/
t_mlx	*set_mlx(t_mlx *mlx)
{
	static t_mlx	*static_mlx;

	if (static_mlx == NULL)
		static_mlx = mlx;
	return (static_mlx);
}

inline t_mlx	*mlx(void)
{
	return (set_mlx(NULL));
}

/*get player struct.*/
t_player	*set_player(t_player *player)
{
	static t_player	*static_player;

	if (static_player == NULL)
		static_player = player;
	return (static_player);
}

inline t_player	*player(void)
{
	return (set_player(NULL));
}
