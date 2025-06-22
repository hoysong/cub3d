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
	t_point	d;
	float	step;
	int		i;

	d.x = (end.x - start.x);
	d.y = (end.y - start.y);
	if (my_abs(d.x) >= my_abs(d.y))
	  step = my_abs(d.x);
	else
	  step = my_abs(d.y);
	d.x = d.x / step;
	d.y = d.y / step;
	ray = start;
	i = 0;
	while (i <= step)
	{
		if (func_ptr(ray))
			return (ray);
		ray.x = ray.x + d.x;
		ray.y = ray.y + d.y;
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
	if (get_map()[(int)floor(point.y/SIZE_OF_BLOCK)][(int)floor(point.x/SIZE_OF_BLOCK)] == '1')
		return (1);
	return (0);
}

/*필요 없을수도?*/
/*어차피 ray_routine에서 다 핸들링 됨.*/
void	ray_cast(t_point point)
{
	if (point.x < 0)
		return;
//	printf("충돌!\n");
	return;
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
		ray_cast(shoot_ray(start, dest, ray_routine));
		degree += RAY_RES;
	}
}
