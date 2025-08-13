/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_defs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 04:30:50 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 07:48:14 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_DEFS_H
# define CUB_DEFS_H

/*Window size.*/
# define WIN_WIDTH	600
# define WIN_HEIGHT	490
# define HALF_WIN_WIDTH		300
# define HALF_WIN_HEIGHT	245

/********************/
/* Minimap handler. */
/********************/

/*Minimap size.*/
# define MINISIZE	160
/*Minimap BG_color.*/
# define BG_COLOR	0x666666
/*Minimap GridColor.*/
# define GRIDCOLOR	0x666666
/*Minimap WallColor.*/
# define WALLCOLOR	0x222222
/*FOV_COLOR*/
# define FOV_COLOR	0x990000

/*
 * size of block.
 * This can adjust virtual map's size.
 * So, if SIZE_OF_BLOCK adjusted, some defines must be adjusted too.
 */
# define SIZE_OF_BLOCK	50

/*Virtual coordinate based player size.*/
# define PLAYER_SIZE	6

/*Player FOV.*/
# define PLAYER_FOV		65

/*Player Angle per tick.*/
# define CAM_ROTATE_ANGLE	2

/*Player's move distance.*/
# define STEP_PER_PIXEL	5

/*Set interval of ray.*/
# define RAY_RES		0.5

/******************/
/* Do not adjust. */
/******************/

/*Convert Player cordinate to minimap_res.*/
//# define MINI_RES(X) ((X)/(float)SIZE_OF_BLOCK)
//# define TO_INDEX(X) ((X)/(float)SIZE_OF_BLOCK)

#endif
