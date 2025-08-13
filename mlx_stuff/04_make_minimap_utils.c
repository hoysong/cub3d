/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_make_minimap_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 04:14:58 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 04:51:21 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./player.h"
#include "./mlx_hdler.h"
#include "../parser/pars_priv.h"
#include "../parser/pars_pub.h"

void	minimap_draw_grid_line_length(size_t sq_len,
		size_t max_height, size_t max_length, t_mlx *mlx_strc)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((j < (sq_len * max_length)) && j < MINISIZE)
	{
		while ((i < (sq_len * max_height)) && i < MINISIZE)
		{
			put_pixel_to_img(&(mlx_strc->minimap), j, i, GRIDCOLOR);
			++i;
		}
		i = 0;
		j += sq_len;
	}
}

void	minimap_draw_grid_line(size_t sq_len,
		size_t max_height, size_t max_length, t_mlx *mlx_strc)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((i < (sq_len * max_height)))
	{
		while ((j < (sq_len * max_length)))
		{
			put_pixel_to_img(&(mlx_strc->minimap), j, i, GRIDCOLOR);
			++j;
		}
		j = 0;
		i += sq_len;
	}
	minimap_draw_grid_line_length(sq_len, max_height, max_length, mlx_strc);
}
