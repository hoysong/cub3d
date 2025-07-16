#include "./my_algorithm.h"
#include "../player.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* ray의 벽 출돌 이후.
 * 면의 시작선과 끝선을 알도록 하면 너비를 구할 수 있음.
 * 	만약 다음과 같이 시작선, 끝선이 구해졌다고 가정.
 *	-1 1 = 2;
 *	-2 2 = 4;
 *	3 7 = 4;
 *
 *	이를 다음과 같이 계산하면 너비를 구해낼 수 있음.
 *	-1 + 1*-1  = abs(-2);
 *	-2 + 2*-1 = abs(-4);
 *	3 + 7*-1  = abs(-4);
 *	-7 + (-2)*-1 = abs(-5);
 * 원리는 위와 같다.
 * 그렇다면, 멀리있는 벽을 가까운 벽이 덮어버리는 상황이 있을 수 있다.
 * 이는 어떻게 해결해야 하는가?
 * 그냥 linkedlist로 만들어버리면 모든 것이 해결이 된다.
 * rayhit거리가 가장 긴 정보를 가진 node부터 그려버리면 된다.
 * 이렇게 진짜 면을 casting한다는 생각으로 접근하면 많은 문제가 해결이 된다.
 */

t_wall_node	*wall_init_node(void)
{
	t_wall_node	*node;

	node = malloc(sizeof(t_wall_node));
	if (node == NULL)
		exit(1);
	node->next = NULL;
	node->prev = NULL;
	node->texture = NULL;

	node->wall_start.x = 0;
	node->wall_start.y = 0;

	node->wall_end.x = 0;
	node->wall_end.y = 0;

	node->start_degree = 0;
	node->end_degree = 0;
	return (node);
}

t_wall_node	*wall_find_first_node(t_wall_node *node)
{
	while(node->prev != NULL)
		node = node->prev;
	return (node);
}

/*returns last node.*/
t_wall_node	*wall_find_lst_node(t_wall_node *node)
{
	while(node->next != NULL)
		node = node->next;
	return (node);
}

/*this will init last node of list and return it.*/
t_wall_node	*wall_init_last_node(t_wall_node *node)
{
	node = wall_find_lst_node(node);
	node->next = wall_init_node();
	node->next->prev = node;
	return (node->next);
}

void	wall_destroy_list(t_wall_node *node)
{
	node = wall_find_lst_node(node);
	while (node->prev != NULL)
	{
		node = node->prev;
		free(node->next);
	}
	free(node);
}

/* 
 * ===============
 * | logic_start |
 * ===============
 */

static inline float	zero_start_degree(float degree)
{
	degree += (float)Player_FOV / 2;
	return (degree);
}

static inline float	get_vertlen(t_point a, t_point b, t_point c)
{
	float	m;
	m = (b.y - a.y) / (b.x - a.x);

	float result;
	result = my_abs(m*c.x - c.y + (a.y - (m*a.x))) / sqrt(pow(m, 2) + 1);
	return (result);
}

static inline float	get_vertical_length(t_ray_info *info)
{
	float	vert_len;
	float	inverse;

	vert_len = get_vertlen(
			player()->cord,
			rotate_point(player()->cord, player()->view_point, 90),
			info->ray_hit);

	/*to inverse*/
	inverse = (SIZE_OF_BLOCK * WIN_HEIGHT) / vert_len;
	if (inverse > WIN_HEIGHT || inverse < 0)
		inverse = WIN_HEIGHT;
	inverse = (float)WIN_HEIGHT/2 - inverse/2;
	return (inverse);
}

static inline int	get_line_location(float degree)
{
	float	zero_degree = zero_start_degree(degree);
	zero_degree = degree;
	float	degree_to_percent = zero_degree / Player_FOV * 100;
	float	line_location = WIN_WIDTH * (degree_to_percent / 100);
	if (line_location == WIN_WIDTH)
		line_location = WIN_WIDTH - 1;
	return (line_location);
}

