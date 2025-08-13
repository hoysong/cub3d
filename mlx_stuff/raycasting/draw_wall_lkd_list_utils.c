/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_lkd_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 07:20:52 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 07:22:09 by jinyjeon         ###   ########.fr       */
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
