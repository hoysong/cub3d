/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_make_floor_ceiling_image.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 03:59:51 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 04:21:15 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (i < HALF_WIN_HEIGHT)
	{
		while (j < HALF_WIN_WIDTH)
		{
			put_pixel_to_img(&(mlx->background), j, i, mlx->ceiling_color);
			put_pixel_to_img(&(mlx->background),
				j + HALF_WIN_WIDTH, i, mlx->ceiling_color);
			put_pixel_to_img(&(mlx->background),
				j, i + HALF_WIN_HEIGHT, mlx->floor_color);
			put_pixel_to_img(&(mlx->background),
				j + HALF_WIN_WIDTH, i + HALF_WIN_HEIGHT,
				mlx->floor_color);
			++j;
		}
		j = 0;
		++i;
	}
}

void	make_background_image(void)
{
	t_mlx	*mlx_struct;

	mlx_struct = mlx();
	mlx_struct->floor_color = rgb_to_int(get_pars()->floor);
	mlx_struct->ceiling_color = rgb_to_int(get_pars()->ceiling);
	mlx_struct->background.img_ptr = mlx_new_image(mlx()->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT);
	get_img_data(&(mlx()->background));
}
