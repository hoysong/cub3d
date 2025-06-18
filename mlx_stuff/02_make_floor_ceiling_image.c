#include "./mlx_hdler.h"
#include "../minilibx-linux/mlx.h"
#include "../parser/pars_priv.h"
//#include <stdio.h>

int	rgb_to_int(t_rgb rgb)
{
	unsigned int				int_rgb;
	unsigned char	*bit_ptr;

	int_rgb = 0;
	bit_ptr = (unsigned char *)&int_rgb;
	*bit_ptr = rgb.blue;
	bit_ptr++;
	*bit_ptr = rgb.green;
	bit_ptr++;
	*bit_ptr = rgb.red;
	return (int_rgb);
}

void	get_img_data(void)
{
	mlx()->background.data_addr = mlx_get_data_addr(
			mlx()->background.img_ptr,
			&(mlx()->background.bits_per_pixel),
			&(mlx()->background.size_line),
			&(mlx()->background.endian));
//	mlx()->ceiling.data_addr = mlx_get_data_addr(
//			mlx()->ceiling.img_ptr,
//			&(mlx()->ceiling.bits_per_pixel),
//			&(mlx()->ceiling.size_line),
//			&(mlx()->ceiling.endian));
}

void	put_pixel_to_img(int horiz, int vert, int color)
{
	char	*location_to_put;

	location_to_put = mlx()->background.data_addr;
	*(unsigned int *)(location_to_put + ((mlx()->background.bits_per_pixel / 8) * horiz)  + mlx()->background.size_line * vert) = color;
}

void	fill_img_color(void)
{
	int	i;
	int	j;
	i = 0;
	j = 0;
	while (i < WIN_HEIGHT / 2)
	{
		while (j < WIN_WIDTH)
		{
			put_pixel_to_img(j, i, mlx()->ceiling_color);
			j++;
		}
		j = 0;
		i++;
	}
	while (i < WIN_HEIGHT)
	{
		while (j < WIN_WIDTH)
		{
			put_pixel_to_img(j, i, mlx()->floor_color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	make_floor_ceiling_image(void)
{
	/*바닥/천장의 rgb값 구하기.*/
	//printf("%d\n", get_pars()->floor.red);
	mlx()->floor_color = rgb_to_int(get_pars()->floor);
	mlx()->ceiling_color = rgb_to_int(get_pars()->ceiling);
	/*바닥,천장의 새로운 이미지 생성.*/
	mlx()->background.img_ptr = mlx_new_image(mlx()->mlx_ptr, WIN_WIDTH, WIN_HEIGHT); 
	get_img_data();
	/*이미지에 점 찍어보기.*/
	fill_img_color();
	mlx_put_image_to_window(mlx()->mlx_ptr, mlx()->mlx_window, mlx()->background.img_ptr, 0, 0);
}
