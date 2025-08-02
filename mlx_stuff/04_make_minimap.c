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
			put_pixel_to_img(&(mlx_strc->minimap), j, i, BG_Color);
			++j;
		}
		j = 0;
		++i;
	}
}

static void	minimap_draw_grid_line(size_t sq_len, size_t max_height, size_t max_length, t_mlx *mlx_strc)
{
	size_t i = 0;
	size_t j = 0;

	while ((i < (sq_len * max_height)))
	{
		while ((j < (sq_len * max_length)))
		{
			put_pixel_to_img(&(mlx_strc->minimap), j, i, GridColor);
			++j;
		}
		j = 0;
		i += sq_len;
	}
	i = 0;
	j = 0;
	while ((j < (sq_len * max_length)) && j < MINISIZE)
	{
		while ((i < (sq_len * max_height)) && i < MINISIZE)
		{
			put_pixel_to_img(&(mlx_strc->minimap), j, i, GridColor);
			++i;
		}
		i = 0;
		j+=sq_len;
	}
}

static void	fill_wall_color(size_t start_height, size_t start_width, size_t sq_len, t_mlx *mlx_strc)
{
	int	i = 0;
	int	j = 0;

	while (i < sq_len)
	{
		while (j < sq_len)
		{
			put_pixel_to_img(&(mlx_strc->minimap), start_width + j, start_height + i, WallColor);
			++j;
		}
		j = 0;
		++i;
	}
}

static void	minimap_draw_walls(size_t sq_len, t_mlx *mlx_strc)
{
	char	**map = get_map();
	size_t	width = 0;
	size_t	height = 0;

	while (map[height])
	{
		while (map[height][width])
		{
			if (map[height][width] == '1')
				fill_wall_color(height * sq_len, width * sq_len, sq_len, mlx_strc);
			++width;
		}
		width = 0;
		++height;
	}
}

static void	draw_player(float sq_len, t_mlx *mlx_strc, t_player *player)
{
	float	ratio = player->ratio;
	int		x = (MINI_RES(player->cord.x) * sq_len) - ratio;
	int		y = (MINI_RES(player->cord.y) * sq_len) - ratio;
	int		x_end = (MINI_RES(player->cord.x) * sq_len) + ratio;
	int		y_end = (MINI_RES(player->cord.y) * sq_len) + ratio;

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
	size_t	square_len = mlx_strc->minimap_square;

	minimap_fill_bg(mlx_strc);
	minimap_draw_walls(square_len, mlx_strc);
	minimap_draw_grid_line(square_len, mlx_strc->pars->map_max_height, mlx_strc->pars->map_max_length, mlx_strc);
	draw_player(square_len, mlx_strc, player());
}
