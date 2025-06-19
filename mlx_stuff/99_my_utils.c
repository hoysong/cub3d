#include "../minilibx-linux/mlx.h"
#include "./mlx_hdler.h"
#include "../parser/pars_pub.h"
//#include <stddef.h>

void	get_img_data(t_img *img)
{
	img->data_addr = mlx_get_data_addr(
			img->img_ptr,
			&(img->bits_per_pixel),
			&(img->size_line),
			&(img->endian));
}

size_t	get_minimap_ratio(void)
{
	size_t	height = get_max_height();
	size_t	length = get_max_length();
	size_t	square_len;

	if (height > length)
		square_len = MINISIZE/height;
	else
		square_len = MINISIZE/length;
	return (square_len);
}
