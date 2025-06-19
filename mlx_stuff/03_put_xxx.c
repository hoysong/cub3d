#include "./mlx_hdler.h"
#include "../minilibx-linux/mlx.h"

void	get_img_data(t_img *img)
{
	img->data_addr = mlx_get_data_addr(
			img->img_ptr,
			&(img->bits_per_pixel),
			&(img->size_line),
			&(img->endian));
}


inline void	put_pixel_to_img(t_img *img, int horiz, int vert, int color)
{
	char	*location_to_put;

	location_to_put = img->data_addr;
	*(unsigned int *)(location_to_put + ((img->bits_per_pixel / 8) * horiz) + img->size_line * vert) = color;
}

inline void	put_background(void)
{
	mlx_put_image_to_window(mlx()->mlx_ptr, mlx()->mlx_window, mlx()->background.img_ptr, 0, 0);
}

inline void	put_minimap(void)
{
	mlx_put_image_to_window(mlx()->mlx_ptr, mlx()->mlx_window, mlx()->minimap.img_ptr, 0, 0);
}
