#include "./my_algorithm.h"
#include <math.h>

/*center is such as player.*/
/*pt(point) is view_point from player.*/
t_point	rotate_point(t_point center, t_point pt, float degree)
{
	t_point	new;

	degree = (degree) * (Pie/180);
	new.x = ((pt.x - center.x)*(float)cos(degree) - (pt.y - center.y)*(float)sin(degree)) + center.x;
	new.y = ((pt.x - center.x)*(float)sin(degree) + (pt.y - center.y)*(float)cos(degree)) + center.y;
	return (new);
}
