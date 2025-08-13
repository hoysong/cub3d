#include "./mlx_hdler.h"
#include "./algorithm/my_algorithm.h"
#include "../parser/pars_priv.h"
#include "../minilibx-linux/mlx.h"
#include <stdio.h>

void	get_img_data(t_img *img)
{
	img->data_addr = mlx_get_data_addr(
			img->img_ptr,
			&(img->bits_per_pixel),
			&(img->size_line),
			&(img->endian));
	printf("%p\n", img->data_addr);
}

size_t	get_minimap_ratio(void)
{
	size_t	height = get_pars()->map_max_height;
	size_t	length = get_pars()->map_max_length;
	size_t	square_len;

	if (height > length)
		square_len = MINISIZE/height;
	else
		square_len = MINISIZE/length;
	return (square_len);
}

inline int	get_xpm_pixel_color(t_img xpm, t_point pixel)
{
	return(
			((int *)xpm.data_addr)
			[(((int)pixel.y * xpm.size_line) >> 2) +
			(((int)pixel.x * xpm.bits_per_pixel) >> 5)]
			);
}
