#include "../my_libft/libft.h"
#include <stdio.h>
#include "./pars_priv.h"

static size_t	get_max_length(void)
{
	t_dnode	*node;
	size_t	len;

	node = get_pars()->cub_file_list;
	len = 0;
	while (node)
	{
		if (ft_strlen((char *)node->data) > len)
			len = ft_strlen((char *)node->data);
		node = node->next_node;
	}
	return (len);
}

static size_t	get_max_height(void)
{
	t_dnode	*node;
	size_t	height;

	node = get_pars()->cub_file_list;
	height = 0;
	while (node)
	{
		node = node->next_node;
		height++;
	}
	return (height);
}

static void	copy_str(char *dest, char *src)
{
	while (*src)
	{
		*dest = *src;
		src++;
		dest++;
	}
}

char	**gen_map(size_t max_length, size_t max_height)
{
	size_t	i;
	char	**map;
	t_dnode	*node;

	i = 0;
	node = get_pars()->cub_file_list;
	map = malloc(sizeof(char *) * (max_height + 1));
	map[max_height] = NULL;
	while (i < max_height)
	{
		map[i] = ft_calloc(max_length, sizeof(char) + 1);
		copy_str(map[i], (char *)node->data);
		node = node->next_node;
		i++;
	}
	return (map);
}

static char	**gen_outline_map(size_t max_length, size_t max_height)
{
	size_t	i;
	char	**map;
	t_dnode	*node;

	i = 0;
	node = get_pars()->cub_file_list;
	map = malloc(sizeof(char *) * (max_height + 2 + 1));
	map[max_height + 2] = NULL;
//	map[i] = malloc(sizeof(char) * (max_length + 2 + 1));
//	map[i] = ft_memset(map[i], ' ', max_length + 2);
//	map[i][max_length + 2] = '\0';
//	i++;

	while (i < max_height + 2)
	{
		map[i] = malloc(sizeof(char) * (max_length + 2 + 1));
		map[i] = ft_memset(map[i], ' ', max_length + 2);
		map[i][max_length + 2] = '\0';
		if (node != NULL && i != 0)
		{
			copy_str((map[i]) + 1, node->data);
			node = node->next_node;
		}
		i++;
	}
	return (map);
}

static int	is_player(char c)
{
	if (c == 'N'
		|| c == 'S'
		|| c == 'E'
		|| c == 'W')
		return (1);
	return (0);
}

static int	is_wall_floor(char c)
{
	if (c == '1' || c == '0')
		return (1);
	return (0);
}

static int	is_map_char(char c)
{
	if (is_player(c) &&
		is_wall_floor(c) &&
		c == ' ')
		return (1);
	return (0);
}

static int	surround_chk(char **map, int i, int j)
{
	if (map[i][j] == ' ' || map[i][j] == '1')
		return (1);
	if (is_player(map[i][j]) &&
		is_wall_floor(map[i - 1][j]) &&
		is_wall_floor(map[i + 1][j]) &&
		is_wall_floor(map[i][j - 1]) &&
		is_wall_floor(map[i][j + 1]))
	{
		return (1);
	}
	else if (map[i][j] == '0' &&
			(is_player(map[i - 1][j]) || is_wall_floor(map[i - 1][j])) &&
			(is_player(map[i + 1][j]) || is_wall_floor(map[i + 1][j])) &&
			(is_player(map[i][j - 1]) || is_wall_floor(map[i][j - 1])) &&
			(is_player(map[i][j + 1]) || is_wall_floor(map[i][j + 1])))
	{
		return (1);
	}
	return (0);
}

static void	good_map_chk(char **map)
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
	if (player_count > 1)
		get_pars()->pars_errno = MULTIPLE_PLAYER;
}

void	map_vld_chk(void)
{
	char	**map;

	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
	map = gen_outline_map(get_max_length(), get_max_height());
	print_splits(map);
//	/*
//	 * 1. 플레이어는 1명이야 한다.
//	 * 2. 바닥의 동서남북 = N,S,E,W,1,0.
//	 * 3. 플레이어의 동서남북 = 1,0.
//	 */
	good_map_chk(map);
	if (get_pars()->pars_errno == 0)
		printf("goodmap!\n");
	free_splits(map);
}
