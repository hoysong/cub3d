#ifndef MY_ALGORITHM
# define MY_ALGORITHM
# define Pie 3.141592653589793
# include "../cub_defs.h"
# include "../mlx_hdler.h"

/*simple point struct.*/
typedef struct s_point
{
	float x;
	float y;
}t_point;

typedef struct s_ray_info
{
	char	**map;
	t_mlx	*mlx;
	float	degree;
	int	wall_x;
	int	wall_y;
	char	*wall_addr;
	t_img	*texture;
	t_point		ray_start;
	t_point		ray_dest;
	t_point		ray_hit;
	t_point		end_point;
}t_ray_info;

typedef struct s_wall_node t_wall_node;
typedef struct s_wall_node
{
	t_wall_node	*next;
	t_wall_node	*prev;
	t_ray_info	*info;
	t_img		*texture;

	/*가상 좌표상의 코너 위치좌표.*/
	t_point		wall_start_cord;
	/*실제 표시되는 시작점의 위치.*/
	t_point		start_point;
	float		start_degree;
	float		start_x;

	t_point		wall_end_cord;
	t_point		end_point;
	float		end_degree;
	float		end_x;

	float		wall_width;
	float		correction_flag;
}t_wall_node;

/****************/
/*ray_functions.*/
/****************/
/*func_ptr is function pointer.*/
/*func_ptr's last void * is for call_by_reference.*/
/*ray_functions will send call_by_ref param to func_ptr's third parameter.*/

/*shoot_limited_ray.*/
int	shoot_ray(
		t_point start,
		t_point end,
		void *call_by_ref,
		int(*func_ptr)(t_point, t_point, void *)
		);
/*shoot infinite ray.*/
int	shoot_inf_ray(
		t_point start,
		t_point end,
		void *call_by_ref,
		int(*func_ptr)(t_point, t_point, void *)
		);

/*ray_routines.*/

/*shoot_ray(or shoot_inf_ray)'s routine.*/
int	detect_wall_hit(t_point point, t_point d, void *ray_info);

/*This will rotate point 'pt' with respect to the param 'center'.*/
t_point	rotate_point(t_point center, t_point pt, float degree);

/*플레이어의 FOV 각도만큼 부채꼴로 ray를 방사합니다.*/
//void	shoot_fov_ray(void);

t_point	to_minimap_ratio(t_point point, t_mlx *mlx_strc);

float	my_abs(float num);

/*this will returns length of between p1 and p2.*/
float	get_length(t_point p1, t_point p2);

/*실험적.*/
// 벽 linked list를 만듭니다.
//void	make_wall_linked_list(void);
#endif
