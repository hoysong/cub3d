#include "./my_algorithm.h"
#include "../mlx_hdler.h"
#include "../../parser/pars_pub.h"
#include <math.h>

static inline t_img *get_player_view_texture(t_point point, t_point d)
{
	d.x *= -1;
	d.y *= -1;
	if ((int)floor(TO_INDEX(point.x + d.x)) < (int)floor(TO_INDEX(point.x)))
		return (&(mlx()->xpm_west));
	else if ((int)floor(TO_INDEX(point.x + d.x)) > (int)floor(TO_INDEX(point.x)))
		return (&(mlx()->xpm_east));
	else if ((int)floor(TO_INDEX(point.y + d.y)) < (int)floor(TO_INDEX(point.y)))
		return (&(mlx()->xpm_north));
	else if ((int)floor(TO_INDEX(point.y + d.y)) > (int)floor(TO_INDEX(point.y)))
		return (&(mlx()->xpm_south));
	else
		return (&(mlx()->xpm_west));
}

inline int	detect_wall_hit(t_point point, t_point d, void *ray_info)
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
		((t_ray_info *)ray_info)->wall_addr = &(get_map()
			[(int)TO_INDEX(floor_pt.y)]
			[(int)TO_INDEX(floor_pt.x)]);
		((t_ray_info *)ray_info)->texture = get_player_view_texture(point, d);
		((t_ray_info *)ray_info)->ray_hit = point;
		return (1);
	}
	return (0);
}
