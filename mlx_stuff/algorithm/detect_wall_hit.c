#include "./my_algorithm.h"
#include "../mlx_hdler.h"
#include <math.h>

static inline t_img *get_player_view_texture(t_point point, t_point d, t_ray_info *info)
{
	d.x *= -1;
	d.y *= -1;
	if ((int)floor(TO_INDEX(point.x + d.x)) < (int)floor(TO_INDEX(point.x)))
		return (&(info->mlx->xpm_west));
	else if ((int)floor(TO_INDEX(point.x + d.x)) > (int)floor(TO_INDEX(point.x)))
		return (&(info->mlx->xpm_east));
	else if ((int)floor(TO_INDEX(point.y + d.y)) < (int)floor(TO_INDEX(point.y)))
		return (&(info->mlx->xpm_north));
	else if ((int)floor(TO_INDEX(point.y + d.y)) > (int)floor(TO_INDEX(point.y)))
		return (&(info->mlx->xpm_south));
	else
		return (&(info->mlx->xpm_west));
}

/*
 * Judge ray's wall hit.
 */
inline int	detect_wall_hit(t_point point, t_point d, void *ray_info)
{
	t_point	floor_pt;

	floor_pt.x = (int)floor(point.x);
	floor_pt.y = (int)floor(point.y);
	put_pixel_to_img(
			&(((t_ray_info *)ray_info)->mlx->minimap),
			to_minimap_ratio(point, ((t_ray_info *)ray_info)->mlx).x,
			to_minimap_ratio(point, ((t_ray_info *)ray_info)->mlx).y,
			FOV_COLOR);
	
	if (((t_ray_info *)ray_info)->map
			[(int)TO_INDEX(floor_pt.y)]
			[(int)TO_INDEX(floor_pt.x)] == '1')
	{
		((t_ray_info *)ray_info)->wall_addr = &(((t_ray_info *)ray_info)->map
			[(int)TO_INDEX(floor_pt.y)]
			[(int)TO_INDEX(floor_pt.x)]);
		(((t_ray_info *)ray_info)->wall_x) = (int)TO_INDEX(floor_pt.x);
		(((t_ray_info *)ray_info)->wall_y) = (int)TO_INDEX(floor_pt.y);
		((t_ray_info *)ray_info)->texture = get_player_view_texture(point, d, ((t_ray_info *)ray_info));
		((t_ray_info *)ray_info)->ray_hit = point;
		return (1);
	}
	return (0);
}
