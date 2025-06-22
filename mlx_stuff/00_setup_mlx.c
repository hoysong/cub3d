#include "./player.h"
#include "./mlx_hdler.h"
#include "../parser/pars_priv.h"
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
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->minimap.img_ptr);
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->xpm_north.xpm_ptr);
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->xpm_south.xpm_ptr);
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->xpm_west.xpm_ptr);
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->xpm_east.xpm_ptr);
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->background.img_ptr);
	mlx_destroy_window(mlx()->mlx_ptr, mlx()->mlx_window);
	mlx_destroy_display(mlx()->mlx_ptr);
	free(mlx()->mlx_ptr);
	free(mlx());
	/*free_player*/
	free(player());
}

static t_texture	get_xpm_data(t_texture tex, char *file_name)
{
	tex.xpm_ptr = mlx_xpm_file_to_image(mlx()->mlx_ptr, file_name, &(tex.width), &(tex.height));
	return (tex);
}

void	get_textures(void)
{
	mlx()->xpm_north = get_xpm_data(mlx()->xpm_east, get_pars()->north_texture);
	mlx()->xpm_south = get_xpm_data(mlx()->xpm_east, get_pars()->south_texture);
	mlx()->xpm_west = get_xpm_data(mlx()->xpm_east, get_pars()->west_texture);
	mlx()->xpm_east = get_xpm_data(mlx()->xpm_east, get_pars()->east_texture);
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
	/*ESC hook.*/
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask, hook_func, mlx);
	/*Destroy('x' button in window) hook.*/
	mlx_hook(mlx->mlx_window, DestroyNotify, NoEventMask, destroy_notify_hook, mlx);
	return (1);
}
