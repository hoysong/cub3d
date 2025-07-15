#include "./my_algorithm.h"
#include <unistd.h>
#include <stdio.h>
/*아래 define들은 추후 삭제해도 됨.*/
#define START_PIX_COLOR 0x00aa00
#define END_PIX_COLOR 0x00aa00

static int	fill_line(t_point pixel_location, t_point dummy1, void *dummy2)
{
	float	line_x;
	float	line_end;

	line_x = pixel_location.x;
	line_end = (float)WIN_HEIGHT - pixel_location.y;
	int	i = pixel_location.y;
//	while (i < line_end)
//	{
//		put_pixel_to_img(&(mlx()->background), line_x, i, 0x440000);
//		++i;
//	}
	put_pixel_to_img(&(mlx()->background), line_x, pixel_location.y, START_PIX_COLOR);
	put_pixel_to_img(&(mlx()->background), line_x, line_end, END_PIX_COLOR);
	return (0);
}

void	try_put_plane(float start_y, float line_x, int degree)
{
	static t_point	prev_point;
	t_point			start;

	start.y = start_y;
	start.x = line_x;
	if (prev_point.x != 0 ||
		prev_point.y != 0)
	{
		shoot_ray(start, prev_point, NULL, fill_line);
	}
	prev_point.x = start.x;
	prev_point.y = start.y;
	if (degree == Player_FOV / 2)
	{
		prev_point.x = 0;
		prev_point.y = 0;
	}
}
