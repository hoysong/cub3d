#include "../player.h"
#include "../mlx_hdler.h"
#include <math.h>
#include <stdio.h>

static inline float	my_abs(float num)
{
	if (num < 0)
		return (num *= -1);
	return (num);
}

/*return's length of between p1 and p2.*/
static inline float	get_length(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

static inline float	zero_start_degree(float degree)
{
	degree += (float)Player_FOV / 2;
	return (degree);
}

static void	ray_casting_1(t_mlx *mlx, float degree, t_ray_info *info)
{
	printf("======================cast_1======================\n");
	printf("degree : %f\n", degree);
	/*get_ray_to_wall dist*/
	float	hit_len;
	float	hit_len_max;
	float	hit_len_percent;

	hit_len = get_length(player()->cord, info->ray_hit);
	hit_len_max = get_length(player()->cord, player()->view_point);
	hit_len_percent = 100 - (hit_len / hit_len_max * 100);
	printf("hit_len    : %f\n", hit_len);
	printf("hit_len_max: %f\n", hit_len_max);
	printf("hit_percent: %f\n", hit_len_percent);
	/*ray_to_wall dist to win_size*/
	float	ray_win_size = WIN_HEIGHT * (hit_len_percent / 100);
	float	line_start = (WIN_HEIGHT - ray_win_size) / 2;
	float	line_end = line_start + ray_win_size;
	int	i = line_start;
	/*get_x location*/
	float	zero_degree = zero_start_degree(degree);
	float	degree_percent = zero_degree / Player_FOV * 100;
	float	x_percent = WIN_WIDTH * (degree_percent / 100);
	printf("degree_precent : %f\n", degree_percent);
	printf("x_percent      : %f\n", x_percent);
	if (x_percent == WIN_WIDTH)
		return ;
	while (i < line_end)
	{
		put_pixel_to_img(&(mlx->background), x_percent, i, 0x0000aa);
		i++;
	}
	printf("ray_win_size: %f\n", ray_win_size);
	printf("\n");
}

static void	ray_casting_2(t_mlx *mlx, float degree, t_ray_info *info)
{
	printf("======================cast_2======================\n");
	float	cos_degree;
	if (degree < 0)
		cos_degree = my_abs(degree);
	else
		cos_degree = degree;

	float	hit_len;
	float	hit_len_max;
	float	perp_len;
	float	perp_percent;

	hit_len = get_length(player()->cord, info->ray_hit);
	hit_len_max = get_length(player()->cord, player()->view_point);
	perp_len = cos(cos_degree * (Pie/180)) * hit_len;
	perp_percent = 100 - (perp_len / hit_len_max * 100);
	printf("hit_len : %f\n", hit_len);
	printf("hit_len_max : %f\n", hit_len_max);
	printf("perp_len: %f\n", perp_len);
	printf("perp_percent: %f\n", perp_percent);
	/*perp to win_size*/
	float	line_len = WIN_HEIGHT * (perp_percent / 100);
	float	win_start = (WIN_HEIGHT - line_len)/2;
	float	win_end = win_start + line_len;
	printf("line_len: %f\n", line_len);
	/*get_x location*/
	float	zero_degree = zero_start_degree(degree);
	float	degree_percent = zero_degree / Player_FOV * 100;
	float	x_percent = WIN_WIDTH * (degree_percent / 100);
	printf("degree_precent : %f\n", degree_percent);
	printf("x_percent      : %f\n", x_percent);
	if (x_percent == WIN_WIDTH)
		return ;
	int	i = win_start;
	while (i < win_end)
	{
		put_pixel_to_img(&(mlx->background), x_percent, i, 0x00ff00);
		i++;
	}
	printf("\n");
}

static void	ray_casting_3(t_mlx *mlx, float degree, t_ray_info *info)
{
	printf("======================cast_3======================\n");
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
	printf("inverse: %f\n", inverse);
	if (inverse > WIN_HEIGHT)
		inverse = WIN_HEIGHT;
	/*get_y start*/
	float	line_start;
	float	line_end;

	line_start = (float)WIN_HEIGHT/2 - inverse/2;
	line_end = (float)WIN_HEIGHT/2 + inverse/2;
	/*get_x location*/
	float	zero_degree = zero_start_degree(degree);
	float	degree_percent = zero_degree / Player_FOV * 100;
	float	x_percent = WIN_WIDTH * (degree_percent / 100);
	printf("degree_precent : %f\n", degree_percent);
	printf("x_percent      : %f\n", x_percent);
	if (x_percent == WIN_WIDTH)
		return ;
	int	i = line_start;
	while (i < line_end)
	{
		put_pixel_to_img(&(mlx->background), x_percent, i, 0xff0000);
		i++;
	}
	printf("\n");
}

static void	ray_casting(t_mlx *mlx, float degree, t_ray_info *info)
{
//	ray_casting_2(mlx, degree, info);
//	ray_casting_1(mlx, degree, info);
	ray_casting_3(mlx, degree, info);
}

void	shoot_fov_ray(void)
{
	t_point		start;
	t_point		end;
	t_point		dest;
	t_ray_info	ray_info;
	int			degree;

	start = player()->cord;
	end = player()->view_point;

	degree = (Player_FOV / 2) * -1;
	while (degree <= Player_FOV / 2)
	{
		dest = rotate_point(start, end, degree);
		if (shoot_ray(start, dest, &(ray_info), detect_wall_hit))
		{
			ray_casting(mlx(), degree, &(ray_info));
		}
		degree += RAY_RES;
	}
}
