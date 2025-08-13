/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_hdler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 04:35:28 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 04:39:37 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "./player.h"

extern int	destroy_notify_hook(void *hi);

/*To toggle mouse mode or minimap.*/
static void	map_mouse_hdler(int key_input)
{
	if (key_input == XK_p)
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
}

static void	player_hdler(int key_input)
{
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
}

static int	hook_func(int key_input)
{
	if (key_input == XK_Escape)
		mlx_loop_end(mlx()->mlx_ptr);
	map_mouse_hdler(key_input);
	player_hdler(key_input);
	put_frame();
	return (0);
}

static int	my_loop_hook(void *mlx)
{
	int	x;
	int	y;

	if (!((t_mlx *)mlx)->toggle_mouse)
		return (0);
	mlx_mouse_get_pos(((t_mlx *)mlx)->mlx_ptr,
		((t_mlx *)mlx)->mlx_window, &x, &y);
	if (x != HALF_WIN_WIDTH)
	{
		if (x < HALF_WIN_WIDTH)
			player_rotate(player(), -CAM_ROTATE_ANGLE);
		else if (x > HALF_WIN_WIDTH)
			player_rotate(player(), CAM_ROTATE_ANGLE);
		mlx_mouse_move(
			((t_mlx *)mlx)->mlx_ptr, ((t_mlx *)mlx)->mlx_window,
			HALF_WIN_WIDTH, HALF_WIN_HEIGHT);
		put_frame();
	}
	return (0);
}

void	setup_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask, hook_func, mlx);
	mlx_hook(mlx->mlx_window,
		DestroyNotify, NoEventMask, destroy_notify_hook, mlx);
	mlx_loop_hook(mlx->mlx_ptr, my_loop_hook, mlx);
}
