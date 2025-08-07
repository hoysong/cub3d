#include "./mlx_hdler.h"
#include "../minilibx-linux/mlx.h"
#include "../parser/pars_priv.h"

static int	rgb_to_int(t_rgb rgb)
{
	unsigned int	int_rgb;
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

void	fill_background_color(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < WIN_HEIGHT >> 1)
	{
		while (j < WIN_WIDTH)
		{
			put_pixel_to_img(&(mlx->background), j, i, mlx->ceiling_color);
			put_pixel_to_img(&(mlx->background), j, i + (WIN_HEIGHT >> 1), mlx->floor_color);
			++j;
		}
		j = 0;
		++i;
	}
//	while (i < WIN_HEIGHT)
//	{
//		while (j < WIN_WIDTH)
//		{
//			put_pixel_to_img(&(mlx->background), j, i, mlx->floor_color);
//			++j;
//		}
//		j = 0;
//		++i;
//	}
}

void	make_background_image(void)
{
	/*바닥/천장의 rgb값 구하기.*/
	mlx()->floor_color = rgb_to_int(get_pars()->floor);
	mlx()->ceiling_color = rgb_to_int(get_pars()->ceiling);
	/*바닥,천장의 새로운 이미지 생성.*/
	mlx()->background.img_ptr = mlx_new_image(mlx()->mlx_ptr, WIN_WIDTH, WIN_HEIGHT); 
	get_img_data(&(mlx()->background));
}
