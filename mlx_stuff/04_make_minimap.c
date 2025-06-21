#include "./mlx_hdler.h"
#include "../parser/pars_priv.h"
#include "../parser/pars_pub.h"
#include "../minilibx-linux/mlx.h"
#include "./player.h"
#include "./algorithm/my_algorithm.h"

extern int	rgb_to_int(t_rgb rgb);

static void	fill_minimap_bg()
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < MINISIZE)
	{
		while (j < MINISIZE)
		{
			put_pixel_to_img(&(mlx()->minimap), j, i, BG_Color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	make_minimap_img(void)
{
	mlx()->minimap.img_ptr = mlx_new_image(mlx()->mlx_ptr, MINISIZE, MINISIZE);
	get_img_data(&(mlx()->minimap));
}

static void	draw_grid_line(size_t sq_len, size_t max_height, size_t max_length)
{
	size_t i = 0;
	size_t j = 0;

	while ((i < (sq_len * max_height)))
	{
		while ((j < (sq_len * max_length)))
		{
			put_pixel_to_img(&(mlx()->minimap), j, i, GridColor);
			j++;
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
			put_pixel_to_img(&(mlx()->minimap), j, i, GridColor);
			i++;
		}
		i = 0;
		j+=sq_len;
	}
}

static void	fill_grid(size_t start_height, size_t start_width, size_t sq_len)
{
	int	i = 0;
	int	j = 0;

	while (i < sq_len)
	{
		while (j < sq_len)
		{
			put_pixel_to_img(&(mlx()->minimap), start_width + j, start_height + i, WallColor);
			j++;
		}
		j = 0;
		i++;
	}
}

static void	fill_minimap_grid(size_t sq_len)
{
	char	**map = get_map();
	size_t	width = 0;
	size_t	height = 0;

	while (map[height])
	{
		while (map[height][width])
		{
			if (map[height][width] == '1')
				fill_grid(height * sq_len, width * sq_len, sq_len);
			width++;
		}
		width = 0;
		height++;
	}
}

extern void	draw_player(float sq_len);

void	draw_minimap()
{
	size_t	square_len = get_minimap_ratio();

	fill_minimap_bg();
	fill_minimap_grid(square_len);
	draw_grid_line(square_len, get_max_height(), get_max_length());
	draw_player(square_len);
}

/*test functions.*/
extern void	draw_test_line(void);
extern void	get_dot(t_point me, t_point vp, float degree);

void	make_minimap(void)
{
	make_minimap_img();
	draw_minimap();
//	draw_test_line();

	/*test...*/
	int i = 1;

	while (i < 30)
	{
		get_dot(player()->cord, player()->view_point, i);
		i++;
	}
}
