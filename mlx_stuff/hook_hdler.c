#include "../minilibx-linux/mlx.h"
#include "./player.h"

static int destroy_notify_hook(void *hi)
{
	mlx_loop_end(mlx()->mlx_ptr);
	return (0);
}

static int	hook_func(int key_input)
{
	static int	move_tick;

	if (key_input == XK_Escape)
		mlx_loop_end(mlx()->mlx_ptr);
	else if (key_input == XK_p)
	{
		if (mlx()->toggle_mouse)
			mlx()->toggle_mouse = 0;
		else
			mlx()->toggle_mouse = 1;
	}
	else if (key_input == XK_m)
	{
		if (mlx()->toggle_minimap)
			mlx()->toggle_minimap = 0;
		else
			mlx()->toggle_minimap = 1;
	}
	else
	{
		if (move_tick < MOVE_TICK)
		{
			move_tick++;
			return (0);
		}
		if (key_input == XK_w)
			player_move(player(), 0);
		else if (key_input == XK_a)
			player_move(player(), -90);
		else if (key_input == XK_d)
			player_move(player(), 90);
		else if (key_input == XK_s)
			player_move(player(), 180);
		else if (key_input == XK_Left)
			player_rotate(player(), -CAM_ROTATE_ANGLE);
		else if (key_input == XK_Right)
			player_rotate(player(), CAM_ROTATE_ANGLE);
		put_frame();
		move_tick = 0;
	}
	return (0);
}

static int	my_loop_hook(void *mlx)
{
	static int	mouse_tick;
	int	x;
	int	y;

	if (!((t_mlx *)mlx)->toggle_mouse)
		return (0);
	mlx_mouse_get_pos(((t_mlx *)mlx)->mlx_ptr, ((t_mlx *)mlx)->mlx_window, &x, &y);
	if (x != MOUSE_MIDDLE_X)
	{
		if (mouse_tick < MOVE_TICK)
		{
			mouse_tick++;
			return (0);
		}
		if (x < MOUSE_MIDDLE_X)
			player_rotate(player(), -CAM_ROTATE_ANGLE);
		else if (x > MOUSE_MIDDLE_X)
			player_rotate(player(), CAM_ROTATE_ANGLE);
		mlx_mouse_move(
				((t_mlx *)mlx)->mlx_ptr, ((t_mlx *)mlx)->mlx_window,
				WIN_WIDTH / 2, WIN_HEIGHT / 2);
		put_frame();
		mouse_tick = 0;
	}
	return (0);
}

void	setup_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask, hook_func, mlx);
	mlx_hook(mlx->mlx_window, DestroyNotify, NoEventMask, destroy_notify_hook, mlx);
	mlx_loop_hook(mlx->mlx_ptr, my_loop_hook, mlx);
}
