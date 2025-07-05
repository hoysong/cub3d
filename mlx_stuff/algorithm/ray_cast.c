#include "../player.h"
#include "../mlx_hdler.h"
#include <math.h>
#include <stdio.h>

/*test*/
static void	print_info(t_ray_info *info)
{
//	printf("info %p\n", info);
//	printf("info->wall_ptr    : %p\n", info->wall_ptr);
//	printf("info->texture     : %p\n", info->texture);
//	printf("info->degree      : %f\n", info->degree);
//	printf("info->ray_start.x : %f\n", info->ray_start.x);
//	printf("info->ray_start.y : %f\n", info->ray_start.y);
//	printf("info->end_point.x : %f\n", info->end_point.x);
//	printf("info->end_point.y : %f\n", info->end_point.y);
//	printf("info->ray_dest.x  : %f\n", info->ray_dest.x);
//	printf("info->ray_dest.y  : %f\n", info->ray_dest.y);
//	printf("\n");
}

static inline float	zero_start_degree(float degree)
{
	degree += (float)Player_FOV / 2;
	return (degree);
}

static inline float	get_vertical_length(float degree, t_ray_info *info)
{
	float	cos_degree;

	if (degree < 0)
		cos_degree = my_abs(degree);
	else
		cos_degree = degree;

	float	hit_len;
	float	perp_len;

	hit_len = get_length(player()->cord, info->ray_hit);
	perp_len = cos(cos_degree * (Pie/180)) * hit_len;
	/*to inverse*/
	float	inverse;

	inverse = (SIZE_OF_BLOCK * WIN_HEIGHT) / perp_len;
//	if (inverse > WIN_HEIGHT)
//		inverse = WIN_HEIGHT;
	return (inverse);
}

static inline float	get_line_location(float degree)
{
	float	zero_degree = zero_start_degree(degree);
	float	degree_to_percent = zero_degree / Player_FOV * 100;
	float	line_location = WIN_WIDTH * (degree_to_percent / 100);

	if (line_location == WIN_WIDTH)
		line_location = WIN_WIDTH - 1;
	return (line_location);
}

extern void	put_texture(t_point prev, t_point current, t_ray_info *info, t_ray_info *prev_info);

static void	try_put_plane(t_point line_start, t_ray_info *info, t_ray_info *prev_info)
{
	static t_point	prev_line_start;
	float	degree;

	/*0일 경우 좌측각으로 ray를 다시 쏴본다.*/
	/*함수로 따로 찢을 수 있을거같다.*/
	/*물론 마지막에 잘리는 X 또한 같은 작업을 해줘야 한다.*/
	if (prev_line_start.y == 0)
	{
		*prev_info = *info;
		degree = prev_info->degree;
		while (1)
		{
			prev_info->ray_dest = rotate_point(
					prev_info->ray_start,
					prev_info->end_point,
					degree
					);
			shoot_ray(prev_info->ray_start, prev_info->ray_dest, prev_info, detect_wall_hit);
			/*ray가 히트한 곳이 현재 벽이 아니라면, 멈춘다.*/
			if (prev_info->wall_ptr != info->wall_ptr || prev_info->texture != info->texture)
			{
				degree += RAY_RES;
				prev_info->ray_dest = rotate_point(
						prev_info->ray_start,
						prev_info->end_point,
						degree
						);
				shoot_ray(prev_info->ray_start, prev_info->ray_dest, prev_info, detect_wall_hit);
				break ;
			}
			degree -= RAY_RES;
		}
		prev_line_start.y = get_vertical_length(degree, prev_info);
		prev_line_start.y = (float)WIN_HEIGHT/2 - prev_line_start.y/2;
		prev_line_start.x = get_line_location(degree);
		printf("len %f\n", prev_line_start.y);
		return ;
	}
	/*X같은 경우는 마지막 각도일 경우에 실행하면된다.*/
	/*해당 경우에는 다시 static을 0으로 초기화를 시켜야 한다.*/
	if (info->degree == (float)Player_FOV / 2)
	{
		degree = info->degree;
		while (1)
		{
			info->ray_dest = rotate_point(
					info->ray_start,
					info->end_point,
					degree
					);
			shoot_ray(info->ray_start, info->ray_dest, info, detect_wall_hit);
			/*ray가 히트한 곳이 현재 벽이 아니라면, 멈춘다.*/
			if (prev_info->wall_ptr != info->wall_ptr || prev_info->texture != info->texture)
			{
				degree -= RAY_RES;
				shoot_ray(info->ray_start, info->ray_dest, info, detect_wall_hit);
				break ;
			}
			degree += RAY_RES;
		}
		line_start.y = get_vertical_length(prev_info->degree, prev_info);
		line_start.y = (float)WIN_HEIGHT/2 - line_start.y/2;
		line_start.x = get_line_location(prev_info->degree);
	}
	put_texture(prev_line_start, line_start, info, prev_info);
	prev_line_start = line_start;
	if (info->degree == (float)Player_FOV / 2)
	{
		prev_line_start.y = 0;
	}
}

static void	ray_casting(t_mlx *mlx, t_ray_info *info, t_ray_info *prev_info)
{
	float	line_len;
	float	line_start;
	float	line_end;
	int		line_x;

	line_len = get_vertical_length(info->degree, info);
	line_start = (float)WIN_HEIGHT/2 - line_len/2;
	line_end = (float)WIN_HEIGHT/2 + line_len/2;
	line_x = get_line_location(info->degree);
	/*try_put*/
	t_point	line_start_location;
	line_start_location.y = line_start;
	line_start_location.x = line_x;
	try_put_plane(line_start_location, info, prev_info);
	/*put_line*/
	int	color;
	if (info->texture == &(mlx->xpm_north))
		color = 0xaa0000;
	else if (info->texture == &(mlx->xpm_south))
		color = 0xaaaa00;
	else if (info->texture == &(mlx->xpm_west))
		color = 0xdddddd;
	else if (info->texture == &(mlx->xpm_east))
		color = 0x0;
	while (line_start < line_end)
	{
		if (line_start > 0 && line_start < WIN_HEIGHT)
			put_pixel_to_img(&(mlx->background), line_x, line_start, color);
		++line_start;
	}
}

extern void	draw_fov(t_player *player);

void	shoot_fov_ray(void)
{
	static int	loop_chk_test;
	t_ray_info	info;
	t_ray_info	prev_info;

	info.ray_start = player()->cord;
	info.end_point = player()->view_point;
	info.degree = ((float)Player_FOV / 2) * -1;

	prev_info.wall_ptr = NULL;
	prev_info.texture = NULL;
	prev_info.degree = 123;
	while (info.degree <= (float)Player_FOV / 2)
	{
		loop_chk_test++;
		info.ray_dest = rotate_point(info.ray_start, info.end_point, info.degree);
		if (shoot_ray(info.ray_start, info.ray_dest, &(info), detect_wall_hit))
		{
			if (prev_info.wall_ptr != info.wall_ptr
				|| prev_info.texture != info.texture)
			{
				ray_casting(mlx(), &(info), &(prev_info));
			}
			else if (info.degree == (float)Player_FOV / 2)
				ray_casting(mlx(), &(info), &(prev_info));
			prev_info = info;
		}
		info.degree += RAY_RES;
	}
	draw_fov(player());
	loop_chk_test = 0;
}
