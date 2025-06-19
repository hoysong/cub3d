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

static void	get_start_location(float *fx, float *fy)
{
	char	**map = get_map();
	int		x = 0;
	int		y = 0;

	while(map[y])
	{
		while(map[y][x] != 'N' && map[y][x])
			x++;
		if (map[y][x] == 'N')
			break ;
		x = 0;
		y++;
	}
	*fx = ((float)x) + 0.5f;
	*fy = ((float)y) + 0.5f;
}

void	draw_player(float sq_len)
{
	int	x = (player()->x * sq_len) - ((sq_len / 2)/2);
	int	y = (player()->y * sq_len) - ((sq_len / 2)/2);
	int	x_end = (player()->x * sq_len) + ((sq_len / 2)/2);
	int	y_end = (player()->y * sq_len) + ((sq_len / 2)/2);

	printf("Player square size\n");
	printf("    x: %d,     y: %d\n", x, y);
	printf("x_end: %d, y_end: %d\n", x_end, y_end);
	while (y <= y_end)
	{
		while (x <= x_end)
		{
			put_pixel_to_img(&(mlx()->minimap), x, y, 0xff0000);
			x++;
		}
		x = (player()->x * sq_len) - ((sq_len / 2)/2);
		y++;
	}
}

void	player_init(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	set_player(player);
	player->degree = 0;
	get_start_location(&(player->x), &(player->y));
	printf("player: x=%f, y=%f\n", player->x, player->y);
}
