#include "./my_algorithm.h"
#include <unistd.h>
#include <stdio.h>
/*아래 define들은 추후 삭제해도 됨.*/
#define START_PIX_COLOR 0x00ff00
#define END_PIX_COLOR 0x00ffff

static int	fill_line(t_point pixel_location, t_point dummy1, void *dummy2)
{
	return (0);
}

void	try_put_plane_2(float degree, float line_len, t_ray_info *info)
{
	static t_ray_info prev_info;
}
