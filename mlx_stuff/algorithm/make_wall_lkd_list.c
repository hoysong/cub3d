#include "./my_algorithm.h"
#include "../player.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./wall_lkd_list/wall_lkd_list.h"

static inline float	get_line_y(t_point point);

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

void	init_info(t_ray_info *info)
{
	info->degree = 0;
	info->wall_x = 0;
	info->wall_y = 0;
	info->screen_left = 0;
	info->screen_right = 0;
	info->virtual_screen_width = 0;
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
	float	x_num;

	a_num = (a->x - b->x)*(c->x - b->x);
	b_num = (a->y - b->y)*(c->y - b->y);
	c_num = pow((a->x - b->x), 2) + pow((a->y - b->y), 2);
	d_num = pow((c->x - b->x), 2) + pow((c->y - b->y), 2);
	x_num = (a_num + b_num) / (sqrt(c_num) * sqrt(d_num));
	/* 기준각과 텍스터 시작 좌표가 기막히게 비슷할 경우 문제가 발생한다.
	 * 해당 문제를 해결하기 위한 방법.*/
	if (x_num > 1)
		x_num = 1;
	else if (x_num < -1)
		x_num = -1;
	arc_cos = acos(x_num);
	printf("acos: %f\n",arc_cos);
	printf("%f\n", (a_num + b_num));
	printf("------div----- = %f\n", (a_num + b_num) / (sqrt(c_num) * sqrt(d_num)));
	printf("%f\n\n", (sqrt(c_num) * sqrt(d_num)));
	return (arc_cos * (180 / Pie));
}

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

void	add_new_wall_node(t_wall_node *node, t_ray_info *info)
{
	node = wall_init_last_node(node);
	/*텍스쳐를 먼저 확인하기.
	 * 텍스쳐에 따른 좌표값을 넣어줘야 함.*/
	get_wall_start_end(info, &(node->wall_start), &(node->wall_end));
	printf("start ");
	node->start_degree = get_degree(&(info->end_point), &(info->ray_start), &(node->wall_start));
	printf("end   ");
	node->end_degree = get_degree(&(info->end_point), &(info->ray_start), &(node->wall_end));
	node->texture = info->texture;
	printf("start deg: %f\n", node->start_degree);
	printf("end   deg: %f\n", node->end_degree);
	node->info = info;
}

void	get_virtual_screen_width(t_ray_info *info)
{
	float	under_len;

	/*좌측 스크린 사이즈 구하기.*/
	shoot_ray(info->ray_start, info->ray_dest, info, detect_wall_hit);
	under_len = get_vertlen(
			player()->cord,
			rotate_point(player()->cord, player()->view_point, 90),
			info->ray_hit);
	info->screen_left = tan(Player_FOV / 2 * (Pie/180)) * under_len;

	/*우측 스크린 사이즈 구하기.*/
	info->degree = Player_FOV;

	info->ray_dest = rotate_point(
			info->ray_start, info->end_point,
			info->degree
			);

	shoot_ray(info->ray_start, info->ray_dest, info, detect_wall_hit);
	under_len = get_vertlen(
			player()->cord,
			rotate_point(player()->cord, player()->view_point, 90),
			info->ray_hit);
	info->screen_right = tan(Player_FOV / 2 * (Pie/180)) * under_len;
	info->virtual_screen_width = info->screen_left + info->screen_right;
	info->degree = 0;
	if (info->screen_left > info->screen_right)
	{
		info->screen_right = info->screen_left;
	}
	else if (info->screen_left < info->screen_right)
	{
		info->screen_left = info->screen_right;
	}
	info->screen_left = 500;
	info->screen_right = 500;
	info->virtual_screen_width = info->screen_left*2;
//	printf("virtual_left : %f\n", screen_left);
//	printf("virtual_right: %f\n", screen_right);
//	printf("virtual_width: %f\n", info->virtual_screen_width);
}

