#include "../player.h"
#include "../cub_defs.h"
#include "../algorithm/my_algorithm.h"
#include "../algorithm/wall_lkd_list/wall_lkd_list.h"
#include "../../parser//pars_pub.h"
#include <math.h>
#include <stdio.h>

static float	get_degree(t_point *a, t_point *b, t_point *c)
{
	t_point	a_b_vect;
	t_point	c_b_vect;
	float	a_b_atan;
	float	c_b_atan;
	float	result_atan;
	float	degree;
	int	over_180_flag;

	over_180_flag = 0;
	a_b_vect.x = a->x - b->x;
	a_b_vect.y = a->y - b->y;
	c_b_vect.x = c->x - b->x;
	c_b_vect.y = c->y - b->y;

	a_b_atan = atan2(a_b_vect.y, a_b_vect.x);
	c_b_atan = atan2(c_b_vect.y, c_b_vect.x);
	result_atan = c_b_atan - a_b_atan;
	/*정규화 if문.*/
	if (result_atan > Pie)
	{
		result_atan -= 2*Pie;
		++over_180_flag;
	}
	else if (result_atan < -Pie)
	{
		result_atan += 2*Pie;
	}
	/*계산된 atan 값을 각도로 변환.*/
	degree = result_atan * (180 / Pie);
	printf("deg_1: %f\n", degree);
//	if (degree < 0)
//		degree += 360;
//	printf("deg_2: %f\n", degree);
	//printf("before: %f\n", degree);
	///*특정 상황에서는 각도를 360도로 계산하도록 변환.*/
	//	degree+= 360;
	//printf("after: %f\n", degree);
	///*SEGV 해결용.*/
	//if (degree > 220)
	//{
	//	degree -= 360;
	//}
	return (degree);
}

/*텍스쳐가 입혀질 면의 시작좌표와 끝좌표를 구하는 과정.*/
static void	get_wall_start_end(t_ray_info *info, t_point *start, t_point *end)
{
	t_mlx	*mlx_ptr = mlx();

	if (&(mlx_ptr->xpm_north) == info->texture)
	{
		start->x = info->wall_x * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
		start->y = info->wall_y * SIZE_OF_BLOCK;
		end->x = info->wall_x * SIZE_OF_BLOCK;
		end->y = info->wall_y * SIZE_OF_BLOCK;
	}
	else if (&(mlx_ptr->xpm_south) == info->texture)
	{
		start->x = info->wall_x * SIZE_OF_BLOCK;
		start->y = info->wall_y * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
		end->x = info->wall_x * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
		end->y = info->wall_y * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
	}
	else if (&(mlx_ptr->xpm_west) == info->texture)
	{
		start->x = info->wall_x * SIZE_OF_BLOCK;
		start->y = info->wall_y * SIZE_OF_BLOCK;
		end->x = info->wall_x * SIZE_OF_BLOCK;
		end->y = info->wall_y * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
	}
	else if (&(mlx_ptr->xpm_east) == info->texture)
	{
		start->x = info->wall_x * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
		start->y = info->wall_y * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
		end->x = info->wall_x * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
		end->y = info->wall_y * SIZE_OF_BLOCK;
	}
}

/*새로운 면 노드에 대한 정보를 담은 노드를 생성합니다.*/
static void	add_new_wall_node(t_wall_node *node, t_ray_info *info)
{
	printf("NEW_NODE\n");
	node = wall_init_last_node(node);
	get_wall_start_end(info, &(node->wall_start_cord), &(node->wall_end_cord));
	node->start_degree =
		get_degree(&(info->end_point), &(info->ray_start), &(node->wall_start_cord));
	node->end_degree =
		get_degree(&(info->end_point), &(info->ray_start), &(node->wall_end_cord));
	node->texture = info->texture;
	node->info = info;
}

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
			((float)Player_FOV / 2)*-1
			);
	info->ray_dest = info->end_point;
}

t_wall_node	*shoot_fov_ray(t_ray_info *info)
{
	t_ray_info	prev_info;
	t_wall_node	*node;
	node = wall_init_node();

	init_info(info);
	prev_info = *info;

	while (info->degree <= Player_FOV)
	{
		info->ray_dest = rotate_point(
				info->ray_start, info->end_point,
				info->degree
				);
		if (shoot_ray(info->ray_start, info->ray_dest, info, detect_wall_hit))
		{
			/*새로운 벽이나 새로운 텍스쳐에 도달했는가?*/
			if (prev_info.texture != info->texture ||
				prev_info.wall_addr != info->wall_addr)
			{
				/*맞다면 노드를 생성한다.*/
				add_new_wall_node(node, info);
				node = node->next;
			}
		}
		prev_info = *info;
		info->degree += RAY_RES;
	}
	/*처음 노드가 비어있어서 첫 노드만 없애는 작업*/
	node = wall_find_first_node(node);
	node = node->next;
	free(node->prev);
	node->prev = NULL;
	return (node);
}
