#ifndef MLX_HDLER_H
# define MLX_HDLER_H
# define WIN_WIDTH	800
# define WIN_HEIGHT	600
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_img
{
	char	*data_addr; // 이미지의 실제 시작지점.
	void	*img_ptr; // 이미지에 대한 mlx 정보. 직접 다룰 순간은 없는 듯.
	int		bits_per_pixel; // 픽셀당 차지하는 비트. 가로 1칸 당 거리라고 생각.
	int		size_line; // 이미지의 다음 라인으로 넘어가기 위한 비트 수인 듯.
	int		endian; // 일단 우리 환경에서는 0임.
}t_img;

typedef struct s_mlx
{
	void	*mlx_ptr; // mlx_ptr.
	void	*mlx_window;
	t_img	background; // 배경 이미지 정보를 저장합니다.
	int		floor_color; // 바닥 색상.
	int		ceiling_color; // 천장 색상.
}t_mlx;

/*mlx 구조체를 구성합니다.*/
int	setup_mlx(void);

/*mlx 구조체를 리턴합니다.*/
t_mlx	*mlx(void);

/*mlx 구조체를 파괴합니다.*/
void	mlx_destroy();

/*setup_mlx 이후 생성한 배경을 윈도우에 바로 올립니다.*/
void	put_background(void);

#endif
