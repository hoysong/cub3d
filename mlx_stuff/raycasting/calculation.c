#include "../player.h"
#include "../algorithm/my_algorithm.h"
#include <math.h>

/*
 * get vertial length of ray's hit point from player's plain.
 * if b.x - a.x is zero, the nan or inf problem can be happend.
 * So, added some exception. 
 */
static inline float	get_vertlen(t_point a, t_point b, t_point c)
{
	float	m;
	float result;

	if (b.x - a.x == 0)
		m = (b.y - a.y) / ((b.x + 0.01) - a.x);
	else
		m = (b.y - a.y) / (b.x - a.x);
	result = my_abs(m*c.x - c.y + (a.y - (m*a.x))) / sqrt(pow(m, 2) + 1);
	return (result);
}

/*convert texture point.y coordinate to screen coordinate.*/
static inline float	get_line_y(t_point point)
{
	float	vert_len;
	float	inverse;

	vert_len = get_vertlen(
			player()->cord,
			rotate_point(player()->cord, player()->view_point, 90),
			point);
	inverse = (SIZE_OF_BLOCK * WIN_HEIGHT) / vert_len;
	inverse = (float)(HALF_WIN_HEIGHT - (inverse / 2));
	return (inverse);
}

/*convert texture point.x coordinate to screen coordinate.*/
static inline int	get_line_x(float degree)
{
	float	degree_to_percent = degree / PLAYER_FOV * 100;
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

static void	correction_left(t_wall_node *left_wall)
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
				detect_wall_hit
				))
	{
		right_wall->end_point.y = get_line_y(right_wall->info->ray_hit);
		right_wall->end_point.x = get_line_x(PLAYER_FOV);
	}
}

/*Correction head and last node.*/
/*From player's view, left_wall can be first node and right wall can be last node.*/
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
