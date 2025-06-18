#include "./mlx_hdler.h"
#include "../minilibx-linux/mlx.h"
#include "../parser/pars_priv.h"

int	rgb_to_int(t_rgb rgb)
{
	int				int_rgb;
	unsigned char	*bit_ptr;

	int_rgb = 0;
	bit_ptr = (unsigned char *)&int_rgb;
	*bit_ptr = rgb.red;
	bit_ptr++;
	*bit_ptr = rgb.green;
	bit_ptr++;
	*bit_ptr = rgb.blue;
	return (int_rgb);
}

void	make_floor_ceiling_image(void)
{
	/*바닥/천장의 rgb값 구하기.*/
	mlx()->floor_color = rgb_to_int(get_pars()->floor);
	mlx()->ceiling_color = rgb_to_int(get_pars()->ceiling);
	/*바닥,천장의 새로운 이미지 생성.*/
	mlx()->floor.img_ptr = mlx_new_image(mlx()->mlx_ptr, WIN_WIDTH, WIN_HEIGHT / 2); 
	mlx()->ceiling.img_ptr = mlx_new_image(mlx()->mlx_ptr, WIN_WIDTH, WIN_HEIGHT / 2); 
	mlx()->floor.data_addr = mlx_get_data_addr(
			mlx()->floor.img_ptr,
			&(mlx()->floor.bits_per_pixel),
			&(mlx()->floor.size_line),
			&(mlx()->floor.endian));
	mlx()->ceiling.data_addr = mlx_get_data_addr(
			mlx()->ceiling.img_ptr,
			&(mlx()->ceiling.bits_per_pixel),
			&(mlx()->ceiling.size_line),
			&(mlx()->ceiling.endian));
	/*이미지에 점 찍어보기.*/
	char	*location_to_put;

	location_to_put = mlx()->floor.data_addr;
	*(location_to_put + mlx()->floor.bits_per_pixel / 8) = mlx()->floor_color;
	*(location_to_put + mlx()->floor.bits_per_pixel / 8) = mlx()->floor_color;
//	location_to_put = mlx()->floor_img;
//	location_to_put[15] = mlx()->floor_color;
	mlx_put_image_to_window(mlx()->mlx_ptr, mlx()->mlx_window, mlx()->floor.img_ptr, 0, 15);
}
