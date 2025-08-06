#include "../pars_priv.h"


inline int	is_player(char c)
{
	if (c == 'N'
		|| c == 'S'
		|| c == 'E'
		|| c == 'W')
		return (1);
	return (0);
}

static inline int	is_wall_floor(char c)
{
	if (c == '1' || c == '0')
		return (1);
	return (0);
}

/*check diagonal spaces.*/
/*map must be rectangle.*/
static int	diagonal_vld_check(char **map, int i, int j)
{
	if (
		map[i - 1][j - 1] == ' ' ||
		map[i - 1][j + 1] == ' ' ||
		map[i + 1][j - 1] == ' ' ||
		map[i + 1][j + 1] == ' '
		)
	{
		return (0);
	}
	return (1);
}

static int	is_surrounded_by_wall_floor(char **map, int i, int j)
{
	if (
		map[i - 1][j - 1] != ' ' &&
		map[i - 1][j + 1] != ' ' &&
		map[i + 1][j - 1] != ' ' &&
		map[i + 1][j + 1] != ' ' &&
		diagonal_vld_check(map, i, j)
		//is_wall_floor(map[i - 1][j]) &&
		//is_wall_floor(map[i + 1][j]) &&
		//is_wall_floor(map[i][j - 1]) &&
		//is_wall_floor(map[i][j + 1])
		)
	{
		return (1);
	}
	return (0);
}

static int	surround_chk(char **map, int i, int j)
{
	if (map[i][j] == ' ' || map[i][j] == '1')
		return (1);
	if (is_player(map[i][j]) &&
		is_surrounded_by_wall_floor(map, i, j)
//		is_surrounded_by_wall_floor(map, i, j) &&
//		diagonal_vld_check(map, i, j)
		)
	{
		return (1);
	}
	else if (map[i][j] == '0' &&
			is_surrounded_by_wall_floor(map, i, j)
//			(is_player(map[i - 1][j]) || is_wall_floor(map[i - 1][j])) &&
//			(is_player(map[i + 1][j]) || is_wall_floor(map[i + 1][j])) &&
//			(is_player(map[i][j - 1]) || is_wall_floor(map[i][j - 1])) &&
//			(is_player(map[i][j + 1]) || is_wall_floor(map[i][j + 1])) &&
//			diagonal_vld_check(map, i, j)
			)
	{
		return (1);
	}
	return (0);
}

void	good_map_chk(char **map)
{
	int	i;
	int	j;
	int	player_count;

	i = 1;
	j = 1;
	player_count = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (!surround_chk(map, i, j))
				get_pars()->pars_errno = MAP_ERR;
			if (is_player(map[i][j]))
				player_count++;
			j++;
		}
		j = 1;
		i++;
	}
	if (player_count != 1)
		get_pars()->pars_errno = 1;
}
