/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_surround_chk_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 03:25:21 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 03:30:33 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars_priv.h"
#include <stdio.h>

inline int	is_player(char c)
{
	if (c == 'N'
		|| c == 'S'
		|| c == 'E'
		|| c == 'W')
		return (1);
	return (0);
}

int	is_wall_floor(char c)
{
	if (c == '1' || c == '0')
		return (1);
	return (0);
}

/*check diagonal spaces.*/
/*map must be rectangle.*/
int	diagonal_vld_check(char **map, int i, int j)
{
	if (
		(is_player(map[i - 1][j - 1]) || is_wall_floor(map[i - 1][j - 1])) &&
		(is_player(map[i + 1][j - 1]) || is_wall_floor(map[i + 1][j - 1])) &&
		(is_player(map[i - 1][j + 1]) || is_wall_floor(map[i - 1][j + 1])) &&
		(is_player(map[i + 1][j + 1]) || is_wall_floor(map[i + 1][j + 1]))
		)
	{
		return (1);
	}
	return (0);
}

int	is_surrounded_by_wall_floor(char **map, int i, int j)
{
	if (
		(is_player(map[i - 1][j]) || is_wall_floor(map[i - 1][j])) &&
		(is_player(map[i + 1][j]) || is_wall_floor(map[i + 1][j])) &&
		(is_player(map[i][j - 1]) || is_wall_floor(map[i][j - 1])) &&
		(is_player(map[i][j + 1]) || is_wall_floor(map[i][j + 1])) &&
		diagonal_vld_check(map, i, j)
		)
	{
		return (1);
	}
	return (0);
}
