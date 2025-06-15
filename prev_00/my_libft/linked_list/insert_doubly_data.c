/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_doubly_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:54:51 by hoysong           #+#    #+#             */
/*   Updated: 2024/10/18 18:44:43 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lkdlist.h"

t_dnode	*insert_data_dubl(t_dnode *doubly_node, void *src)
{
	if (doubly_node->next_node == 0)
	{
		doubly_node->next_node = init_dubl();
		if (doubly_node->next_node == NULL)
			return (0);
		doubly_node->next_node->data = src;
		doubly_node->next_node->prev_node = doubly_node;
		return (doubly_node->next_node);
	}
	else if (doubly_node->prev_node == 0)
	{
		doubly_node->prev_node = init_dubl();
		if (doubly_node->next_node == NULL)
			return (0);
		doubly_node->prev_node->data = src;
		doubly_node->prev_node->next_node = doubly_node;
		return (doubly_node->prev_node);
	}
	return (0);
}
