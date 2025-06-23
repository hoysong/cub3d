#include "../minilibx-linux/mlx.h"
#include "./algorithm/my_algorithm.h"
#include "./player.h"

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

extern void	put_frame(void);

static int	my_loop_hook(void *mlx)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(((t_mlx *)mlx)->mlx_ptr, ((t_mlx *)mlx)->mlx_window, &x, &y);
	if (x != WIN_WIDTH / 2)
	{
		if (x < WIN_WIDTH / 2)
			player()->view_point =
				rotate_point(player()->cord, player()->view_point, -CAM_ROTATE_ANGLE);
		else if (x > WIN_WIDTH / 2)
			player()->view_point =
				rotate_point(player()->cord, player()->view_point, CAM_ROTATE_ANGLE);
		mlx_clear_window(((t_mlx *)mlx)->mlx_ptr, ((t_mlx *)mlx)->mlx_window);
		mlx_mouse_move(
				((t_mlx *)mlx)->mlx_ptr,
				((t_mlx *)mlx)->mlx_window,
				WIN_WIDTH / 2,
				WIN_HEIGHT / 2
				);
		put_frame();
	}
	return (0);
}

void	setup_hooks(t_mlx *mlx)
{
	/*ESC hook.*/
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask, hook_func, mlx);
	/*Destroy('x' button in window) hook.*/
	mlx_hook(mlx->mlx_window, DestroyNotify, NoEventMask, destroy_notify_hook, mlx);
	mlx_loop_hook(mlx->mlx_ptr, my_loop_hook, mlx);
}

