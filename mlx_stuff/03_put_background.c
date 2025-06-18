#include "./mlx_hdler.h"
#include "../minilibx-linux/mlx.h"

inline void	put_background(void)
{
	/*이미지 화면에 올리기.*/
	mlx_put_image_to_window(mlx()->mlx_ptr, mlx()->mlx_window, mlx()->background.img_ptr, 0, 0);
}
