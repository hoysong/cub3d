#include "./my_algorithm.h"
#include "../player.h"
#include "../mlx_hdler.h"
#include "../../parser/pars_pub.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <float.h>

/*
 * 0. 파라미터는?
 * 		어디로 쏠 지.
 * 			결국 맵은 닫혀있으니까 어디든 충돌함.
 * 			만약 찾지 못하만 에러를 리턴하면 될 듯.
 * 1. 파라미터 다시생각.
 * 		t_point ray_shooter(t_point from, t_point to, funt_ptr);
 * 		func_ptr는 2가지 정도면 될 듯 하다.
 * 			+ 하나는 minimap에 픽셀을 찍을 함수.
 * 			+ 다른 하나는 ray 충돌지점을 계산할 함수.
 * 			if (func_ptr( (t_point)point ))
 * 				break ;
 * 			???
 * 			shooy_ray를 2번 호출할 필요가 있을까.
 * 			충돌지점을 찾기 위해 ray를 발사하면서, 충돌지점을 찾아내면 된다.
 * 			가시거리를 정해버리자.
 * 2. 리턴타입
 * 		출돌지점을 리턴하면 되나?
 * 		리턴한다면 어떻게 해야하나.
 * 			일단 미니맵에 적용되는 것은 시각화 하기 위한 것이다.
 * 			먼저 충돌지점을 구하고,
 * 			이를 미니맵의 ratio로 변환하여 찍어야 한다.
 * 3. 충돌지점을 리턴받고 나서.
 * 		가까운 정수 roundf()를 사용하면 텍스처를 알 수 있지 않을까.
 * 4. x와 y를 정수로 만들면?
 * 		홀 짝 구별을 통해서 만들 수 있지 않을까?
 * 		플레이어가 우측 하단에 있다는 가정..
 * 			x 홀, y 홀
 * */

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
	printf("%d | %d\n", (int)floor(point.y/SIZE_OF_BLOCK),(int)floor(point.x/SIZE_OF_BLOCK));
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
