#include "./my_algorithm.h"
#include "../player.h"
#include "../mlx_hdler.h"
#include <math.h>
#include <stdio.h>

void	get_dot(t_point me, t_point vp, float degree)
{
	t_point	new;

	printf("%f", cos(degree));

	new.x = (vp.x - me.x)*(float)cos(degree) - (vp.y - me.y)*(float)sin(degree) + me.x;
	new.y = (vp.x - me.x)*(float)sin(degree) + (vp.y - me.y)*(float)cos(degree) + me.y;
	printf("dot test: x: %f, y: %f\n", new.x, new.y);
	/*test put_pixel*/
	put_pixel_to_img(&(mlx()->minimap), new.x * (float)get_minimap_ratio(), new.y * (float)get_minimap_ratio(), 0xff0000);
}

void	get_visivle_radius(void)
{
	//90도?
	get_dot(player()->cord, player()->view_point, RAY_RES);
}
