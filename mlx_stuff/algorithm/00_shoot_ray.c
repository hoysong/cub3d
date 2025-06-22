#include "./my_algorithm.h"
#include "../player.h"
#include "../mlx_hdler.h"
#include "../../parser/pars_pub.h"
#include <math.h>
#include "../mlx_hdler.h"
#include <stdio.h>
/*
 * 1.99 / 1 = 1
 * + 0.01
 * 2.00 / 1 = 2
 */

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

/*
 * x또는 y가 증/감 됨으로써로 구분하면 됨.
 * x가 감소되어 인덱스에 도달했다 = 오른쪽에서 바라봄.
 * x가 증가하며 인덱스에 도달했다 = 왼쪽에서 바라봄.
 * y가 감소되며 인덱스에 도달했다 = 아래에서 바라봄.
 * y가 증가되며 인덱스에 도달했다 = 위에서 바라봄.
 */

t_point	shoot_ray(t_point start, t_point end, int(*func_ptr)(t_point, t_point))
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
	printf("dx=%f dy=%f\n", d.x, d.y);
	while (i <= step)
	{
		if (func_ptr(ray, d))
			return (ray);
		ray.x = ray.x + d.x;
		ray.y = ray.y + d.y;
		i = i + 1;
	}
	ray.x = -1;
	ray.y = -1;
	return (ray);
}

# define NORTH 0xffff00
# define SOUTH 0x00ffff
# define WEST 0x00ff00
# define EAST 0x0000ff
# define UNKNOWN 0xffffff

static void ray_from_where(t_point point, t_point d)
{
	/*invert sign.*/
	d.x *= -1;
	d.y *= -1;
	if ((int)floor(TO_INDEX(point.x + d.x)) < (int)floor(TO_INDEX(point.x)))
		printf("west?==========================================\n");
	else if ((int)floor(TO_INDEX(point.x + d.x)) > (int)floor(TO_INDEX(point.x)))
		printf("east?==========================================\n");
	if ((int)floor(TO_INDEX(point.y + d.y)) < (int)floor(TO_INDEX(point.y)))
		printf("north?==========================================\n");
	else if ((int)floor(TO_INDEX(point.y + d.y)) > (int)floor(TO_INDEX(point.y)))
		printf("south?==========================================\n");
}

inline int	ray_routine(t_point point, t_point d)
{
	int		wall_tex = UNKNOWN;
	t_point	floor_pt;

	floor_pt.x = (int)floor(point.x);
	floor_pt.y = (int)floor(point.y);

	put_pixel_to_img(
			&(mlx()->minimap),
			to_minimap_ratio(point).x,
			to_minimap_ratio(point).y,
			FOV_COLOR);
	printf(
			"RAY: x=%f , y=%f | index: %d, %d\n",
			point.x,
			point.y,
			(int)floor(TO_INDEX(point.x)),
			(int)floor(TO_INDEX(point.y))
			);
	if (get_map()
			[(int)TO_INDEX(floor_pt.y)]
			[(int)TO_INDEX(floor_pt.x)] == '1')
	{
		/*충돌함.*/
					printf("충돌: x=%f y=%f\n",
							point.x,
							point.y);
					printf("floor: x=%d y=%d\n",
							(int)floor(point.x),
							(int)floor(point.y));
					printf("index: x=%d y=%d\n",
							(int)floor(point.x/SIZE_OF_BLOCK),
							(int)floor(point.y/SIZE_OF_BLOCK));
		printf("\n");
		ray_from_where(point, d);
		return (1);
	}
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
	while (degree <= Player_FOV / 2)
	{
		dest = rotate_point(start, end, degree);
		ray_cast(shoot_ray(start, dest, ray_routine));
		degree += RAY_RES;
	}
}
