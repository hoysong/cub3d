/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_surround_chk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 03:23:41 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 05:12:28 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars_priv.h"
#include <stdio.h>

extern int	is_player(char c);
extern int	is_wall_floor(char c);
extern int	diagonal_vld_check(char **map, int i, int j);
extern int	is_surrounded_by_wall_floor(char **map, int i, int j);

static int	surround_chk(char **map, int i, int j)
{
	if (map[i][j] == ' ' || map[i][j] == '1')
		return (1);
	if ((is_player(map[i][j]) || map[i][j] == '0') &&
		is_surrounded_by_wall_floor(map, i, j)
		)
	{
		return (1);
	}
	return (0);
}

static int	is_both_same(char *tex_1, char *tex_2)
{
	return (!ft_strncmp(tex_1, tex_2, ft_strlen(tex_1) + 1));
}

static int	is_same_texture_files(t_pars *pars)
{
	if (
		is_both_same(pars->north_texture, pars->south_texture)
		|| is_both_same(pars->north_texture, pars->west_texture)
		|| is_both_same(pars->north_texture, pars->east_texture)
		|| is_both_same(pars->south_texture, pars->west_texture)
		|| is_both_same(pars->south_texture, pars->east_texture)
		|| is_both_same(pars->west_texture, pars->east_texture)
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
		get_pars()->pars_errno = MULTIPLE_PLAYER;
	if (is_same_texture_files(get_pars()))
		get_pars()->pars_errno = SAME_TEXTURE;
}
