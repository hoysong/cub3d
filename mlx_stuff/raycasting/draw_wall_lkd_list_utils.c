/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_lkd_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 07:20:52 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/15 06:24:51 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_defs.h"
#include "../algorithm/my_algorithm.h"

float	get_left_walls_pixel_x(t_wall_node *node, t_point *ray)
{
	return (node->texture->xpm_width
		* ((ray->x - (node->end_point.x - node->wall_width))
			/ node->wall_width));
}

float	get_other_walls_pixel_x(t_wall_node *node, t_point *ray)
{
	return (node->texture->xpm_width
		* ((ray->x - node->start_point.x) / node->wall_width));
}

float	get_pixel_x(t_wall_node *node, t_point *ray)
{
	if (node->prev == NULL
		&& node->next == NULL)
	{
		if (node->correction_flag)
			return (get_other_walls_pixel_x(node, ray));
		return (get_left_walls_pixel_x(node, ray));
	}
	if (node->start_degree <= 0)
		return (get_left_walls_pixel_x(node, ray));
	return (get_other_walls_pixel_x(node, ray));
}