extern void	try_put_plane(float start_y, float line_x, int degree);
extern void	try_put_plane_2(float degree, float line_len, t_ray_info *info);

static void	ray_casting(t_mlx *mlx, t_ray_info *info)
{
	float	line_len;
	float	line_start;
	float	line_end;
	int		line_location;

	line_len = get_vertical_length(info);
	line_start = (float)WIN_HEIGHT/2 - line_len/2;
	line_end = (float)WIN_HEIGHT/2 + line_len/2;
	line_location = get_line_location(info->degree);
	/*try_put*/
//	try_put_plane(line_start, line_location, (int)degree);
//	try_put_plane_2(degree, line_len, info);
	/*put_line*/
	while (line_start < line_end)
	{
		printf("%d\n", line_location);
		printf("%f\n", line_start);
		put_pixel_to_img(&(mlx->background), line_location, line_start, 0x00ff00);
		++line_start;
	}
}

/*fov범위만큼 벽들에 ray를 쏠 것이다.
 * 서로 다른 면이 감지될 경우 node에 면의 정보(시작과 끝선)을 추가할 것이다.
 * 	서로 다른 면의 판정은 어떻게 해야 하는가?
 * 	1. 주소가 바뀐 경우: 당연히 해야 함.
 * 	2. 주소는 그대로지만 텍스쳐가 바뀐 경우.
 * 만약 북쪽을 바라보고 있다면 실제로는 남쪽벽을 바라볼 것이다.
 * 그리고 벽의 인덱스 상 위치가 1,1 이라면?
 * 남쪽벽의 시작과 끝의 좌표는 어떻게 되나?
 * 	|시작|
 * 		x = x*sizeof_wall;
 * 		y = y*sizeof_wall + sizeof_wall;
 * 	| 끝 |
 * 		x = x*sizeof_wall + sizeof_wall;
 * 		y = y*sizeof_wall + sizeof_wall;
 * 위의 점들을 플레이어로 ray를 쏠 것이다.
 * */

void	init_info(t_ray_info *info)
{
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
	float	a_num;
	float	b_num;
	float	c_num;
	float	d_num;
	float	arc_cos;

	a_num = (a->x - b->x)*(c->x - b->x);
	b_num = (a->y - b->y)*(c->y - b->y);
	c_num = pow((a->x - b->x), 2) + pow((a->y - b->y), 2);
	d_num = pow((c->x - b->x), 2) + pow((c->y - b->y), 2);
	arc_cos = acos(
			(a_num + b_num) / (sqrt(c_num) * sqrt(d_num))
			);
	return (arc_cos * (180 / Pie));
}

void	get_wall_start_end(t_ray_info *info, t_point *start, t_point *end)
{
	t_mlx	*mlx_ptr = mlx();

	if (&(mlx_ptr->xpm_north) == info->texture)
	{
		printf("1\n");
		start->x = info->wall_x * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
		start->y = info->wall_y * SIZE_OF_BLOCK;
		end->x = info->wall_x * SIZE_OF_BLOCK;
		end->y = info->wall_y * SIZE_OF_BLOCK;
	}
	else if (&(mlx_ptr->xpm_south) == info->texture)
	{
		printf("2\n");
		start->x = info->wall_x * SIZE_OF_BLOCK;
		start->y = info->wall_y * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
		end->x = info->wall_x * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
		end->y = info->wall_y * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
	}
	else if (&(mlx_ptr->xpm_west) == info->texture)
	{
		printf("3\n");
		start->x = info->wall_x * SIZE_OF_BLOCK;
		start->y = info->wall_y * SIZE_OF_BLOCK;
		end->x = info->wall_x * SIZE_OF_BLOCK;
		end->y = info->wall_y * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
	}
	else if (&(mlx_ptr->xpm_east) == info->texture)
	{
		printf("4\n");
		start->x = info->wall_x * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
		start->y = info->wall_y * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
		end->x = info->wall_x * SIZE_OF_BLOCK + SIZE_OF_BLOCK;
		end->y = info->wall_y * SIZE_OF_BLOCK;
	}
}

