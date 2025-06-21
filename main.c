#include "./parser/pars_pub.h"
#include "./mlx_stuff/mlx_hdler.h"
#include "./minilibx-linux/mlx.h"
#include "./mlx_stuff/algorithm/my_algorithm.h"

static void	put_frame(void)
{
	put_background();
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
