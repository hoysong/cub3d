#include "../algorithm/my_algorithm.h"
//#include "../algorithm/wall_lkd_list/wall_lkd_list.h"
#include "../player.h"
//#include "../../parser/pars_pub.h"
#include <math.h>
#include <stdio.h>
//#include <stdlib.h>

static inline float	get_vertlen(t_point a, t_point b, t_point c)
{
	float	m;
	if (b.x - a.x == 0)
		m = (b.y - a.y) / ((b.x + 0.01) - a.x);
	else
		m = (b.y - a.y) / (b.x - a.x);

	float result;
	result = my_abs(m*c.x - c.y + (a.y - (m*a.x))) / sqrt(pow(m, 2) + 1);
	return (result);
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

/*가상 맵에서의 벽 좌표를 화면상 좌표로 계산합니다.*/
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

/*화면상 잘리는 처음 노드와 마지막 노드를 보정합니다.*/
void	first_last_correction(t_wall_node *left_wall, t_wall_node *right_wall)
{
	left_wall->info->degree = 0;
	left_wall->info->ray_dest = rotate_point(
			left_wall->info->ray_start, left_wall->info->end_point,
			left_wall->info->degree
			);
	if (shoot_ray(
				left_wall->info->ray_start,
				left_wall->info->ray_dest,
				left_wall->info,
				detect_wall_hit
				))
	{
		left_wall->start_point.y = get_line_y(left_wall->info->ray_hit);
		left_wall->start_point.x = get_line_x(0);
	}
	if (left_wall == right_wall)
		return ;
	right_wall->info->degree = (float)Player_FOV - RAY_RES;
	right_wall->info->ray_dest = rotate_point(
			right_wall->info->ray_start, right_wall->info->end_point,
			right_wall->info->degree
			);
	if (shoot_ray(
				right_wall->info->ray_start,
				right_wall->info->ray_dest,
				right_wall->info,
				detect_wall_hit
				))
	{
		right_wall->end_point.y = get_line_y(right_wall->info->ray_hit);
		right_wall->end_point.x = get_line_x(Player_FOV);
	}
}
