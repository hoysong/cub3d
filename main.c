#include "./parser/pars_pub.h"
#include "./mlx_stuff/mlx_hdler.h"
#include "./minilibx-linux/mlx.h"
#include "./mlx_stuff/algorithm/my_algorithm.h"

static void	try_put_xpm(void)
{
	t_img	img = mlx()->xpm_north;
	int	vert = 0;
	int	horiz = 0;

	while (vert < img.xpm_height)
	{
		while (horiz < img.xpm_width)
		{
			put_pixel_to_img(
					&(mlx()->background),
					horiz,
					vert,
					((unsigned int *)img.data_addr)
					[
					((vert * img.size_line)/4) + ((horiz * img.bits_per_pixel)/32)
					]);
			horiz++;
		}
		horiz = 0;
		vert++;
	}
}

static void	put_frame(void)
{
	try_put_xpm();
	put_background();
	//mlx_put_image_to_window(
	//		mlx()->mlx_ptr,
	//		mlx()->mlx_window,
	//		mlx()->xpm_north.img_ptr,
	//		0,
	//		0);
//	shoot_fov_ray();
//	put_minimap();
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
