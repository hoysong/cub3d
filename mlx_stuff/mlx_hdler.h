#ifndef MLX_HDLER_H
# define MLX_HDLER_H
# define WIN_WIDTH	800
# define WIN_HEIGHT	600
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_img
{
	char	*data_addr;
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_window;
	t_img	floor;
	t_img	ceiling;
	int		floor_color;
	int		ceiling_color;
}t_mlx;

/*mlx 구조체를 구성합니다.*/
int	setup_mlx(void);

/*mlx 구조체를 파괴합니다.*/
void	mlx_destroy();

/*mlx 구조체를 리턴합니다.*/
t_mlx	*mlx(void);

#endif
