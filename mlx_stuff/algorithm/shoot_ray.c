#include "./my_algorithm.h"

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
		++i;
	}
	return (0);
}
