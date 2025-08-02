#include "./my_algorithm.h"
#include "./wall_lkd_list/wall_lkd_list.h"
#include "../player.h"
#include "../../parser/pars_pub.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static inline float	get_vertlen(t_point a, t_point b, t_point c)
{
	float	m;
	m = (b.y - a.y) / (b.x - a.x);

	float result;
	result = my_abs(m*c.x - c.y + (a.y - (m*a.x))) / sqrt(pow(m, 2) + 1);
	return (result);
}

void	init_info(t_ray_info *info)
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

float	get_degree(t_point *a, t_point *b, t_point *c)
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
	/*특정 상황에서는 각도를 360도로 계산하도록 변환.*/
	if (over_180_flag)
		degree+= 360;
	/*SEGV 해결용.*/
	if (degree > 220)
	{
		degree -= 360;
	}
	return (degree);
}

/*텍스쳐가 입혀질 면의 시작좌표와 끝좌표를 구하는 과정.*/
void	get_wall_start_end(t_ray_info *info, t_point *start, t_point *end)
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
void	add_new_wall_node(t_wall_node *node, t_ray_info *info)
{
	node = wall_init_last_node(node);
	get_wall_start_end(info, &(node->wall_start_cord), &(node->wall_end_cord));
	node->start_degree =
		get_degree(&(info->end_point), &(info->ray_start), &(node->wall_start_cord));
	node->end_degree =
		get_degree(&(info->end_point), &(info->ray_start), &(node->wall_end_cord));
	node->texture = info->texture;
	node->info = info;
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

/*찍혀야 하는 면의 모서리에 점을 찍어봅니다.*/
void	try_put_edge_to_minimap(t_wall_node *node)
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

/*화면상 위치할 좌표를 지정합니다.*/
static inline float	get_line_y(t_point point)
{
	float	vert_len;
	float	inverse;

	vert_len = get_vertlen(
			player()->cord,
			rotate_point(player()->cord, player()->view_point, 90),
			point);
	inverse = (SIZE_OF_BLOCK * WIN_HEIGHT) / vert_len;
	inverse = (float)((WIN_HEIGHT >> 1) - (inverse / 2));
	return (inverse);
}

/*화면상 위치할 좌표를 지정합니다.*/
static inline int	get_line_x(float degree)
{
	float	degree_to_percent = degree / Player_FOV * 100;
	float	line_location = WIN_WIDTH * (degree_to_percent / 100);
	if (line_location == WIN_WIDTH)
		line_location = WIN_WIDTH - 1;
	return (line_location);
}

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

void	first_last_correction(t_wall_node *left_wall, t_wall_node *right_wall)
{
	left_wall->info->degree = 0;
	left_wall->info->ray_dest = rotate_point(
			left_wall->info->ray_start, left_wall->info->end_point,
			left_wall->info->degree
			);
	if (shoot_ray(left_wall->info->ray_start, left_wall->info->ray_dest, left_wall->info, detect_wall_hit))
	{
		{
			left_wall->start_point.y = get_line_y(left_wall->info->ray_hit);
			left_wall->start_point.x = get_line_x(0);
		}
	}
	if (left_wall == right_wall)
		return ;
	right_wall->info->degree = (float)Player_FOV - RAY_RES;
	right_wall->info->ray_dest = rotate_point(
			right_wall->info->ray_start, right_wall->info->end_point,
			right_wall->info->degree
			);
	if (shoot_ray(right_wall->info->ray_start, right_wall->info->ray_dest, right_wall->info, detect_wall_hit))
	{
		{
			right_wall->end_point.y = get_line_y(right_wall->info->ray_hit);
			right_wall->end_point.x = get_line_x(Player_FOV);
		}
	}
}

/*ray를 가로 대각선으로 조사하며 세로축의 선을 그려내는 로직이다.*/
int	put_texture(t_point ray, t_point y, void *param)
{
	float	lower_point = ((float)(WIN_HEIGHT >> 1)) + (((float)(WIN_HEIGHT >> 1)) - ray.y);
	t_wall_node	*node = param;
	t_point		start_ray = ray;
	t_point		pixel = ray;

	if (ray.x < 0)
		return (0);
	else if (ray.x >= WIN_WIDTH)
		return (1);
	if (node->start_degree <= 0)
	{
		pixel.x = node->texture->xpm_width * ((ray.x - (node->end_point.x - node->wall_width)) / node->wall_width);
	}
	else
	{
		pixel.x = node->texture->xpm_width * ((ray.x - node->start_point.x) / node->wall_width);
	}
	if (ray.y < 0)
		ray.y = 0;
	while ((ray.y < lower_point) && ray.y < WIN_HEIGHT)
	{
		pixel.y =
		node->texture->xpm_height *
		(
		(ray.y - start_ray.y)
		/
		((WIN_HEIGHT >> 1) + ((WIN_HEIGHT >> 1) - start_ray.y) - start_ray.y)
		);
		put_pixel_to_img(&(node->info->mlx->background), ray.x, ray.y,
				get_xpm_pixel_color(*(node->texture), pixel)
				);
		ray.y++;
	}
	return (0);
}

void	try_put_texture(t_wall_node *node)
{
	t_mlx	*mlx_ptr = mlx();

	while (node)
	{
		shoot_ray(node->start_point, node->end_point, node, put_texture);
		node = node->next;
	}
}

extern void	sort_wall_list(t_wall_node *node);

void	ray_casting(void)
{
	t_ray_info	info;
	t_wall_node	*node;
	t_wall_node	*start_node;
	t_wall_node	*end_node;

	node = shoot_fov_ray(&info);
	start_node = wall_find_first_node(node);
	end_node = wall_find_lst_node(node);
	/*미니맵에 ray의 충돌판정이 된 면을 표시합니다.*/
	try_put_edge_to_minimap(node);
	/*가상 맵에서의 벽 좌표를 화면상 좌표로 계산합니다.*/
	calculate_point_location(node);
	/*화면상 잘리는 처음 노드와 마지막 노드를 보정합니다.*/
	first_last_correction(start_node, end_node);
	/*리스트를 정렬합니다.*/
	sort_wall_list(node);
	/*정렬 이후 헤드노드를 찾습니다.*/
	node = wall_find_first_node(node);
	/*텍스쳐를 입혀봅니다.*/
	try_put_texture(node);
	/*linked_list를 삭제합니다.*/
	wall_destroy_list(node);
}
