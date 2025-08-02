#include "./mlx_hdler.h"
#include "./algorithm/my_algorithm.h"
#include "../minilibx-linux/mlx.h"

inline void	put_pixel_to_img(t_img *img, int horiz, int vert, int color)
{
	char	*location_to_put;

	location_to_put = img->data_addr;
	*(unsigned int *)
		(
		 location_to_put + ((img->bits_per_pixel >> 3) * horiz) + img->size_line * vert
		 ) = color;
}

inline void	put_background(t_mlx *mlx_strc)
{
	mlx_put_image_to_window(
			mlx_strc->mlx_ptr,
			mlx_strc->mlx_window,
			mlx_strc->background.img_ptr, 0, 0);
}

inline void	put_minimap(t_mlx *mlx_strc)
{
	mlx_put_image_to_window(
			mlx_strc->mlx_ptr,
			mlx_strc->mlx_window,
			mlx_strc->minimap.img_ptr, 0, 0);
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
extern void	draw_minimap(t_mlx *mlx_strc);
extern void	ray_casting(void);

void	put_frame(void)
{
	t_mlx	*mlx_strc = mlx();
	/*화면 배경 채우기.*/
	fill_background_color(mlx_strc);
	/*미니맵 뼈대 그리기.*/
	if (mlx_strc->toggle_minimap)
		draw_minimap(mlx_strc);
	/*배경 위에 Casting결과 덮어쓰기.*/
	ray_casting();
	/*화면 올리기.*/
	put_background(mlx_strc);
	/*미니맵 올리기.*/
	if (mlx_strc->toggle_minimap)
		put_minimap(mlx_strc);
}
