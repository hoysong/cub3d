#include "../algorithm/my_algorithm.h"
#include "../algorithm/wall_lkd_list/wall_lkd_list.h"
#include <stdio.h>

//static void	print_node(t_wall_node *node)
//{
//	if (node != NULL)
//	{
//		printf("width: %f\n", node->wall_width);
//	}
//	else
//		printf("NULL node..\n");
//}

/*미니맵에 ray의 충돌판정이 된 면을 표시합니다.*/
/*찍혀야 하는 면의 모서리에 점을 찍어봅니다.*/
/*ray_casting함수에서만 사용합니다.*/
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

/*리스트를 정렬합니다.*/
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

static void	left_wall_to_last(t_wall_node *node, t_wall_node *lst_node)
{
	if (node->start_degree < -100)
		wall_to_last(node);
	if (lst_node->end_degree > 100)
		wall_to_last(lst_node);
}

void	ray_casting(void)
{
	t_ray_info	info;
	t_wall_node	*node;
	t_wall_node	*start_node;
	t_wall_node	*end_node;

	t_wall_node	*start_next;

//	printf("NEW_FRAME=================================\n");
	node = shoot_fov_ray(&info);
	start_node = wall_find_first_node(node);
		start_next = start_node->next;
	end_node = wall_find_lst_node(node);
	put_edge_to_minimap(node);
	degree_correction(start_node, end_node);
//		print_node(start_node);
//		print_node(start_next);
	calculate_point_location(node);
//		print_node(start_node);
//		print_node(start_next);
	sort_wall_list(node);
	first_last_correction(start_node, end_node);
	/*만약 좌측면의 노드가 -각도로 나가있다면 마지막에 그려지도록 만듦.*/
	left_wall_to_last(start_node, end_node);
	node = wall_find_first_node(node);
	draw_wall_lkd_list(node);
	wall_destroy_list(node);
}
