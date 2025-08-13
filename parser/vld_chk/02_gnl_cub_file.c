/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_gnl_cub_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 03:22:15 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 03:22:57 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../my_libft/libft.h"
#include "../pars_priv.h"
#include <fcntl.h>

static int	count_nodes(t_dnode *node)
{
	int	i;

	i = 0;
	while (node)
	{
		i++;
		node = node->next_node;
	}
	return (i);
}

static void	del_null_data(void)
{
	t_dnode	*node;

	node = get_pars()->cub_file_list;
	while (node->next_node != NULL)
	{
		node = node->next_node;
		if (node->prev_node->data == NULL)
			destroy_doubly_node(node->prev_node);
	}
	get_pars()->cub_file_list = find_head_dubly(node);
	if (count_nodes(get_pars()->cub_file_list) == 1)
		return ;
	if (find_tail_dubly(node)->data == NULL)
		destroy_doubly_node(find_tail_dubly(node));
}

static void	del_lst_newline_nodes(t_dnode *node)
{
	node = find_tail_dubly(node);
	while (node->prev_node != NULL)
	{
		node = node->prev_node;
		if (*(char *)node->next_node->data == '\n')
			destroy_doubly_node(node->next_node);
		else
			break ;
	}
}

void	gnl_cub_file( void )
{
	t_dnode	*gnl_node;
	int		fd;

	if (get_pars()->pars_errno)
		return ;
	fd = open(get_pars()->argv[1], O_RDONLY);
	get_pars()->cub_file_list = get_gnl_node(fd);
	if (get_pars()->cub_file_list == NULL)
		malloc_fail_perror();
	del_null_data();
	if (count_nodes(get_pars()->cub_file_list) <= 6)
	{
		get_pars()->pars_errno = NEED_MORE_FILE_ARGS;
		return ;
	}
	del_lst_newline_nodes(get_pars()->cub_file_list);
	gnl_node = get_pars()->cub_file_list;
	while (gnl_node)
	{
		*ft_strchr((char *)gnl_node->data, '\n') = '\0';
		gnl_node = gnl_node->next_node;
	}
	close(fd);
}
