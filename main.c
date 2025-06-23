#include "./parser/pars_pub.h"
#include "./mlx_stuff/mlx_hdler.h"
#include "./minilibx-linux/mlx.h"
#include "./mlx_stuff/algorithm/my_algorithm.h"

int	get_xpm_pixel_color(t_img xpm, t_point pixel)
{
	return(((int *)xpm.data_addr)
			[ (((int)pixel.y * xpm.size_line)/4) +
			(((int)pixel.x * xpm.bits_per_pixel)/32) ]);
}

static void	try_put_xpm(void)
{
	t_img	img = mlx()->xpm_north;
	t_point	point;

	point.x = 0;
	point.y = 0;
	while (point.y < img.xpm_height)
	{
		while (point.x < img.xpm_width)
		{
			put_pixel_to_img(
					&(mlx()->background),
					point.x, point.y,
					get_xpm_pixel_color(img, point)
					);
			point.x++;
		}
		point.x = 0;
		point.y++;
	}
}

extern void	fill_background_color(void);
extern void	draw_minimap();

static void	put_frame(void)
{
	fill_background_color();
	put_background();
	draw_minimap();
	shoot_fov_ray();
	put_minimap();
}

int	main(int argc, char **argv)
{
	pars_init(argc, argv);
	if (pars_file_vld_chk())
	{
		pars_perror();
		pars_destroy();
		return (1);
	}
	else
		pars_cub_file();
	setup_mlx();
	put_frame();
	mlx_loop(mlx()->mlx_ptr);
	mlx_destroy();
	pars_destroy();
}
