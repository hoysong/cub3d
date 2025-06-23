#ifndef MY_ALGORITHM
# define MY_ALGORITHM
# define Pie 3.141592653589793
# include "../cub_defs.h"
# include "../mlx_hdler.h"

typedef struct s_point
{
	float x;
	float y;
}t_point;

typedef struct s_ray_info
{
	t_img	texture;
	t_point	ray_hit;
}t_ray_info;


/*ray를 투사합니다.*/
/*리턴타입 t_point는 ray충돌지점을 나타내기 위해 존재합니다.*/
int	shoot_ray(
		t_point start,
		t_point end,
		void *call_by_ref,
		int(*func_ptr)(t_point, t_point, void *)
		);
/*충돌지점이 감지되면 -1,-1이 아닌 t_point값을 리턴합니다.*/
/*ray가 투사되며 step당 실행할 루틴입니다.*/
int	ray_routine(t_point point, t_point d, void *info);
/*pt를 center 를 기준으로 degree만큼 회전합니다.*/
t_point	rotate_point(t_point center, t_point pt, float degree);
/*플레이어의 FOV 각도만큼 부채꼴로 ray를 방사합니다.*/
void	shoot_fov_ray(void);
/*가상의 맵을 위해 게산되던 포인트를 minimap의 좌표 비율로 변환합니다.*/
t_point	to_minimap_ratio(t_point point);

#endif
