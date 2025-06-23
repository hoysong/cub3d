#include "./my_algorithm.h"
#include "../player.h"
#include "../mlx_hdler.h"
#include "../mlx_hdler.h"

inline t_point	to_minimap_ratio(t_point point)
{
	point.x = MINI_RES(point.x) * get_minimap_ratio();
	point.y = MINI_RES(point.y) * get_minimap_ratio();
	return (point);
}

static inline float	my_abs(float num)
{
	if (num < 0)
		return (num *= -1);
	return (num);
}

/*	shoot_ray함수를 더 건들게 있을까?
 *	더 없는 듯 하다.
 *	Return 1 을 통해서 목표에 도달했음을 리턴하고,
 *	함수포인터에 call by ref로 값까지 전달 해주면 더 할 것이 없다.
 *	이대로 유지하도록 하자.
 */

int	shoot_ray(t_point start, t_point end,
		void *call_by_ref,
		int(*func_ptr)(t_point, t_point, void *)
		)
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
		if (func_ptr(ray, d, call_by_ref))
			return (1);
		ray.x = ray.x + d.x;
		ray.y = ray.y + d.y;
		i = i + 1;
	}
	return (0);
}

static void	ray_casting(float degree, t_ray_info *info)
{
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
			ray_casting(degree, &(ray_info));
		}
		degree += RAY_RES;
	}
}
