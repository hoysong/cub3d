/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_setup_mlx_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 03:54:58 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 03:56:13 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./player.h"
#include "./mlx_hdler.h"
#include "../parser/pars_priv.h"
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>

static void	destroy_xpm(t_mlx *mlx)
{
	if (mlx->xpm_north.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->xpm_north.img_ptr);
	if (mlx->xpm_south.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->xpm_south.img_ptr);
	if (mlx->xpm_west.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->xpm_west.img_ptr);
	if (mlx->xpm_east.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->xpm_east.img_ptr);
}

void	mlx_destroy(void)
{
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->minimap.img_ptr);
	destroy_xpm(mlx());
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->background.img_ptr);
	mlx_destroy_window(mlx()->mlx_ptr, mlx()->mlx_window);
	mlx_destroy_display(mlx()->mlx_ptr);
	free(mlx()->mlx_ptr);
	free(mlx());
	free(player());
}
