#ifndef MY_ALGORITHM
# define MY_ALGORITHM
# define Pie 3.141592653589793
# include "../cub_defs.h"

typedef struct s_point
{
	float x;
	float y;
}t_point;

t_point	shoot_ray(t_point start, t_point end, int(*func_ptr)(float, float));
t_point	rotate_point(t_point center, t_point pt, float degree);
void	shoot_fov_ray(void);

#endif
