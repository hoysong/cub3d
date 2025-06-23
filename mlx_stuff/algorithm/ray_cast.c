#include "../player.h"

static void	ray_casting(float degree, t_ray_info *info)
{
}

void	shoot_fov_ray(void)
{
	t_point		start;
	t_point		end;
	t_point		dest;
	t_ray_info	ray_info;
	int			degree;

	start = player()->cord;
	end = player()->view_point;

	degree = (Player_FOV / 2) * -1;
	while (degree <= Player_FOV / 2)
	{
		dest = rotate_point(start, end, degree);
		if (shoot_ray(start, dest, &(ray_info), detect_wall_hit))
		{
			ray_casting(degree, &(ray_info));
		}
		degree += RAY_RES;
	}
}
