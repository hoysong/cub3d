#include "./my_algorithm.h"
#include "../mlx_hdler.h"
#include "../../parser/pars_pub.h"
#include "../player.h"
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
//		return (NULL);
}

static int	fov_ray_routine(t_point point, t_point d, void *ray_info)
{
	t_point	floor_pt;

	floor_pt.x = (int)floor(point.x);
	floor_pt.y = (int)floor(point.y);
	put_pixel_to_img(
			&(mlx()->minimap),
			to_minimap_ratio(point).x,
			to_minimap_ratio(point).y,
			0x0000ff);
	if (get_map()
			[(int)TO_INDEX(floor_pt.y)]
			[(int)TO_INDEX(floor_pt.x)] == '1')
	{
		return (1);
	}
	return (0);
}

void	draw_fov(t_player *player)
{
	float	degree;
	t_point	dest_point;

	degree = ((float)Player_FOV / 2) * -1;
	dest_point = rotate_point(player->cord, player->view_point, degree);
	shoot_ray(player->cord, dest_point, NULL, fov_ray_routine);
	degree = ((float)Player_FOV / 2);
	dest_point = rotate_point(player->cord, player->view_point, degree);
	shoot_ray(player->cord, dest_point, NULL, fov_ray_routine);
}
