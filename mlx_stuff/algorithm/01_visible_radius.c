#include "./my_algorithm.h"
#include "../player.h"
#include "../mlx_hdler.h"
#include <math.h>
#include <stdio.h>
# define Pie 3.141592653589793

void	get_dot(t_point me, t_point vp, float degree)
{
	t_point	new;

	printf("%f %f\n", vp.x, vp.y);
	new.x = ((vp.x - me.x)*(float)cos(degree * (Pie/180)) - (vp.y - me.y)*(float)sin(degree *(Pie/180))) + me.x;
	new.y = ((vp.x - me.x)*(float)sin(degree * (Pie/180)) + (vp.y - me.y)*(float)cos(degree *(Pie/180))) + me.y;
	printf("degree:%f | vp: x: %f, y: %f\n", degree, new.x, new.y);
	/*test put_pixel*/
	put_pixel_to_img(&(mlx()->minimap), new.x * (float)get_minimap_ratio(), new.y * (float)get_minimap_ratio(), 0xff0000);
}

//void	get_visivle_radius(void)
//{
//	//90도?
//	get_dot(player()->cord, player()->view_point, RAY_RES);
//}
