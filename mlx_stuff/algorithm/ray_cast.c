#include "../player.h"
#include "../mlx_hdler.h"
#include <math.h>
#include <stdio.h>

static inline float	zero_start_degree(float degree)
{
	degree += (float)Player_FOV / 2;
	return (degree);
}

float	get_vertlen(t_point a, t_point b, t_point c)
{
	float	m;
	m = (b.y - a.y) / (b.x - a.x);

	float result;
	result = my_abs(m*c.x - c.y + (a.y - (m*a.x))) / sqrt(pow(m, 2) + 1);
	return (result);
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

	hit_len = get_vertlen(
			player()->cord,
			rotate_point(player()->cord, player()->view_point, 90),
			info->ray_hit);
	perp_len = hit_len;

//	hit_len = get_length(player()->cord, info->ray_hit);
//	/*90도인 경우 0이 나와버려 문제가 발생한다 (주석 없애지 말 것.)*/
//	/*지금 해결된 상태는 아님.*/
//	perp_len = cos(cos_degree * (Pie/180)) * hit_len;

	/*to inverse*/
	float	inverse;

	//if (cos_degree == 90)
	//{
	//	perp_len = hit_len;
	//}
	inverse = (SIZE_OF_BLOCK * WIN_HEIGHT) / perp_len;
	//printf("degree  : %f\n", degree);
	//printf("cos_degree  : %f\n", cos_degree);
	printf("rayhit  : %f\n", hit_len);
	//printf("cos()   : %f\n", cos(cos_degree * (Pie/180)));
	printf("cos*hit : %f\n", perp_len);
	printf("RESULT  : %f\n", inverse);
	printf("\n");
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

void	try_put_plane(float start_y, float line_x, int degree);

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
	try_put_plane(line_start, line_location, (int)degree);
	/*put_line*/
	while (line_start < line_end)
	{
		put_pixel_to_img(&(mlx->background), line_location, line_start, 0xffffff);
		++line_start;
	}
}

void	shoot_fov_ray(void)
{
	float		degree;
	t_ray_info	info;

	info.ray_start = player()->cord;
	info.end_point = player()->view_point;
	degree = ((float)Player_FOV / 2) * -1;
	while (degree <= (float)Player_FOV / 2)
	{
		info.ray_dest = rotate_point(info.ray_start, info.end_point, degree);
		if (shoot_ray(info.ray_start, info.ray_dest, &(info), detect_wall_hit))
			ray_casting(mlx(), degree, &(info));
		degree += RAY_RES;
	}
}
