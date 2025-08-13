/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_fov_ray_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 07:25:30 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 07:30:29 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../player.h"
#include "../cub_defs.h"
#include "../algorithm/my_algorithm.h"
#include "../algorithm/wall_lkd_list/wall_lkd_list.h"
#include "../../parser/pars_pub.h"
#include <math.h>
#include <stdio.h>

/*
 * start of FOV is 0 degree.
 * this function returns degree of points.
 */

float	get_degree(t_point *a, t_point *b, t_point *c)
{
	float	a_b_atan;
	float	c_b_atan;
	float	result_atan;
	float	degree;

	a_b_atan = atan2(a->y - b->y, a->x - b->x);
	c_b_atan = atan2(c->y - b->y, c->x - b->x);
	result_atan = c_b_atan - a_b_atan;
	if (result_atan > PIE)
		result_atan -= 2 * PIE;
	else if (result_atan < -PIE)
		result_atan += 2 * PIE;
	degree = result_atan * (180 / PIE);
	return (degree);
}

/*
 * this calculate texture's virtual coordinate based start point and end point.
 */
void	get_wall_start_end(t_ray_info *info, t_point *start, t_point *end)
{
	t_mlx	*mlx_ptr;

	mlx_ptr = mlx();
	start->x = info->wall_x * SIZE_OF_BLOCK;
	start->y = info->wall_y * SIZE_OF_BLOCK;
	end->x = info->wall_x * SIZE_OF_BLOCK;
	end->y = info->wall_y * SIZE_OF_BLOCK;
	if (&(mlx_ptr->xpm_north) == info->texture
		|| &(mlx_ptr->xpm_east) == info->texture)
		start->x = info->wall_x * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
	if (&(mlx_ptr->xpm_south) == info->texture
		|| &(mlx_ptr->xpm_west) == info->texture)
		end->y = info->wall_y * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
	if (&(mlx_ptr->xpm_south) == info->texture
		|| &(mlx_ptr->xpm_east) == info->texture)
	{
		start->y = info->wall_y * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
		end->x = info->wall_x * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
	}
}

/*
 * This function will..
 * Get texture's start point and end point.
 * Get degree of texture start/end point that start from Fov point
 */
void	add_new_wall_node(t_wall_node *node, t_ray_info *info)
{
	node = wall_init_last_node(node);
	get_wall_start_end(info, &(node->wall_start_cord), &(node->wall_end_cord));
	node->start_degree = get_degree(&(info->end_point),
			&(info->ray_start), &(node->wall_start_cord));
	node->end_degree = get_degree(&(info->end_point),
			&(info->ray_start), &(node->wall_end_cord));
	node->texture = info->texture;
	node->info = info;
}
