/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_lkd_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 07:02:00 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/15 06:34:02 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_defs.h"
#include "../algorithm/my_algorithm.h"

extern float	get_left_walls_pixel_x(t_wall_node *node, t_point *ray);
extern float	get_other_walls_pixel_x(t_wall_node *node, t_point *ray);
extern float	get_pixel_x(t_wall_node *node, t_point *ray);

static inline float	get_pixel_y(t_wall_node *node,
		t_point *ray, t_point *start_ray, float lower_point)
{
	return (node->texture->xpm_height
		* ((ray->y - start_ray->y) / (lower_point - start_ray->y)));
}

static inline void	put_xpm_pixel(
		t_wall_node *node, t_point *ray, t_point *pixel)
{
	put_pixel_to_img(&(node->info->mlx->background), ray->x, ray->y,
		get_xpm_pixel_color(*(node->texture), *pixel));
}

/*
 * From screen, draw a vertical line
 * Calculate pixel's location and convert it to img's pixel location.
 */
static inline int	put_texture(t_point ray, t_point y, void *param)
{
	float		lower_point;
	t_wall_node	*node;
	t_point		start_ray;
	t_point		pixel;

	(void)y;
	node = param;
	ray.y = (int)ray.y;
	start_ray = ray;
	lower_point = ((float)(HALF_WIN_HEIGHT))
		+ (((float)(HALF_WIN_HEIGHT)) - ray.y);
	if (ray.x < 0)
		return (0);
	else if (ray.x >= WIN_WIDTH)
		return (1);
	pixel.x = get_pixel_x(node, &ray);
	if (ray.y < 0)
		ray.y = 0;
	while ((ray.y < lower_point) && ray.y < WIN_HEIGHT)
	{
		pixel.y = get_pixel_y(node, &ray, &start_ray, lower_point);
		put_xpm_pixel(node, &ray, &pixel);
		ray.y += 1;
	}
	return (0);
}

/*
 * This function will put textures.
 * Draw a line that start from start_point to end_point.
 * start_point can be texture's start and end_point can be texture's last.
 */
void	draw_wall_lkd_list(t_wall_node *node)
{
	t_mlx	*mlx_ptr;

	mlx_ptr = mlx();
	while (node)
	{
		shoot_ray(node->start_point, node->end_point, node, put_texture);
		node = node->next;
	}
}
