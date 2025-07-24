#include "./my_algorithm.h"
#include "../player.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./wall_lkd_list/wall_lkd_list.h"

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

	a_b_vect.x = a->x - b->x;
	a_b_vect.y = a->y - b->y;
	c_b_vect.x = c->x - b->x;
	c_b_vect.y = c->y - b->y;

	a_b_atan = atan2(a_b_vect.y, a_b_vect.x);
	c_b_atan = atan2(c_b_vect.y, c_b_vect.x);
	result_atan = c_b_atan - a_b_atan;
	if (result_atan > Pie)
		result_atan -= 2*Pie;
	else if (result_atan < -Pie)
		result_atan += 2*Pie;
	degree = result_atan * (180 / Pie);
	return (degree);
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
	get_wall_start_end(info, &(node->wall_start_cord), &(node->wall_end_cord));
	node->start_degree =
		get_degree(&(info->end_point), &(info->ray_start), &(node->wall_start_cord));
	node->end_degree =
		get_degree(&(info->end_point), &(info->ray_start), &(node->wall_end_cord));
	node->texture = info->texture;
	node->info = info;
}

t_wall_node	*new_shoot_fov_ray(t_ray_info *info)
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
				/*그리고 표시되는 윈도우의 길이를 알아야 한다.*/
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
void	try_put_edge_to_map(t_wall_node *node)
{
	while (node)
	{
		put_pixel_to_img(
				&(mlx()->minimap),
				to_minimap_ratio(node->wall_start_cord).x,
				to_minimap_ratio(node->wall_start_cord).y,
				0x00ffff);
		put_pixel_to_img(
				&(mlx()->minimap),
				to_minimap_ratio(node->wall_end_cord).x,
				to_minimap_ratio(node->wall_end_cord).y,
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
	inverse = (SIZE_OF_BLOCK * WIN_HEIGHT) / vert_len;
	inverse = (float)WIN_HEIGHT/2 - inverse/2;
	return (inverse);
}

static inline int	get_line_x(float degree)
{
	float	degree_to_percent = degree / Player_FOV * 100;
	float	line_location = WIN_WIDTH * (degree_to_percent / 100);
	if (line_location == WIN_WIDTH)
		line_location = WIN_WIDTH - 1;
	return (line_location);
}

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

int	put_top_line(t_point ray, t_point y, void *dummy_3)
{
		if (
				(ray.x > 0 && ray.x < WIN_WIDTH) &&
				(ray.y > 0 && ray.y < WIN_HEIGHT)
				)
			put_pixel_to_img(&(mlx()->background), ray.x, ray.y, 0x0);
		return (0);
}

void	print_tex(t_img *img)
{
	printf("Texture: ");
	if (&(mlx()->xpm_north) == img)
		printf("NORTH\n");
	else if (&(mlx()->xpm_south) == img)
		printf("SOUTH\n");
	else if (&(mlx()->xpm_west) == img)
		printf("WEST\n");
	else if (&(mlx()->xpm_east) == img)
		printf("east\n");
}

void	print_list(t_wall_node *node)
{
	printf("====print_list====\n");
	while (node)
	{
		printf("ray_info: %p\n",node->info);
		printf("wall_start  : %f | %f\n", node->wall_start_cord.x, node->wall_start_cord.y);
		printf("start_degree: %f\n", node->start_degree);
		printf("wall_end  : %f | %f\n", node->wall_end_cord.x, node->wall_end_cord.y);
		printf("end_degree: %f\n", node->end_degree);
		printf("\n");
		node = node->next;
	}
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

void	try_put_vert_line(t_wall_node *node)
{
	t_mlx	*mlx_ptr = mlx();

	while (node)
	{
		put_line(&(mlx_ptr->background), node->start_point, 0x00ff00);
		put_line(&(mlx_ptr->background), node->end_point, 0xffff00);
		shoot_ray(node->start_point, node->end_point, NULL, put_top_line);
		node = node->next;
	}
}

void	first_last_correction(t_wall_node *node)
{
	node->info->degree = 0;
	node->info->ray_dest = rotate_point(
			node->info->ray_start, node->info->end_point,
			node->info->degree
			);
	if (shoot_ray(node->info->ray_start, node->info->ray_dest, node->info, detect_wall_hit))
	{
		{
			node->start_point.y = get_line_y(node->info->ray_hit);
			node->start_point.x = get_line_x(0);
		}
	}

	node = wall_find_first_node(node);
	if(wall_count_nodes(node) == 1)
		return ;
	node = wall_find_lst_node(node);

	node->info->degree = (float)Player_FOV - RAY_RES;
	node->info->ray_dest = rotate_point(
			node->info->ray_start, node->info->end_point,
			node->info->degree
			);
	if (shoot_ray(node->info->ray_start, node->info->ray_dest, node->info, detect_wall_hit))
	{
		{
			node->end_point.y = get_line_y(node->info->ray_hit);
			node->end_point.x = get_line_x(Player_FOV);
		}
	}
}

int	put_texture(t_point ray, t_point y, void *param)
{
	float	lower_point = ((float)WIN_HEIGHT / 2) + (((float)WIN_HEIGHT / 2) - ray.y);

	if ((ray.x > 0 && ray.x < WIN_WIDTH) &&
		(ray.y > 0 && ray.y < WIN_HEIGHT))
		put_pixel_to_img(&(mlx()->background), ray.x, ray.y, 0x00ff00);
	/*세로 채우기.*/
	t_wall_node	*node = param;
	t_point		start_ray = ray;
	t_point		pixel = ray;
	if (node->prev == NULL)
		pixel.x = node->texture->xpm_width * ((ray.x - (node->end_point.x - node->wall_width)) / node->wall_width);
	else
		pixel.x = node->texture->xpm_width * ((ray.x - node->start_point.x) / node->wall_width);
	while (ray.y < lower_point)
	{
		pixel.y =
		node->texture->xpm_height *
		(
		(ray.y - start_ray.y) // 진행거리. 이거 틀릴 일 없음.
		/
		(((float)WIN_HEIGHT / 2) + ((float)WIN_HEIGHT / 2 - start_ray.y) - start_ray.y) // 비율 구하기.
		);
		if ((ray.x > 0 && ray.x < WIN_WIDTH) &&
			(ray.y > 0 && ray.y < WIN_HEIGHT))
		{
			put_pixel_to_img(&(mlx()->background), ray.x, ray.y,
					get_xpm_pixel_color(*(node->texture), pixel)
					);
		}
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

void	sort_wall_list(t_wall_node *node);

void	make_wall_linked_list(void)
{
	t_ray_info	info;
	t_wall_node	*node;

	node = new_shoot_fov_ray(&info);
	/*미니맵에 ray의 충돌판정이 된 면을 표시합니다.*/
	try_put_edge_to_map(node);
	/*가상 맵에서의 벽 좌표를 화면상 좌표로 계산합니다.*/
	calculate_point_location(node);
	/*화면상 잘리는 처음 노드와 마지막 노드를 보정합니다.*/
	first_last_correction(node);
	/*리스트를 정렬합니다.*/
	sort_wall_list(node);
	node = wall_find_first_node(node);
	/*텍스쳐를 입혀봅니다.*/
	try_put_texture(node);
	/*linked_list를 삭제합니다.*/
	wall_destroy_list(node);
}
