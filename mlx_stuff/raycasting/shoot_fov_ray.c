/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_fov_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 06:40:13 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 07:30:15 by jinyjeon         ###   ########.fr       */
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
extern float	get_degree(t_point *a, t_point *b, t_point *c);
extern void		get_wall_start_end(t_ray_info *info,
					t_point *start, t_point *end);
extern void		add_new_wall_node(t_wall_node *node, t_ray_info *info);

static void	init_info(t_ray_info *info)
{
	info->map = get_map();
	info->mlx = mlx();
	info->degree = 0;
	info->wall_x = 0;
	info->wall_y = 0;
	info->wall_addr = NULL;
	info->texture = NULL;
	info->ray_start = player()->cord;
	info->end_point = player()->view_point;
	info->end_point = rotate_point(
			info->ray_start,
			info->end_point,
			((float)PLAYER_FOV / 2) * -1);
	info->ray_dest = info->end_point;
}

/*
 * Wrap function.
 * Rotate end_point based on ray_start point.
 * return's next_ray_point.
 */
static inline t_point	next_ray_point(t_ray_info *info)
{
	return (rotate_point(info->ray_start, info->end_point, info->degree));
}

/*
 * Wrap function.
 * Shoot infinite ray to detect wall hit.
 * Shoot from: ray_start.
 * Shoot to  : ray_dest.
 */
static inline int	shoot_ray_until_hit(t_ray_info *info)
{
	return (shoot_inf_ray(info->ray_start,
			info->ray_dest, info, detect_wall_hit));
}

/*
 * Wrap function.
 * check prev ray info and current ray info.
 * compare prev's texture and current texture.
 * compare prev's wall and current wall.
 */
static inline int	new_texture_or_wall(t_ray_info *prev, t_ray_info *current)
{
	return (prev->texture != current->texture
		|| prev->wall_addr != current->wall_addr);
}

t_wall_node	*shoot_fov_ray(t_ray_info *info)
{
	t_ray_info	prev_info;
	t_wall_node	*node;

	node = wall_init_node();
	init_info(info);
	prev_info = *info;
	while (info->degree <= PLAYER_FOV)
	{
		info->ray_dest = next_ray_point(info);
		if (shoot_ray_until_hit(info))
		{
			if (new_texture_or_wall(&prev_info, info))
			{
				add_new_wall_node(node, info);
				node = node->next;
			}
		}
		prev_info = *info;
		info->degree += RAY_RES;
	}
	node = wall_find_first_node(node);
	node = node->next;
	free(node->prev);
	node->prev = NULL;
	return (node);
}