void	add_new_wall_node(t_wall_node *node, t_ray_info *info)
{
	node = wall_init_last_node(node);
	/*텍스쳐를 먼저 확인하기.
	 * 텍스쳐에 따른 좌표값을 넣어줘야 함.*/
	get_wall_start_end(info, &(node->wall_start), &(node->wall_end));
	node->start_degree = get_degree(&(info->end_point), &(info->ray_start), &(node->wall_start));
	node->end_degree = get_degree(&(info->end_point), &(info->ray_start), &(node->wall_end));
	node->texture = info->texture;
	printf("start deg: %f\n", node->start_degree);
	printf("end   deg: %f\n", node->end_degree);
}

t_wall_node	*new_shoot_fov_ray(void)
{
	/* while문을 돌리면서 list를 만들기.
	 * 	노드 하나하나를 생성하면서 진행됨.
	 * 	1. 노드가 생성될 수 있는 조건.
	 * 		현재의 ray가 도달한 주소가 다르거나 다른 텍스쳐인 경우.
	 * 	2. 노드가 만들어지고 하는 일.
	 * 		도착한 곳의 texture를 판별하여 어디가 선의 시작이고 어디가 선의 끝인지 알아냄.
	 * 	3. 그렇다면 선에 대한 정보는 어떤 것들이 필요한가.
	 * 		+ 선의 시작위치
	 * 			가로(x)의 어디에 위치할 것인지.
	 * 			세로(y)의 어디서 시작하는지.
	 * 		+ 선의 가로 중 어디에 위치할지를 정하기 위해서는 각도가 필요하다.
	 * 			그렇다면 3점 사이의 각도를 구하면 될 듯 하다.
	 * 			실제로는 info.end_point를 info.ray_start를 기준으로 회전시키는 것이다.
	 * 			end_point, start, wall_start 순으로 연결시키면
	 * 			start 쪽의 각도를 알아낼 수 있다.
	 * 실제로 그리는 것은 위 과정 이후에 하면 되니 간단하게 된다.
	 * 그리는 과정은 다음과 같이 하면된다.
	 * 	1. 가장 먼 거리의 벽을 구한다.
	 * 		이는 ray_start와 ray_hit간의 거리를 구하기만 하면 되니 편하다.
	 * 	2. 시작과 끝을 연결한다.
	 * 		x,y에 위치한 면의 시작과 x2,y2에 위치한 면의 끝을 이어준다.
	 * 	3. 연결 과정에서 텍스쳐를 입힌다.
	 * 		텍스쳐는 면 시작과 끝의 너비를 구해서 입력하면 된다.
	 * 		아마 x2 - x로 계산하면 간단하게 너비를 구할 수 있다.
	 * 		텍스쳐는 비율로 어디의 선을 그어내면 될지 구하면 될 듯 하다.
	 */
	t_ray_info	info;
	t_ray_info	prev_info;
	t_wall_node	*node;
	node = wall_init_node();

	init_info(&info);
	prev_info = info;
	printf("======================================================\n");
	while (info.degree <= Player_FOV)
	{
		info.ray_dest = rotate_point(
				info.ray_start, info.end_point,
				info.degree
				);
		if (shoot_ray(info.ray_start, info.ray_dest, &info, detect_wall_hit))
		{
			/*새로운 벽이나 새로운 텍스쳐에 도달했는가?*/
			if (prev_info.texture != info.texture ||
				prev_info.wall_addr != info.wall_addr)
			{
				printf("deg: %f\n", info.degree);
				/*맞다면 노드를 생성한다.*/
				add_new_wall_node(node, &info);
				node = node->next;
				printf("\n");
			}
		}
		prev_info = info;
		info.degree += RAY_RES;
	}
	/*처음 노드가 비어있어서 첫 노드만 없애는 작업*/
	node = wall_find_first_node(node);
	node = node->next;
	free(node->prev);
	node->prev = NULL;
	return (node);
}

