/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_lkdlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:54:51 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/29 14:55:36 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lkdlist.h"

t_dnode	*find_head_dubly(t_dnode *dubly_node)
{
	while (dubly_node->prev_node != NULL)
		dubly_node = dubly_node->prev_node;
	return (dubly_node);
}

t_dnode	*find_tail_dubly(t_dnode *dubly_node)
{
	while (dubly_node->next_node != NULL)
		dubly_node = dubly_node->next_node;
	return (dubly_node);
}

void	insert_dubl(t_dnode *dest, t_dnode *new_node)
{
	new_node->next_node = dest->next_node;
	if (dest->next_node != 0)
		new_node->next_node->prev_node = new_node;
	new_node->prev_node = dest;
	dest->next_node = new_node;
}

void	insert_chain(t_dnode *dest, t_dnode *src_node)
{
	t_dnode	*src_head;
	t_dnode	*src_tail;

	src_head = find_head_dubly(src_node);
	src_tail = find_tail_dubly(src_node);
	src_tail->next_node = dest->next_node;
	if (dest->next_node != 0)
		dest->next_node->prev_node = src_tail;
	dest->next_node = src_head;
	src_head->prev_node = dest;
}

t_dnode	*init_dubl(void)
{
	t_dnode	*node;

	node = malloc(sizeof(t_dnode));
	if (node == NULL)
		return (0);
	node->next_node = 0;
	node->prev_node = 0;
	node->data = 0;
	return (node);
}
