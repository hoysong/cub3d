/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_lkdlist_destroy.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:54:51 by hoysong           #+#    #+#             */
/*   Updated: 2024/12/04 16:19:38 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lkdlist.h"

t_dnode	*destroy_doubly_node(t_dnode *dest)
{
	t_dnode	*dest_prev;
	t_dnode	*dest_next;

	dest_next = dest->next_node;
	dest_prev = dest->prev_node;
	free(dest->data);
	free(dest);
	if (dest_next != NULL)
		dest_next->prev_node = dest_prev;
	if (dest_prev != NULL)
		dest_prev->next_node = dest_next;
	if (dest_next != NULL)
		return (find_head_dubly(dest_next));
	else if (dest_prev != NULL)
		return (find_head_dubly(dest_prev));
	return (NULL);
}

void	destroy_next_chain(t_dnode *doubly_node)
{
	if (doubly_node == 0)
		return ;
	while (doubly_node->next_node != 0)
	{
		doubly_node = doubly_node->next_node;
		if (doubly_node->prev_node->data != 0)
			free(doubly_node->prev_node->data);
		free(doubly_node->prev_node);
	}
	if (doubly_node->data != 0)
		free(doubly_node->data);
	free(doubly_node);
}

void	destroy_prev_chain(t_dnode *doubly_node)
{
	if (doubly_node == 0)
		return ;
	while (doubly_node->prev_node != 0)
	{
		doubly_node = doubly_node->prev_node;
		if (doubly_node->next_node->data != 0)
			free(doubly_node->next_node->data);
		free(doubly_node->next_node);
	}
	if (doubly_node->data != 0)
		free(doubly_node->data);
	free(doubly_node);
}

void	destroy_doubly_list(t_dnode *doubly_node)
{
	t_dnode	*prev;
	t_dnode	*next;

	prev = doubly_node->prev_node;
	next = doubly_node->next_node;
	if (doubly_node->data != 0)
		free(doubly_node->data);
	free(doubly_node);
	if (next != 0 && prev != 0)
	{
		while (prev->prev_node != 0 && next->next_node != 0)
		{
			prev = prev->prev_node;
			if (prev->next_node->data != 0)
				free(prev->next_node->data);
			free(prev->next_node);
			next = next->next_node;
			if (next->prev_node->data != 0)
				free(next->prev_node->data);
			free(next->prev_node);
		}
	}
	destroy_prev_chain(prev);
	destroy_next_chain(next);
}
