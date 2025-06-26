#include "../player.h"
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

static inline float	get_win_x(float degree)
{
	float	percent_of_degree;

	percent_of_degree = (degree / Player_FOV) * 100;
	return ((float)WIN_WIDTH * percent_of_degree / 100);
}

static float	get_len(t_point a, t_point b, t_point c)
{
	float	A = b.y - a.y;
	float	B = -(b.x - a.x);
	float	C = -a.x*(b.y - a.y) + a.y*(b.x - a.x);

	float	len;
	len = my_abs(A*c.x + B*c.y + C) / sqrt(pow(A, 2) + pow(B, 2));
	return (len);
}

static void	ray_casting(t_mlx *mlx, float degree, t_ray_info *info)
{
	float	win_x;
	degree += (float)Player_FOV / 2;
	win_x = get_win_x(degree);
	float	view_dist = get_length(player()->cord, player()->view_point);;
	float	ray_hit_dist;
	ray_hit_dist = get_len(
		rotate_point(player()->cord, player()->view_point, -90),
		player()->cord,
		info->ray_hit
		);
	float	percent_of_hit_dist = (ray_hit_dist / view_dist) * 100;
	float	vert_from_up = ((float)WIN_HEIGHT * percent_of_hit_dist / 100) / 2; // 선은 위에서부터 긋는다. 시작지점.
	float	vert_from_down = (float)WIN_HEIGHT - vert_from_up; // 그어진 선이 아래에 도착하는 도착지점.

	int	i = vert_from_up;
	while (i < vert_from_down)
	{
		put_pixel_to_img(&(mlx->background), win_x, i, 0x0000);
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
