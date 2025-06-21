#include "./my_algorithm.h"
#include "../player.h"
#include "../mlx_hdler.h"
#include <math.h>
#include <stdio.h>
# define Pie 3.141592653589793

t_point	cord_correction(t_point point)
{
	point.x = point.y;
	point.y = point.x * -1;
	return (point);
}

void	get_dot(t_point me, t_point vp, float degree)
{
	t_point	new;

	//printf("%f %f\n", vp.x, vp.y);
	//degree = (degree + 90) * (Pie/180);
	//new.x = ((vp.x - me.x)*(float)cos(degree) - (vp.y - me.y)*(float)sin(degree)) + me.x;
	//new.y = ((vp.x - me.x)*(float)sin(degree) + (vp.y - me.y)*(float)cos(degree)) + me.y;
	//printf("degree:%f | vp: x: %f, y: %f\n", degree, new.x, new.y);
	///*test put_pixel*/
	//put_pixel_to_img(&(mlx()->minimap), new.x * (float)get_minimap_ratio(), new.y * (float)get_minimap_ratio(), 0xff0000);
	//
	printf("%f %f\n", vp.x, vp.y);
	degree = (degree - 90) * (Pie/180);
	new.x = ((vp.y - me.y)*(float)cos(degree) - (vp.x - me.x)*(float)sin(degree)) + me.x;
	new.y = ((vp.y - me.y)*(float)sin(degree) + (vp.x - me.x)*(float)cos(degree)) + me.y;
	printf("degree:%f | vp: x: %f, y: %f\n", degree, new.x, new.y);
	/*test put_pixel*/
	put_pixel_to_img(&(mlx()->minimap), new.x * (float)get_minimap_ratio(), new.y * (float)get_minimap_ratio(), 0xff0000);
}

//void	get_visivle_radius(void)
//{
//	//90도?
//	get_dot(player()->cord, player()->view_point, RAY_RES);
//}
