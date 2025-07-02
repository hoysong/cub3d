#include "./my_algorithm.h"
#include <math.h>

/*center is such as player.*/
/*pt(point) is view_point from player.*/
inline t_point	rotate_point(t_point center, t_point pt, float degree)
{
	t_point	new;

	degree = (degree) * (Pie/180);
	new.x = ((pt.x - center.x)*(float)cos(degree) - (pt.y - center.y)*(float)sin(degree)) + center.x;
	new.y = ((pt.x - center.x)*(float)sin(degree) + (pt.y - center.y)*(float)cos(degree)) + center.y;
	return (new);
}

inline float	my_abs(float num)
{
	if (num < 0)
		return (num *= -1);
	return (num);
}

/*return's length of between p1 and p2.*/
inline float	get_length(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

