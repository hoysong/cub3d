/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_pars_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:51:32 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 03:02:42 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars_priv.h"
#include "../pars_pub.h"
#include <stdio.h>
#include <fcntl.h>

inline char	**get_map(void)
{
	return (get_pars()->map);
}

extern char		**gen_map(size_t max_length, size_t max_height);

void	pars_map(void)
{
	t_pars	*pars_struct;

	pars_struct = get_pars();
	pars_struct->map_max_length = get_max_length();
	pars_struct->map_max_height = get_max_height();
	pars_struct->map = gen_map(get_max_length(), get_max_height());
}
