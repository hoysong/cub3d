#include "./my_algorithm.h"
#include "../mlx_hdler.h"
#include "../../parser/pars_pub.h"
#include <math.h>
#include <stdio.h>

/*shoot_ray에서 d를 더하게 되는데 부호를 반전시켜 다시 빼도록 만드는 로직.
 * 해당 함수를 들어오기 전에 나눗셈을 통해서 인덱스에 접근하며 검사함.
 * 만약 특정 벽'1'이 포함된 인덱스에 도달하면 해당 로직이 실행됨.
 *
 * index가 바로 직후에 변한 좌표(x or y)를 찾아서 바라보는 방향을 판정냄.
 * 좌표가 감소하다가 혹은 증가하다가 변함을 찾아서 어디서 바라보는지 판정냄.
 * 동서남북 중 벽 블록'1' 기준으로 플레이어의 위치를 동서남북으로 판정냄.
 *
 * 간혹 정확히 45도에서 바라보고, 정확히 코너를 바라보는 ray의 경우,
 * 두 판정이 동시에 존재함.
 * 그래서 나중에 컨트롤 하기 위해 if문을 나눠놓음.
*/

static t_img *get_player_view_texture(t_point point, t_point d)
{
	/*invert sign.*/
	d.x *= -1;
	d.y *= -1;
	if ((int)floor(TO_INDEX(point.x + d.x)) < (int)floor(TO_INDEX(point.x)))
		return (&(mlx()->xpm_west));
	else if ((int)floor(TO_INDEX(point.x + d.x)) > (int)floor(TO_INDEX(point.x)))
		return (&(mlx()->xpm_east));
	else if ((int)floor(TO_INDEX(point.y + d.y)) < (int)floor(TO_INDEX(point.y)))
		return (&(mlx()->xpm_north));
	else if ((int)floor(TO_INDEX(point.y + d.y)) > (int)floor(TO_INDEX(point.y)))
		return (&(mlx()->xpm_south));
	else
		return (&(mlx()->xpm_west));
}

inline int	ray_routine(t_point point, t_point d, void *ray_info)
{
	t_point	floor_pt;

	floor_pt.x = (int)floor(point.x);
	floor_pt.y = (int)floor(point.y);
	put_pixel_to_img(
			&(mlx()->minimap),
			to_minimap_ratio(point).x,
			to_minimap_ratio(point).y,
			FOV_COLOR);
	if (get_map()
			[(int)TO_INDEX(floor_pt.y)]
			[(int)TO_INDEX(floor_pt.x)] == '1')
	{
		((t_ray_info *)ray_info)->texture = get_player_view_texture(point, d);
		((t_ray_info *)ray_info)->ray_hit = point;
		return (1);
	}
	return (0);
}
