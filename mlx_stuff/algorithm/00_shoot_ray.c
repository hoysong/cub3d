#include "./my_algorithm.h"
#include "../player.h"
#include "../mlx_hdler.h"
#include "../../parser/pars_pub.h"
#include <math.h>
#include <stdio.h>

inline t_point	to_minimap_ratio(t_point point)
{
	point.x = MINI_RES(point.x) * get_minimap_ratio();
	point.y = MINI_RES(point.y) * get_minimap_ratio();
	return (point);
}

static float	my_abs(float num)
{
	if (num < 0)
		return (num *= -1);
	return (num);
}

t_point	shoot_ray(t_point start, t_point end, int(*func_ptr)(t_point))
{
	t_point	ray;
	float	dx, dy, step;
	int		i;

	dx = (end.x - start.x);
	dy = (end.y - start.y);
	if (my_abs(dx) >= my_abs(dy))
	  step = my_abs(dx);
	else
	  step = my_abs(dy);
	dx = dx / step;
	dy = dy / step;
	ray.x = start.x;
	ray.y = start.y;
	i = 0;

	while (i <= step)
	{
		if (func_ptr(ray))
			return (ray);
		ray.x = ray.x + dx;
		ray.y = ray.y + dy;
		i = i + 1;
	}
	ray.x = -1;
	ray.y = -1;
	return (ray);
}

inline int	ray_routine(t_point point)
{
	put_pixel_to_img(
			&(mlx()->minimap),
			to_minimap_ratio(point).x,
			to_minimap_ratio(point).y,
			FOV_COLOR);
	printf("x:%d | y:%d\n",
			(int)floor(point.x/SIZE_OF_BLOCK),
			(int)floor(point.y/SIZE_OF_BLOCK));

	if (get_map()[(int)floor(point.y/SIZE_OF_BLOCK)][(int)floor(point.x/SIZE_OF_BLOCK)] == '1')
		return (1);
	return (0);
}

void	shoot_fov_ray(void)
{
	t_point	start;
	t_point	end;
	t_point	dest;
	int		degree;

	start = player()->cord;
	end = player()->view_point;

	degree = (Player_FOV / 2) * -1;
	while (degree < Player_FOV / 2)
	{
		dest = rotate_point(start, end, degree);
		shoot_ray(start, dest, ray_routine);
		degree += RAY_RES;
	}
}
