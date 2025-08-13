/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_make_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 04:03:07 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 04:50:12 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./player.h"
#include "./mlx_hdler.h"
#include "../parser/pars_priv.h"
#include "../parser/pars_pub.h"

static void	minimap_fill_bg(t_mlx *mlx_strc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < MINISIZE)
	{
		while (j < MINISIZE)
		{
			put_pixel_to_img(&(mlx_strc->minimap), j, i, BG_COLOR);
			++j;
		}
		j = 0;
		++i;
	}
}

extern void	minimap_draw_grid_line_length(size_t sq_len, \
		size_t max_height, size_t max_length, t_mlx *mlx_strc);
extern void	minimap_draw_grid_line(size_t sq_len, \
		size_t max_height, size_t max_length, t_mlx *mlx_strc);

static void	fill_wall_color(size_t start_height,
		size_t start_width, size_t sq_len, t_mlx *mlx_strc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < sq_len)
	{
		while (j < sq_len)
		{
			put_pixel_to_img(&(mlx_strc->minimap),
				start_width + j, start_height + i, WALLCOLOR);
			++j;
		}
		j = 0;
		++i;
	}
}

static void	minimap_draw_walls(size_t sq_len, t_mlx *mlx_strc)
{
	char	**map;
	size_t	width;
	size_t	height;

	map = get_map();
	width = 0;
	height = 0;
	while (map[height])
	{
		while (map[height][width])
		{
			if (map[height][width] == '1')
				fill_wall_color(height * sq_len, width * sq_len,
					sq_len, mlx_strc);
			++width;
		}
		width = 0;
		++height;
	}
}

static void	draw_player(float sq_len, t_mlx *mlx_strc, t_player *player)
{
	float	ratio;
	int		x;
	int		y;
	int		x_end;
	int		y_end;

	ratio = player->ratio;
	x = (to_index(player->cord.x) * sq_len) - ratio;
	y = (to_index(player->cord.y) * sq_len) - ratio;
	x_end = (to_index(player->cord.x) * sq_len) + ratio;
	y_end = (to_index(player->cord.y) * sq_len) + ratio;
	while (y <= y_end)
	{
		while (x <= x_end)
		{
			put_pixel_to_img(&(mlx_strc->minimap), x, y, 0xff0000);
			++x;
		}
		x = ((player->cord.x / SIZE_OF_BLOCK) * sq_len) - ratio;
		++y;
	}
}

void	draw_minimap(t_mlx *mlx_strc)
{
	size_t	square_len;

	square_len = mlx_strc->minimap_square;
	minimap_fill_bg(mlx_strc);
	minimap_draw_walls(square_len, mlx_strc);
	minimap_draw_grid_line(
		square_len,
		mlx_strc->pars->map_max_height,
		mlx_strc->pars->map_max_length,
		mlx_strc);
	draw_player(square_len, mlx_strc, player());
}
