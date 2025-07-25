#include "../parser/pars_pub.h"
#include "./player.h"
#include "./mlx_hdler.h"
#include <stdlib.h>
#include <stdio.h>

t_player	*set_player(t_player *player)
{
	static t_player	*static_player;

	if (static_player == NULL)
		static_player = player;
	return (static_player);
}

inline t_player	*player(void)
{
	return (set_player(NULL));
}
extern int	is_player(char c);

static void	get_player_view_degree(int x, int y)
{
	char **map = get_map();
	if (map[y][x] == 'N')
		player()->view_degree = 0;
	else if (map[y][x] == 'S')
		player()->view_degree = 180;
	else
		player()->view_degree = 0;
	if (map[y][x] == 'W')
		player()->view_degree = 0;
	else if (map[y][x] == 'E')
		player()->view_degree = 0;
	else
		player()->view_degree = 0;
}

static void	get_player_view_point(int x, int y)
{
	char **map = get_map();
	if (map[y][x] == 'N')
		player()->view_point.y = player()->cord.y - (float)VIEW_DIST;
	else if (map[y][x] == 'S')
		player()->view_point.y = player()->cord.y + (float)VIEW_DIST;
	else
		player()->view_point.y = player()->cord.y;
	if (map[y][x] == 'W')
		player()->view_point.x = player()->cord.x - (float)VIEW_DIST;
	else if (map[y][x] == 'E')
		player()->view_point.x = player()->cord.x + (float)VIEW_DIST;
	else
		player()->view_point.x = player()->cord.x;
}

static void	get_start_location(float *fx, float *fy)
{
	char	**map = get_map();
	int		x = 0;
	int		y = 0;

	while(map[y])
	{
		while(!is_player(map[y][x]) && map[y][x])
			x++;
		if (is_player(map[y][x]))
			break ;
		x = 0;
		y++;
	}
	/*만약 인덱스가 2,2 라 나온다면, 25,25로 블록의 중앙에 놓아준다.*/
	*fx = ((float)x) * SIZE_OF_BLOCK + (float)SIZE_OF_BLOCK / 2;
	*fy = ((float)y) * SIZE_OF_BLOCK + (float)SIZE_OF_BLOCK / 2;
	get_player_view_point(x, y);
	get_player_view_degree(x, y);
}

void	draw_player(float sq_len, t_mlx *mlx_strc, t_player *player)
{
	float	ratio = player->ratio;
	int		x = (MINI_RES(player->cord.x) * sq_len) - ratio;
	int		y = (MINI_RES(player->cord.y) * sq_len) - ratio;
	int		x_end = (MINI_RES(player->cord.x) * sq_len) + ratio;
	int		y_end = (MINI_RES(player->cord.y) * sq_len) + ratio;

	while (y <= y_end)
	{
		while (x <= x_end)
		{
			put_pixel_to_img(&(mlx_strc->minimap), x, y, 0xff0000);
			x++;
		}
		x = ((player->cord.x / SIZE_OF_BLOCK) * sq_len) - ratio;
		y++;
	}
}

void	player_init(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	set_player(player);
	player->ratio = ((float)get_minimap_ratio() / 3) / 3;
	player->view_point.x = 0;
	player->view_point.y = 0;
	get_start_location(&(player->cord.x), &(player->cord.y));
	player_get_step_point(player);
	printf("player info\n");
	printf("├─Location   : x=%f, y=%f\n", player->cord.x, player->cord.y);
	printf("├─view_point : x=%f, y=%f\n", player->view_point.x, player->view_point.y);
	printf("├─step_point : x=%f, y=%f\n", player->step_point.x, player->step_point.y);
	printf("├─Ratio      : %f\n", player->ratio);
	printf("└─(empty)\n");
}
