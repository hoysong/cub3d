#include "mlx_hdler.h"
#include <stdlib.h>

t_mlx	*set_mlx(t_mlx *mlx)
{
	static t_mlx	*static_mlx;

	if (static_mlx == NULL)
		static_mlx = mlx;
	return (static_mlx);
}

inline t_mlx	*mlx(void)
{
	return (set_mlx(NULL));
}
