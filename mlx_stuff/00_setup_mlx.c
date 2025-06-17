#include "./mlx_hdler.h"
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>

static t_mlx	*set_mlx(t_mlx *mlx)
{
	static t_mlx	*static_mlx;

	if (static_mlx == NULL)
		static_mlx = mlx;
	return (static_mlx);
}

t_mlx	*mlx(void)
{
	t_mlx *(*get_mlx)(t_mlx *);
	get_mlx = set_mlx;

	return (get_mlx(NULL));
}

void	mlx_destroy()
{
	mlx_destroy_display(mlx()->mlx_ptr);
}

int	setup_mlx(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	set_mlx(mlx);
	return (1);
}