t_wall_node	*new_shoot_fov_ray(t_ray_info *info)
{
	t_ray_info	prev_info;
	t_wall_node	*node;
	node = wall_init_node();

	init_info(info);
	get_virtual_screen_width(info);
	prev_info = *info;

	printf("======================================================\n");
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
				printf("deg: %f\n", info->degree);
				/*맞다면 노드를 생성한다.*/
				/*그리고 표시되는 윈도우의 길이를 알아야 한다.*/
				add_new_wall_node(node, info);
				node = node->next;
				printf("\n");
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
void	try_put_edge_to_map(t_wall_node *node)
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
	printf("GET_X\n");
	printf("degree            : %f\n", zero_degree);
	printf("degree_to_percent : %f\n", degree_to_percent);
	printf("line_location     : %f\n\n", line_location);
	if (line_location == WIN_WIDTH)
		line_location = WIN_WIDTH - 1;
	return (line_location);
}

static void	put_line(t_img *img_ptr, t_point point, int color)
{
	float	line_end;
	line_end = WIN_HEIGHT - point.y;
	printf("on put_line %f | %f\n", point.x, point.y);
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
		return (0);
}

float	new_get_line_end(t_wall_node *node, t_point *start, t_point *end)
{
	float	vert_len;
	float	inverse;

	/*가상의 삼각형 밑변을 구함.*/
	vert_len = get_vertlen(
			player()->cord,
			rotate_point(player()->cord, player()->view_point, 90),
			node->wall_end);

	/*실제 화면의 길이로 변환.*/
	inverse = (SIZE_OF_BLOCK * WIN_HEIGHT) / vert_len;
	/*실제 화면에서 시작하는 픽셀y 위치를 구함.*/
	inverse = (float)WIN_HEIGHT/2 - inverse/2;
	/*탄젠트를 통해 높이를 구하는 공식이 필요함.*/
	/*fov / 2 - 벽각도.*/
	float	height;
	if (node->end_degree < Player_FOV / 2)
	{
		printf("각도작음\n");
		/*만약 FOV/2보다 큰 곳에 수직선이 위치하면 해당 각도는 fov/2를 빼줘야 함.*/
		height = tan((Player_FOV / 2 - node->end_degree) * (Pie / 180)) * vert_len;
		printf("vertlen: %f\n",vert_len);
		printf("node->degree %f\n", node->end_degree);
		printf("tan: %f\n", tan((node->end_degree - Player_FOV / 2) * (Pie / 180)));
	}
	else
		/*만약 FOV/2보다 작은 곳에 수직선이 위치하면 해당 각도는 fov/2에서 빼야 함.*/
		height = tan((node->end_degree - Player_FOV / 2) * (Pie / 180)) * vert_len;
	/*그럼 아주 수직인 경우에는 문제가 없나?*/
	/*나중에 생각해보기.*/
	/*일단 높이는 구한 상황.*/
	/*이제는 가상 화면에서의 거리를 구해야 함.*/
	float	virtual_screen_x;

	if (node->end_degree < Player_FOV / 2)
		/*각도가 fov/2보다 작다면 왼쪽에서 뺀다.*/
		virtual_screen_x = node->info->screen_left - height;
	else	
		/*각도가 fov/2보다 크다면 왼쪽을 더한다.*/
		virtual_screen_x = node->info->screen_left + height;

	float	percent = virtual_screen_x / node->info->virtual_screen_width * 100;
	float	x_location = WIN_WIDTH * (percent / 100);

	printf("virtual_width: %f\n", node->info->virtual_screen_width);
	printf("tan_height:    %f\n", height);
	printf("virtual_screen_x: %f\n", virtual_screen_x);
	printf("x_location: %f\n", x_location);
	printf("\n");

	return (x_location);
}

