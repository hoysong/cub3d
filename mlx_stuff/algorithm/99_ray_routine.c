#include "./my_algorithm.h"
#include "../mlx_hdler.h"
#include "../../parser/pars_pub.h"
#include <math.h>
#include <stdio.h>

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
	t_point	floor_pt;

	floor_pt.x = (int)floor(point.x);
	floor_pt.y = (int)floor(point.y);

	put_pixel_to_img(
			&(mlx()->minimap),
			to_minimap_ratio(point).x,
			to_minimap_ratio(point).y,
			FOV_COLOR);
	if (get_map()
			[(int)TO_INDEX(floor_pt.y)]
			[(int)TO_INDEX(floor_pt.x)] == '1')
	{
		ray_from_where(point, d);
		return (1);
	}
	return (0);
}

