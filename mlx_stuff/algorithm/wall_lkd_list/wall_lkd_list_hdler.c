/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_lkd_list_hdler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 06:29:33 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 06:39:46 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_algorithm.h"
#include <stdlib.h>

extern void			wall_swap_node(t_wall_node *a, t_wall_node *b);
extern t_wall_node	*wall_init_node(void);
extern t_wall_node	*wall_find_first_node(t_wall_node *node);

/*returns last node.*/
t_wall_node	*wall_find_lst_node(t_wall_node *node)
{
	while (node->next != NULL)
		node = node->next;
	return (node);
}

/*this will init last node of list and return it.*/
t_wall_node	*wall_init_last_node(t_wall_node *node)
{
	node = wall_find_lst_node(node);
	node->next = wall_init_node();
	node->next->prev = node;
	return (node->next);
}

void	wall_destroy_list(t_wall_node *node)
{
	node = wall_find_lst_node(node);
	while (node->prev != NULL)
	{
		node = node->prev;
		free(node->next);
	}
	free(node);
}

int	wall_count_nodes(t_wall_node *node)
{
	int	i;

	i = 0;
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}

void	wall_to_last(t_wall_node *node)
{
	t_wall_node	*lst_node;

	lst_node = wall_find_lst_node(node);
	if (node == lst_node)
		return ;
	node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	lst_node->next = node;
	node->prev = lst_node;
	node->next = NULL;
}
