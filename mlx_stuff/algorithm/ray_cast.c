#include "../player.h"
#include <math.h>
#include <stdio.h>

static inline float	my_abs(float num)
{
	if (num < 0)
		return (num *= -1);
	return (num);
}

/*return's length of between p1 and p2.*/
static inline float	get_length(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

static inline float	get_win_x(float degree)
{
	float	percent_of_degree;

	percent_of_degree = (degree / Player_FOV) * 100;
	return ((float)WIN_WIDTH * percent_of_degree / 100);
}

static inline float	unfisheye_len(t_point a, t_point b, t_point c)
{
	float	A = b.y - a.y;
	float	B = -(b.x - a.x);
	float	C = -a.x*(b.y - a.y) + a.y*(b.x - a.x);
	float	len;

	len = my_abs(A*c.x + B*c.y + C) / sqrt(pow(A, 2) + pow(B, 2));
	return (len);
}

static void	ray_casting(t_mlx *mlx, float degree, t_ray_info *info)
{
	float	win_x;
	degree += (float)Player_FOV / 2;
	win_x = get_win_x(degree);
	float	view_dist = get_length(player()->cord, player()->view_point);;
	float	perp_wall_dist;
	perp_wall_dist = unfisheye_len(
		rotate_point(player()->cord, player()->view_point, -90),
		player()->cord,
		info->ray_hit
		);
	///*윈도우 비율로 맞추는 과정.*/
	//	/*어안렌즈 보정 값은 뷰포인트의 어느정도에 해당하는가?*/
	//	float	percent_view_dist = (perp_wall_dist / view_dist) * 100;
	//	/*최대가시거리와 윈도우의 비례식?*/
	//	float	brsick = view_dist * WIN_HEIGHT;
	//	/**/
	//	float	rbrsick_wall_height = brsick / perp_wall_dist;
	//	/**/
	//	float	real_height = rbrsick_wall_height / WIN_HEIGHT * 100;

	//	/*이미지의 시작과 끝점 지정.*/
	//	float	vert_start = (WIN_HEIGHT - real_height)/2;
	//	float	vert_end = (float)WIN_HEIGHT / 2 + real_height / 2;
	//	printf("%f\n", real_height);

	//	int	i = vert_start;
	//	while (i < vert_end)
	//	{
	//		put_pixel_to_img(&(mlx->background), win_x, i, 0x0000);
	//		i++;
	//	}
	/*2번째 코드.*/
//	/*윈도우 비율로 맞추는 과정.*/
	/*어안렌즈 보정 값은 뷰포인트의 어느정도에 해당하는가?*/
	/*100 퍼센트 중 어느정도에 해당하는가?*/
	float	percent_view_dist = (perp_wall_dist / view_dist) * 100;
	/*100퍼센트에서 해당하는 만큼을 다시 빼서 역수로 만든다.*/
	float	rev_per = 100 - percent_view_dist;
	/*역수를 다시 Window 높이에 적용한다.*/
	float	win_height_len = WIN_HEIGHT * ((rev_per + 17) / 100);
	printf("view_point_len : %f\n", get_length(player()->cord, player()->view_point));
	printf("rev_per        : %f\n", rev_per);
	printf("win_height_len : %f\n", win_height_len);
	int	i = (WIN_HEIGHT - win_height_len) / 2;
	printf("%d\n", i);
	win_height_len += i;
	while (i < win_height_len)
	{
		put_pixel_to_img(&(mlx->background), win_x, i, 0x0000);
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
			ray_casting(mlx(), degree, &(ray_info));
		}
		degree += RAY_RES;
	}
}
