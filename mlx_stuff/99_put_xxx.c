#include "./mlx_hdler.h"
#include "./algorithm/my_algorithm.h"
#include "../minilibx-linux/mlx.h"

inline void	put_pixel_to_img(t_img *img, int horiz, int vert, int color)
{
	char	*location_to_put;

	location_to_put = img->data_addr;
	*(unsigned int *)
		(location_to_put + ((img->bits_per_pixel / 8) * horiz) + img->size_line * vert) = color;
}

inline void	put_background(void)
{
	mlx_put_image_to_window(mlx()->mlx_ptr, mlx()->mlx_window, mlx()->background.img_ptr, 0, 0);
}

inline void	put_minimap(void)
{
	mlx_put_image_to_window(mlx()->mlx_ptr, mlx()->mlx_window, mlx()->minimap.img_ptr, 0, 0);
}

static int	get_xpm_pixel_color(t_img xpm, t_point pixel)
{
	return(((int *)xpm.data_addr)
			[ (((int)pixel.y * xpm.size_line)/4) +
			(((int)pixel.x * xpm.bits_per_pixel)/32) ]);
}

/*xpm 이미지 올리기 테스트 함수.*/
/*나중에 참고하여 코드 사용하기...*/
void	try_put_xpm(void)
{
	t_img	img = mlx()->xpm_north;
	t_point	point;

	point.x = 0;
	point.y = 0;
	while (point.y < img.xpm_height)
	{
		while (point.x < img.xpm_width)
		{
			put_pixel_to_img(
					&(mlx()->background),
					point.x, point.y,
					get_xpm_pixel_color(img, point)
					);
			point.x++;
		}
		point.x = 0;
		point.y++;
	}
}

extern void	fill_background_color(t_mlx *mlx);
extern void	draw_minimap();

void	put_frame(void)
{
	/*화면 배경 채우기.*/
	fill_background_color(mlx());
	/*미니맵 뼈대 그리기.*/
	if (mlx()->toggle_minimap)
		draw_minimap();
	/*그림들 위에 Ray결과 덮어쓰기.*/
	shoot_fov_ray();
	/*화면 올리기.*/
	put_background();
	/*미니맵 올리기.*/
	if (mlx()->toggle_minimap)
		put_minimap();
}
