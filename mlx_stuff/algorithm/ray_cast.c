#include "../player.h"
#include "../mlx_hdler.h"
#include <math.h>
#include <stdio.h>

int	color_num = 0;

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

static inline float	get_vertical_length(float degree, t_ray_info *info)
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
	return (inverse);
}

static inline int	get_line_location(float degree)
{
	float	zero_degree = zero_start_degree(degree);
	float	degree_to_percent = zero_degree / Player_FOV * 100;
	float	line_location = WIN_WIDTH * (degree_to_percent / 100);
	if (line_location == WIN_WIDTH)
		line_location = WIN_WIDTH - 1;
	return (line_location);
}

extern void	try_put_plane(float start_y, float line_x, int degree);
extern void	try_put_plane_2(float degree, float line_len, t_ray_info *info);

static void	ray_casting(t_mlx *mlx, float degree, t_ray_info *info)
{
	float	line_len;
	float	line_start;
	float	line_end;
	int		line_location;

	line_len = get_vertical_length(degree, info);
	line_start = (float)WIN_HEIGHT/2 - line_len/2;
	line_end = (float)WIN_HEIGHT/2 + line_len/2;
	line_location = get_line_location(degree);
	/*try_put*/
//	try_put_plane(line_start, line_location, (int)degree);
	try_put_plane_2(degree, line_len, info);
	/*put_line*/
	while (line_start < line_end)
	{
		printf("%d\n", line_location);
		printf("%f\n", line_start);
		put_pixel_to_img(&(mlx->background), line_location, line_start, color_num);
		++line_start;
	}
}

static inline int	is_current_longer(t_ray_info *prev_info, t_ray_info *current)
{
	if (get_length(player()->cord, prev_info->ray_hit) < get_length(player()->cord, current->ray_hit))
	{
		return (1);
	}
	return (0);
}

void	shoot_fov_ray(void)
{
	float		degree;
	t_ray_info	info;
	static t_ray_info	prev_info;

	info.ray_start = player()->cord;
	info.end_point = player()->view_point;
	degree = ((float)Player_FOV / 2) * -1;
	while (degree <= (float)Player_FOV / 2)
	{
		info.ray_dest = rotate_point(info.ray_start, info.end_point, degree);
		if (shoot_ray(info.ray_start, info.ray_dest, &(info), detect_wall_hit))
		{
			if (prev_info.wall_addr != info.wall_addr ||
					prev_info.texture != info.texture)
			{
				color_num = 0x00ff00;
//				if (is_current_longer(&prev_info, &info))
//				{
//					/*fixed line.*/
//					color_num = 0xff0000;
//					degree -= RAY_RES;
//					info.ray_dest = rotate_point(info.ray_start, info.end_point, degree);
//					shoot_ray(info.ray_start, info.ray_dest, &(info), detect_wall_hit);
//					ray_casting(mlx(), degree, &(info));
//					degree += RAY_RES;
//					info.ray_dest = rotate_point(info.ray_start, info.end_point, degree);
//					shoot_ray(info.ray_start, info.ray_dest, &(info), detect_wall_hit);
//				}
//				else
					ray_casting(mlx(), degree, &(info));
			}
			prev_info = info;
		}
		degree += RAY_RES;
	}
}
