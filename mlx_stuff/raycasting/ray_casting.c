#include "../algorithm/my_algorithm.h"
#include "../algorithm/wall_lkd_list/wall_lkd_list.h"
#include <stdio.h>

/*put point of wall's start and end point to minimap.*/
static void	put_edge_to_minimap(t_wall_node *node)
{
	while (node)
	{
		put_pixel_to_img(
				&(mlx()->minimap),
				to_minimap_ratio(node->wall_start_cord, node->info->mlx).x,
				to_minimap_ratio(node->wall_start_cord, node->info->mlx).y,
				0x00ffff);
		put_pixel_to_img(
				&(mlx()->minimap),
				to_minimap_ratio(node->wall_end_cord, node->info->mlx).x,
				to_minimap_ratio(node->wall_end_cord, node->info->mlx).y,
				0x00ffff);
		node = node->next;
	}
}

extern void			sort_wall_list(t_wall_node *node);
extern void			draw_wall_lkd_list(t_wall_node *node);
extern t_wall_node	*shoot_fov_ray(t_ray_info *info);
extern void			first_last_correction(t_wall_node *left_wall, t_wall_node *right_wall);
extern  void		calculate_point_location(t_wall_node *node);

static void	degree_correction(t_wall_node *left, t_wall_node *right)
{
	if (right->end_degree < 0)
		right->end_degree += 360;
}

/*Send left wall from player's view to linked list's tail.*/
static void	left_wall_to_last(t_wall_node *node, t_wall_node *lst_node)
{
	if (node->start_degree < -100)
		wall_to_last(node);
	if (lst_node->end_degree > 100)
		wall_to_last(lst_node);
}

/*raycasting logics.*/
void	ray_casting(void)
{
	t_ray_info	info;
	t_wall_node	*node;
	t_wall_node	*start_node;
	t_wall_node	*end_node;

	node = shoot_fov_ray(&info);
	start_node = wall_find_first_node(node);
	end_node = wall_find_lst_node(node);
	put_edge_to_minimap(node);
	degree_correction(start_node, end_node);
	calculate_point_location(node);
	sort_wall_list(node);
	first_last_correction(start_node, end_node);
	left_wall_to_last(start_node, end_node);
	node = wall_find_first_node(node);
	draw_wall_lkd_list(node);
	wall_destroy_list(node);
}
