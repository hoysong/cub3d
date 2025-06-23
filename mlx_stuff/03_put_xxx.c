#include "./mlx_hdler.h"
#include "../minilibx-linux/mlx.h"
#include "./algorithm/my_algorithm.h"

inline void	put_pixel_to_img(t_img *img, int horiz, int vert, int color)
{
	char	*location_to_put;

	location_to_put = img->data_addr;
	*(unsigned int *)
		(location_to_put + ((img->bits_per_pixel / 8) * horiz) + img->size_line * vert) = color;
}

inline void	put_background(void)
{
	mlx_put_image_to_window(mlx()->mlx_ptr, mlx()->mlx_window, mlx()->background.img_ptr, 0, 0);
}

inline void	put_minimap(void)
{
	mlx_put_image_to_window(mlx()->mlx_ptr, mlx()->mlx_window, mlx()->minimap.img_ptr, 0, 0);
}

static int	get_xpm_pixel_color(t_img xpm, t_point pixel)
{
	return(((int *)xpm.data_addr)
			[ (((int)pixel.y * xpm.size_line)/4) +
			(((int)pixel.x * xpm.bits_per_pixel)/32) ]);
}

void	try_put_xpm(void)
{
	t_img	img = mlx()->xpm_north;
	t_point	point;

	point.x = 0;
	point.y = 0;
	while (point.y < img.xpm_height)
	{
		while (point.x < img.xpm_width)
		{
			put_pixel_to_img(
					&(mlx()->background),
					point.x, point.y,
					get_xpm_pixel_color(img, point)
					);
			point.x++;
		}
		point.x = 0;
		point.y++;
	}
}

