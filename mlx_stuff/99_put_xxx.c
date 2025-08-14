/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_put_xxx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 04:28:04 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 04:30:15 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx_hdler.h"
#include "./algorithm/my_algorithm.h"
#include "../minilibx-linux/mlx.h"

inline void	put_pixel_to_img(t_img *img, int horiz, int vert, int color)
{
	char	*location_to_put;

	location_to_put = img->data_addr;
	*(unsigned int *)
		(
		location_to_put +
		((img->bits_per_pixel >> 3) * horiz) +
		img->size_line * vert
		) = color;
}

inline void	put_background(t_mlx *mlx_strc)
{
	mlx_put_image_to_window(
		mlx_strc->mlx_ptr,
		mlx_strc->mlx_window,
		mlx_strc->background.img_ptr, 0, 0);
}

inline void	put_minimap(t_mlx *mlx_strc)
{
	mlx_put_image_to_window(
		mlx_strc->mlx_ptr,
		mlx_strc->mlx_window,
		mlx_strc->minimap.img_ptr, 0, 0);
}

extern void	fill_background_color(t_mlx *mlx);
extern void	draw_minimap(t_mlx *mlx_strc);
extern void	ray_casting(void);

void	put_frame(void)
{
	t_mlx	*mlx_strc;

	mlx_strc = mlx();
	fill_background_color(mlx_strc);
	if (mlx_strc->toggle_minimap)
		draw_minimap(mlx_strc);
	ray_casting();
	put_background(mlx_strc);
	if (mlx_strc->toggle_minimap)
		put_minimap(mlx_strc);
}
