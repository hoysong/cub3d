#include "my_algorithm.h"
#include <stdio.h>

int	put_vert_routine(t_point point, t_point d, void *img_ptr)
{
	int	color;
	if ((t_img *)img_ptr == &((mlx())->xpm_north))
		color = 0xaa0000;
	else if ((t_img *)img_ptr == &((mlx())->xpm_south))
		color = 0xaaaa00;
	else if ((t_img *)img_ptr == &((mlx())->xpm_west))
		color = 0xdddddd;
	else if ((t_img *)img_ptr == &((mlx())->xpm_east))
		color = 0x0;
	if ((point.x > 0 && point.x < WIN_WIDTH) &&
		(point.y >= 0 && point.y < WIN_HEIGHT))
		put_pixel_to_img(&(mlx()->background), point.x, point.y, color);
	//printf("plane_put: %f\n", point.x);
	return (0);
}

void	put_texture(t_point prev, t_point current, t_ray_info *info, t_ray_info *prev_info)
{
	shoot_ray(prev, current, prev_info->texture, put_vert_routine);
}
