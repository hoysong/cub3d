#include "../minilibx-linux/mlx.h"
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
	else
	{
		mlx_clear_window(mlx()->mlx_ptr, mlx()->mlx_window);
		if (key_input == XK_w)
			player_move(player(), 0);
		else if (key_input == XK_a)
			player_move(player(), -90);
		else if (key_input == XK_d)
			player_move(player(), 90);
		else if (key_input == XK_s)
			player_move(player(), 180);
		put_frame();
	}
	return (0);
}

extern void	put_frame(void);

static int	my_loop_hook(void *mlx)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(((t_mlx *)mlx)->mlx_ptr, ((t_mlx *)mlx)->mlx_window, &x, &y);
	if (x != MOUSE_MIDDLE_X)
	{
		if (x < MOUSE_MIDDLE_X)
			player_rotate(player(), -CAM_ROTATE_ANGLE);
		else if (x > MOUSE_MIDDLE_X)
			player_rotate(player(), CAM_ROTATE_ANGLE);
		mlx_clear_window(((t_mlx *)mlx)->mlx_ptr, ((t_mlx *)mlx)->mlx_window);
		mlx_mouse_move(
				((t_mlx *)mlx)->mlx_ptr, ((t_mlx *)mlx)->mlx_window,
				WIN_WIDTH / 2, WIN_HEIGHT / 2);
		put_frame();
	}
	return (0);
}

void	setup_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask, hook_func, mlx);
	mlx_hook(mlx->mlx_window, DestroyNotify, NoEventMask, destroy_notify_hook, mlx);
	mlx_loop_hook(mlx->mlx_ptr, my_loop_hook, mlx);
}
