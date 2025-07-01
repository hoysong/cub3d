#include "../player.h"
#include "../mlx_hdler.h"
#include <math.h>

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

static void	ray_casting(t_mlx *mlx, float degree, t_ray_info *info)
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
	if (x_percent == WIN_WIDTH)
		x_percent = WIN_WIDTH - 1;
	int	i = line_start;
	while (i < line_end)
	{
		put_pixel_to_img(&(mlx->background), x_percent, i, 0x00aaaa);
		i++;
	}
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