/*찍혀야 하는 면의 모서리에 점을 찍어봅니다.*/
void	try_put_edge(t_wall_node *node)
{
//	node = wall_find_first_node(node);
	while (node)
	{
		put_pixel_to_img(
				&(mlx()->minimap),
				to_minimap_ratio(node->wall_start).x,
				to_minimap_ratio(node->wall_start).y,
				0x00ffff);
		put_pixel_to_img(
				&(mlx()->minimap),
				to_minimap_ratio(node->wall_end).x,
				to_minimap_ratio(node->wall_end).y,
				0x00ffff);
		node = node->next;
	}
}

static inline float	get_line_y(t_point point)
{
	float	vert_len;
	float	inverse;

	vert_len = get_vertlen(
			player()->cord,
			rotate_point(player()->cord, player()->view_point, 90),
			point);

	/*to inverse*/
	inverse = (SIZE_OF_BLOCK * WIN_HEIGHT) / vert_len;
//	if (inverse > WIN_HEIGHT || inverse < 0)
//		inverse = WIN_HEIGHT;
	inverse = (float)WIN_HEIGHT/2 - inverse/2;
	return (inverse);
}

static inline int	get_line_x(float degree)
{
	float	zero_degree = zero_start_degree(degree);
	zero_degree = degree;
	float	degree_to_percent = zero_degree / Player_FOV * 100;
	float	line_location = WIN_WIDTH * (degree_to_percent / 100);
//	printf("GET_X\n");
//	printf("degree            : %f\n", zero_degree);
//	printf("degree_to_percent : %f\n", degree_to_percent);
//	printf("line_location     : %f\n", line_location);
//	printf("%f\n", zero_degree);
	if (line_location == WIN_WIDTH)
		line_location = WIN_WIDTH - 1;
	return (line_location);
}

//	put_pixel_to_img(&(mlx->background), line_location, line_start, color_num);
static void	put_line(t_img *img_ptr, t_point point, int color)
{
	float	line_end;
	line_end = WIN_HEIGHT - point.y;
	while (point.y < line_end)
	{
		if (
				(point.x > 0 && point.x < WIN_WIDTH) &&
				(point.y > 0 && point.y < WIN_HEIGHT)
				)
			put_pixel_to_img(img_ptr, point.x, point.y, color);
		++point.y;
	}
}

int	put_texture(t_point ray, t_point y, void *dummy_3)
{
		if (
				(ray.x > 0 && ray.x < WIN_WIDTH) &&
				(ray.y > 0 && ray.y < WIN_HEIGHT)
				)
			put_pixel_to_img(&(mlx()->background), ray.x, ray.y, 0x0);
}

void	try_put_vertline(t_wall_node *node)
{
	t_mlx	*mlx_ptr = mlx();
	t_point	tex_start;
	t_point	tex_end;

	while (node)
	{
		/*시작면의 시작을 구함.*/
		tex_start.y = get_line_y(node->wall_start);
		tex_start.x = get_line_x(node->start_degree);
		put_line(&(mlx_ptr->background), tex_start, 0x00ff00);
		/*끝면의 시작을 구함.*/
		tex_end.y = get_line_y(node->wall_end);
		tex_end.x = get_line_x(node->end_degree);
		put_line(&(mlx_ptr->background), tex_end, 0xffff00);
		printf("SHOOTING RAY\n");
		printf("from: %f | %f\n", tex_start.x, tex_start.y);
		printf("to  : %f | %f\n", tex_end.x, tex_end.y);
		shoot_ray(tex_start, tex_end, NULL, put_texture);

		node = node->next;
	}
}

/*이름은 나중에 draw_walls라고 하는게 좋을 듯 싶다.
 * draw_walls()
 * put_texture()
 */
void	make_wall_linked_list(void)
{
	t_wall_node	*node;

	node = new_shoot_fov_ray();
	printf("BEFORE - : %f\n", node->start_degree);
	node->start_degree *= -1;
	try_put_edge(node);
	try_put_vertline(node);
	wall_destroy_list(node);
}
