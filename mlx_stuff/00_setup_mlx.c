#include "../parser/pars_priv.h"
#include "./mlx_hdler.h"
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>

static int destroy_notify_hook(void *hi)
{
	mlx_loop_end(mlx()->mlx_ptr);
	return (0);
}

static int	hook_func(int key_input)
{
	if (key_input == XK_Escape)
		mlx_loop_end(mlx()->mlx_ptr);
	return (0);
}

void	mlx_destroy(void)
{
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->background.img_ptr);
	mlx_destroy_window(mlx()->mlx_ptr, mlx()->mlx_window);
	mlx_destroy_display(mlx()->mlx_ptr);
	free(mlx()->mlx_ptr);
	free(mlx());
}

extern t_mlx	*set_mlx(t_mlx *mlx);
extern void		make_floor_ceiling_image(void);

int	setup_mlx(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	set_mlx(mlx);

	mlx->floor_color = 0;
	mlx->ceiling_color = 0;

	mlx->mlx_ptr = mlx_init();
	mlx->mlx_window = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, get_pars()->argv[1]);
	make_floor_ceiling_image();

	/*ESC hook.*/
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask, hook_func, mlx);
	/*Destroy('x' button in window) hook.*/
	mlx_hook(mlx->mlx_window, DestroyNotify, NoEventMask, destroy_notify_hook, mlx);
	return (1);
}
