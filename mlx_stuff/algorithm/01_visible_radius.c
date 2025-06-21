#include "./my_algorithm.h"
//#include "../player.h"
//#include "../mlx_hdler.h"
#include <math.h>
//#include <stdio.h>
# define Pie 3.141592653589793

/*center is such as player.*/
/*pt(point) is such as view_point from player.*/
t_point	rotate_point(t_point center, t_point pt, float degree)
{
	t_point	new;

	degree = (degree) * (Pie/180);
	new.x = ((pt.y - center.y)*(float)cos(degree) - (pt.x - center.x)*(float)sin(degree)) + center.x;
	new.y = ((pt.y - center.y)*(float)sin(degree) + (pt.x - center.x)*(float)cos(degree)) + center.y;
	return (new);
}
