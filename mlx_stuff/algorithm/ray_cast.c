#include "../player.h"
#include <math.h>
#include <stdio.h>

/*return's length of between p1 and p2.*/
static inline float	get_length(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

static void	ray_casting(float degree, t_ray_info *info)
{
	float percent_of_degree;

	/*각도를 변환하여 X의 위치에 점을 찍기.*/
		/*각도가 0부터 시작하도록 변경.*/
		degree += (float)Player_FOV / 2;
		/*레이 각도마다 일단 점을 찍어본다.*/
		percent_of_degree = (degree / Player_FOV) * 100;
		put_pixel_to_img(&(mlx()->background), (float)WIN_WIDTH * percent_of_degree / 100, WIN_HEIGHT / 2, 0x0);
	/*fisheye현상 고치는 값.*/
		/*일단 플레어어의 뷰포인트의 코사인(degree)/빗변*/
		cos(Player_FOV / 2);
	/*플레이어와 벽충돌점을 시야최대거리로부터 퍼센트화.*/
		float	view_dist = get_length(player()->cord, player()->view_point);;
		float	ray_hit_dist = get_length(player()->cord, info->ray_hit);
		float	percent_of_hit_dist = (ray_hit_dist / view_dist) * 100;
		float	vert_from_up = ((float)WIN_HEIGHT * percent_of_hit_dist / 100) / 2; // 선은 위에서부터 긋는다. 시작지점.
		float	vert_from_down = (float)WIN_HEIGHT - vert_from_up; // 그어진 선이 아래에 도착하는 도착지점.

		int	i = vert_from_up;
		while (i < vert_from_down)
		{
			put_pixel_to_img(&(mlx()->background), (float)WIN_WIDTH * percent_of_degree / 100, i, 0x0);
			i++;
		}
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
