/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_pars_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 00:52:00 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 02:50:02 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars_priv.h"
#include <stdlib.h>

static t_pars	*set_pars( t_pars *pars )
{
	static t_pars	*static_pars;

	if (static_pars == NULL)
		static_pars = pars;
	return (static_pars);
}

t_pars	*get_pars( void )
{
	return (set_pars(NULL));
}

void	pars_init(int argc, char **argv)
{
	t_pars	*pars;

	pars = malloc(sizeof(t_pars));
	if (pars == NULL)
		malloc_fail_perror();
	pars->argc = argc;
	pars->argv = argv;
	pars->pars_errno = 0;
	pars->cub_file_list = NULL;
	pars->north_texture = NULL;
	pars->south_texture = NULL;
	pars->west_texture = NULL;
	pars->east_texture = NULL;
	pars->map = NULL;
	pars->map_max_length = 0;
	pars->map_max_height = 0;
	pars->floor_parsed_flag = 0;
	pars->ceiil_parsed_flag = 0;
	set_pars(pars);
}

void	destroy_gnl_list(t_dnode *node)
{
	if (get_pars()->cub_file_list == NULL)
		return ;
	node = find_head_dubly(node);
	while (node->next_node != NULL)
	{
		node = node->next_node;
		destroy_doubly_node(node->prev_node);
	}
	destroy_doubly_node(node);
}

void	pars_destroy( void )
{
	t_pars	*pars;

	pars = get_pars();
	if (pars->pars_errno || pars->pars_errno == 0)
	{
		destroy_gnl_list(pars->cub_file_list);
		free(pars->north_texture);
		free(pars->south_texture);
		free(pars->west_texture);
		free(pars->east_texture);
	}
	if (!pars->pars_errno)
		free_splits(pars->map);
	free(pars);
}