float	new_get_line_start(t_wall_node *node, t_point *start, t_point *end)
{
	float	vert_len;
	float	inverse;

	/*가상의 삼각형 밑변을 구함.*/
	vert_len = get_vertlen(
			player()->cord,
			rotate_point(player()->cord, player()->view_point, 90),
			node->wall_start);

	/*실제 화면의 길이로 변환.*/
	inverse = (SIZE_OF_BLOCK * WIN_HEIGHT) / vert_len;
	/*실제 화면에서 시작하는 픽셀y 위치를 구함.*/
	inverse = (float)WIN_HEIGHT/2 - inverse/2;
	/*탄젠트를 통해 높이를 구하는 공식이 필요함.*/
	/*fov / 2 - 벽각도.*/
	float	height;
	if (node->start_degree < Player_FOV / 2)
	{
		printf("각도작음\n");
		/*만약 FOV/2보다 큰 곳에 수직선이 위치하면 해당 각도는 fov/2를 빼줘야 함.*/
		height = tan((Player_FOV / 2 - node->start_degree) * (Pie / 180)) * vert_len;
		printf("vertlen: %f\n",vert_len);
		printf("node->degree %f\n", node->start_degree);
		printf("tan: %f\n", tan((node->start_degree - Player_FOV / 2) * (Pie / 180)));
	}
	else
		/*만약 FOV/2보다 작은 곳에 수직선이 위치하면 해당 각도는 fov/2에서 빼야 함.*/
		height = tan((node->start_degree - Player_FOV / 2) * (Pie / 180)) * vert_len;
	/*그럼 아주 수직인 경우에는 문제가 없나?*/
	/*나중에 생각해보기.*/
	/*일단 높이는 구한 상황.*/
	/*이제는 가상 화면에서의 거리를 구해야 함.*/
	float	virtual_screen_x;

	if (node->start_degree < Player_FOV / 2)
		/*각도가 fov/2보다 작다면 왼쪽에서 뺀다.*/
		virtual_screen_x = node->info->screen_left - height;
	else	
		/*각도가 fov/2보다 크다면 왼쪽을 더한다.*/
		virtual_screen_x = node->info->screen_left + height;

	float	percent = virtual_screen_x / node->info->virtual_screen_width * 100;
	float	x_location = WIN_WIDTH * (percent / 100);

	printf("virtual_width: %f\n", node->info->virtual_screen_width);
	printf("tan_height:    %f\n", height);
	printf("virtual_screen_x: %f\n", virtual_screen_x);
	printf("x_location: %f\n", x_location);
	printf("\n");

	return (x_location);
}

//void	try_put_vertline(t_wall_node *node)
//{
//	t_mlx	*mlx_ptr = mlx();
//	t_point	tex_start;
//	t_point	tex_end;
//
//	printf("virtual_left: %f\n", node->info->screen_left);
//	printf("virtual_right: %f\n", node->info->screen_right);
//	while (node)
//	{
//		tex_start.x = new_get_line_start(node, &tex_start, &tex_start);
////		tex_start.y = get_line_y(node->wall_start);
////		tex_start.x = get_line_x(node->start_degree);
////		put_line(&(mlx_ptr->background), tex_start, 0x00ff00);
////
////		tex_end.y = get_line_y(node->wall_end);
////		tex_end.x = get_line_x(node->end_degree);
////		put_line(&(mlx_ptr->background), tex_end, 0xffff00);
////
////		shoot_ray(tex_start, tex_end, NULL, put_texture);
//
//		node = node->next;
//	}
//}

void	try_put_vertline(t_wall_node *node)
{
	t_mlx	*mlx_ptr = mlx();
	t_point	tex_start;
	t_point	tex_end;

	printf("virtual_left: %f\n", node->info->screen_left);
	printf("virtual_right: %f\n", node->info->screen_right);
	while (node)
	{
		tex_start.y = get_line_y(node->wall_start);
		tex_start.x = new_get_line_start(node, &tex_start, &tex_start);
		put_line(&(mlx_ptr->background), tex_start, 0x00ff00);

		tex_end.y = get_line_y(node->wall_end);
		tex_end.x = new_get_line_end(node, &tex_start, &tex_start);
		put_line(&(mlx_ptr->background), tex_end, 0xffff00);

		shoot_ray(tex_start, tex_end, NULL, put_texture);

		node = node->next;
	}
}

void	print_list(t_wall_node *node)
{
	printf("====print_list====\n");
	while (node)
	{
		printf("ray_info: %p\n",node->info);
		printf("wall_start  : %f | %f\n", node->wall_start.x, node->wall_start.y);
		printf("start_degree: %f\n", node->start_degree);
		printf("wall_end  : %f | %f\n", node->wall_end.x, node->wall_end.y);
		printf("end_degree: %f\n", node->end_degree);
		printf("\n");
		node = node->next;
	}
}

/* 이름은 나중에 draw_walls라고 하는게 좋을 듯 싶다.
 * draw_walls()
 * put_texture()
 */

void	make_wall_linked_list(void)
{
	t_ray_info	info;
	t_wall_node	*node;

	node = new_shoot_fov_ray(&info);
//	printf("BEFORE - : %f\n", node->start_degree);
	print_list(node);
	node->start_degree *= -1;
	try_put_edge_to_map(node);
	try_put_vertline(node);
	wall_destroy_list(node);
}
