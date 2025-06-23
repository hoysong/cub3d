#include "./player.h"
#include "./mlx_hdler.h"
#include "../parser/pars_priv.h"
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>

void	mlx_destroy(void)
{
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->minimap.img_ptr);
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->xpm_north.img_ptr);
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->xpm_south.img_ptr);
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->xpm_west.img_ptr);
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->xpm_east.img_ptr);
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->background.img_ptr);
	mlx_destroy_window(mlx()->mlx_ptr, mlx()->mlx_window);
	mlx_destroy_display(mlx()->mlx_ptr);
	free(mlx()->mlx_ptr);
	free(mlx());
	/*free_player*/
	free(player());
}

static void	get_xpm_data(t_img *xpm, char *filename)
{
	xpm->img_ptr = mlx_xpm_file_to_image(
			mlx()->mlx_ptr,
			filename,
			&(xpm->xpm_width),
			&(xpm->xpm_height));
	get_img_data(xpm);
}

void	get_textures(void)
{
	get_xpm_data(&(mlx()->xpm_north), get_pars()->north_texture);
	get_xpm_data(&(mlx()->xpm_south), get_pars()->south_texture);
	get_xpm_data(&(mlx()->xpm_west), get_pars()->west_texture);
	get_xpm_data(&(mlx()->xpm_east), get_pars()->east_texture);
}

extern void	put_frame(void);

static int destroy_notify_hook(void *hi)
{
	mlx_loop_end(mlx()->mlx_ptr);
	return (0);
}

static int	hook_func(int key_input)
{
	if (key_input == XK_Escape)
		mlx_loop_end(mlx()->mlx_ptr);
	else if (key_input == XK_a)
	{
		mlx_clear_window(mlx()->mlx_ptr, mlx()->mlx_window);
		put_frame();
	}
	else if (key_input == XK_d)
	{
		mlx_clear_window(mlx()->mlx_ptr, mlx()->mlx_window);
		put_frame();
	}
	return (0);
}

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
	mlx_mouse_hide(mlx->mlx_ptr, mlx->mlx_window);
	/*ESC hook.*/
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask, hook_func, mlx);
	/*Destroy('x' button in window) hook.*/
	mlx_hook(mlx->mlx_window, DestroyNotify, NoEventMask, destroy_notify_hook, mlx);
	mlx_loop_hook(mlx->mlx_ptr, my_loop_hook, mlx);
}

extern t_mlx	*set_mlx(t_mlx *mlx);
extern void		make_background_image(void);
extern void		make_minimap(void);

int	setup_mlx(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	set_mlx(mlx);
	mlx->floor_color = 0;
	mlx->ceiling_color = 0;
	mlx->mlx_ptr = mlx_init();
	player_init();
	make_background_image();
	get_textures();
	make_minimap();
	mlx->mlx_window = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, get_pars()->argv[1]);
	setup_hooks(mlx);
	return (1);
}
