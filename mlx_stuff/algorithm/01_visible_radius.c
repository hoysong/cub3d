#include "./my_algorithm.h"
#include "../player.h"
#include "../mlx_hdler.h"
#include <math.h>
#include <stdio.h>
# define Pie 3.141592653589793

void	get_dot(t_point me, t_point vp, float degree)
{
	t_point	new;

	//vp.x -= me.x;
	//vp.y -= me.y;
	//printf("vpx: %f vpy: %f\n", vp.x, vp.y);
	//vp.x = vp.x * (float)cos(degree) - vp.y * (float)sin(degree);
	//vp.y = vp.x * (float)sin(degree) + vp.y * (float)cos(degree);
	//vp.x += me.x;
	//vp.y += me.y;
	printf("%f %f\n", vp.x, vp.y);
	new.x = ((vp.x - me.x)*(float)cos(degree * (Pie/180)) - (vp.y - me.y)*(float)sin(degree *(Pie/180))) + me.x;
	new.y = ((vp.x - me.x)*(float)sin(degree * (Pie/180)) + (vp.y - me.y)*(float)cos(degree *(Pie/180))) + me.y;
	printf("degree:%f | vp: x: %f, y: %f\n", degree, new.x, new.y);
	/*test put_pixel*/
	put_pixel_to_img(&(mlx()->minimap), new.x * (float)get_minimap_ratio(), new.y * (float)get_minimap_ratio(), 0x0);
	put_pixel_to_img(&(mlx()->minimap), 1 + new.x * (float)get_minimap_ratio(), 1 + new.y * (float)get_minimap_ratio(), 0x0);
}

//void	get_visivle_radius(void)
//{
//	//90도?
//	get_dot(player()->cord, player()->view_point, RAY_RES);
//}
