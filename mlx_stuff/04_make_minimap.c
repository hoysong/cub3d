#include "./mlx_hdler.h"
#include "../parser/pars_priv.h"
#include "../minilibx-linux/mlx.h"

extern int	rgb_to_int(t_rgb rgb);

static void	fill_minimap(int white)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < MINISIZE)
	{
		while (j < MINISIZE)
		{
			put_pixel_to_img(&(mlx()->minimap), j, i, white);
			j++;
		}
		j = 0;
		i++;
	}
}

void	make_minimap(void)
{
	t_rgb	white;

	white.red = 255;
	white.green = 255;
	white.blue = 255;
	mlx()->minimap.img_ptr = mlx_new_image(mlx()->mlx_ptr, MINISIZE, MINISIZE);
	get_img_data(&(mlx()->minimap));
	fill_minimap(rgb_to_int(white));
}
