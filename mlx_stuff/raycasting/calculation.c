/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 06:44:43 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 07:01:50 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../player.h"
#include "../algorithm/my_algorithm.h"
#include <math.h>

/*
 * get vertial length of ray's hit point from player's plain.
 * if b.x - a.x is zero, the nan or inf problem can be happend.
 * So, added some exception. 
 */
extern float	get_line_y(t_point point);
extern int		get_line_x(float degree);

/*convert wall's virtual coordinate to screen coordinate.*/
void	calculate_point_location(t_wall_node *node)
{
	while (node)
	{
		node->start_point.y = get_line_y(node->wall_start_cord);
		node->start_point.x = get_line_x(node->start_degree);
		node->end_point.y = get_line_y(node->wall_end_cord);
		node->end_point.x = get_line_x(node->end_degree);
		node->wall_width = node->end_point.x - node->start_point.x;
		node = node->next;
	}
}

static void	correction_left(t_wall_node *left_wall)
{
	left_wall->info->degree = 0;
	left_wall->info->ray_dest = rotate_point(
			left_wall->info->ray_start, left_wall->info->end_point,
			left_wall->info->degree);
	if (shoot_ray(
			left_wall->info->ray_start,
			left_wall->info->ray_dest,
			left_wall->info,
			detect_wall_hit))
	{
		left_wall->start_point.y = get_line_y(left_wall->info->ray_hit);
		left_wall->start_point.x = get_line_x(0);
	}
}

static void	correction_right(t_wall_node *right_wall)
{
	right_wall->info->degree = (float)PLAYER_FOV - RAY_RES;
	right_wall->info->ray_dest = rotate_point(
			right_wall->info->ray_start, right_wall->info->end_point,
			right_wall->info->degree
			);
	if (shoot_ray(
			right_wall->info->ray_start,
			right_wall->info->ray_dest,
			right_wall->info,
			detect_wall_hit))
	{
		right_wall->end_point.y = get_line_y(right_wall->info->ray_hit);
		right_wall->end_point.x = get_line_x(PLAYER_FOV);
	}
}

void	first_last_correction(t_wall_node *left_wall, t_wall_node *right_wall)
{
	if (left_wall == right_wall)
	{
		if (left_wall->start_point.y > left_wall->end_point.y)
		{
			left_wall->correction_flag++;
			correction_right(right_wall);
		}
		else
			correction_left(left_wall);
		return ;
	}
	correction_left(left_wall);
	if (left_wall == right_wall)
		return ;
	correction_right(right_wall);
}
