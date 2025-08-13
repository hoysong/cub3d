/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_my_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 04:24:54 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 04:27:33 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}

size_t	get_minimap_ratio(void)
{
	size_t	height;
	size_t	length;
	size_t	square_len;

	height = get_pars()->map_max_height;
	length = get_pars()->map_max_length;
	if (height > length)
		square_len = MINISIZE / height;
	else
		square_len = MINISIZE / length;
	return (square_len);
}

inline int	get_xpm_pixel_color(t_img xpm, t_point pixel)
{
	return (
		((int *)xpm.data_addr)
		[(((int)pixel.y * xpm.size_line) >> 2) + \
		(((int)pixel.x * xpm.bits_per_pixel) >> 5)]);
}
