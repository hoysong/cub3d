#include "./player.h"
#include "./mlx_hdler.h"
#include "../parser/pars_priv.h"
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>

/*this function free xpm textures.*/
static void	destroy_xpm(t_mlx *mlx)
{
	if (mlx->xpm_north.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->xpm_north.img_ptr);
	if (mlx->xpm_south.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->xpm_south.img_ptr);
	if (mlx->xpm_west.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->xpm_west.img_ptr);
	if (mlx->xpm_east.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->xpm_east.img_ptr);
}

void	mlx_destroy(void)
{
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->minimap.img_ptr);
	destroy_xpm(mlx());
	mlx_destroy_image(mlx()->mlx_ptr, mlx()->background.img_ptr);
	mlx_destroy_window(mlx()->mlx_ptr, mlx()->mlx_window);
	mlx_destroy_display(mlx()->mlx_ptr);
	free(mlx()->mlx_ptr);
	free(mlx());
	free(player());
}

static void	get_xpm_data(t_img *xpm, char *filename)
{
	xpm->img_ptr = mlx_xpm_file_to_image(
			mlx()->mlx_ptr,
			filename,
			&(xpm->xpm_width),
			&(xpm->xpm_height));
	/*wrong xpm file is here..*/
	if (xpm->img_ptr == NULL)
		return ;
	get_img_data(xpm);
}

static void	get_textures(void)
{
	get_xpm_data(&(mlx()->xpm_north), get_pars()->north_texture);
	get_xpm_data(&(mlx()->xpm_south), get_pars()->south_texture);
	get_xpm_data(&(mlx()->xpm_west), get_pars()->west_texture);
	get_xpm_data(&(mlx()->xpm_east), get_pars()->east_texture);
}

extern t_mlx	*set_mlx(t_mlx *mlx);
extern void		make_background_image(void);
extern void		setup_hooks(t_mlx *mlx);

void	make_minimap_image(void)
{
	mlx()->minimap.img_ptr = mlx_new_image(mlx()->mlx_ptr, MINISIZE, MINISIZE);
	get_img_data(&(mlx()->minimap));
}

int	setup_mlx(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	set_mlx(mlx);
	mlx->floor_color = 0;
	mlx->ceiling_color = 0;
	mlx->toggle_minimap = 0;
	mlx->toggle_mouse = 0;
	mlx->mlx_ptr = mlx_init();
	mlx->pars = get_pars();
	mlx->minimap_square = get_minimap_ratio();
	player_init();
	make_background_image();
	get_textures();
	make_minimap_image();
	mlx->mlx_window = mlx_new_window(
			mlx->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT,
			get_pars()->argv[1]);
	if (
			mlx->xpm_north.img_ptr == NULL
			|| mlx->xpm_south.img_ptr == NULL
			|| mlx->xpm_west.img_ptr == NULL
			|| mlx->xpm_east.img_ptr == NULL
			)
	{
		return (1);
	}
	setup_hooks(mlx);
	return (0);
}
