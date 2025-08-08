#ifndef MLX_HDLER_H
# define MLX_HDLER_H
# include "./cub_defs.h"
# include "../parser/pars_priv.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stddef.h>

/*mlx_get_data_addr() 함수를 위해 존재합니다.*/
/*아래의 get_img_data() 참고.*/
typedef struct s_point t_point;

typedef struct s_img
{
	char	*data_addr; // 이미지의 실제 시작지점.
	void	*img_ptr; // 이미지에 대한 mlx 정보. 직접 다룰 순간은 없는 듯.
	int		bits_per_pixel; // 픽셀당 차지하는 비트. 가로 1칸 당 거리라고 생각.
	int		size_line; // 이미지의 다음 라인으로 넘어가기 위한 비트 수인 듯.
	int		endian; // 일단 우리 환경에서는 0임.
	/*xpm datas.*/
	int		xpm_width;
	int		xpm_height;
}t_img;

typedef struct s_mlx
{
	void	*mlx_ptr; // mlx_ptr.
	void	*mlx_window;
	t_img	xpm_north;
	t_img	xpm_south;
	t_img	xpm_west;
	t_img	xpm_east;
	int		ceiling_color; // 천장 색상.
	int		floor_color; // 바닥 색상.
	t_img	background; // 배경 이미지 정보를 저장합니다.
	t_img	minimap; // 미니맵 이미지 정보를 저장합니다.
	int		toggle_mouse;
	int		toggle_minimap;
	/*다른 파라미터용.*/
	t_pars	*pars;
	size_t	minimap_square;
}t_mlx;

/*mlx 구조체를 구성합니다.*/
/*setup t_mlx struct*/
int	setup_mlx(void);

/*mlx 구조체를 리턴합니다.*/
/*It returns t_mlx struct*/
t_mlx	*mlx(void);

/*mlx 구조체를 파괴합니다.*/
/*This Function destroys t_mlx struct.*/
void	mlx_destroy(void);

/*mlx_get_data_addr를 내부적으로 호출합니다.*/
/*this funetion invoke 'mlx_get_data_addr()' internally.*/
void	get_img_data(t_img *img);

/*이미지의 가로[horiz], 세로[vert]위치에 color값을 가진 pixel을 찍습니다.*/
/*put pixel on images hoiz and vert loation.*/
void	put_pixel_to_img(t_img *img, int horiz, int vert, int color);

/*준비된 배경이미지를 윈도우에 바로 올립니다.*/
/*deploy prepared image to window.*/
void	put_background(t_mlx *mlx_strc);

/*미니맵의 그리드 비율을 구합니다.*/
/*reutrns minimap's ratio.*/
size_t	get_minimap_ratio(void);

/*미니맵을 윈도우에 올립니다.*/
/*put_minimap to window.*/
void	put_minimap(t_mlx *mlx_strc);

/*플레이어를 윈도우에 올립니다.*/
/*put_player to window.*/
void	put_player(void);

/*한 프레임을 올립니다.*/
void	put_frame(void);

/*xpm이미지의 픽셀 색상을 가져옵니다.*/
int	get_xpm_pixel_color(t_img xpm, t_point pixel);

#endif
