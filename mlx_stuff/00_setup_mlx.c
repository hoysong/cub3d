#include "../parser/pars_priv.h"
#include "../parser/pars_pub.h"
#include "./mlx_hdler.h"
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>

static int	hook_func(int key_input)
{
	if (key_input == XK_Escape)
	{
		mlx_destroy();
		pars_destroy();
		exit(0);
	}
	return (0);
}

static t_mlx	*set_mlx(t_mlx *mlx)
{
	static t_mlx	*static_mlx;

	if (static_mlx == NULL)
		static_mlx = mlx;
	return (static_mlx);
}

t_mlx	*mlx(void)
{
	t_mlx	*(*get_mlx)(t_mlx *);

	get_mlx = set_mlx;
	return (get_mlx(NULL));
}

void	mlx_destroy(void)
{
	mlx_destroy_window(mlx()->mlx_ptr, mlx()->mlx_window);
	mlx_destroy_display(mlx()->mlx_ptr);
	free(mlx()->mlx_ptr);
	free(mlx());
}

int	setup_mlx(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));

	mlx->mlx_ptr = mlx_init();
	mlx->mlx_window = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, get_pars()->argv[1]);
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask, hook_func, mlx);

	set_mlx(mlx);
	return (1);
}
