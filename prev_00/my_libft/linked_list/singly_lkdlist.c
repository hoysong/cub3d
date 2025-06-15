/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singly_lkdlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:14:16 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/02 21:40:34 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "lkdlist.h"

/*
	== insert_node ==
	1. description
	add new node between 2 nodes.

	2. return value
	none
*/
void	insert_node(t_node *dest, t_node *new_node)
{
	new_node->next_node = dest->next_node;
	dest->next_node = new_node;
}

/*
   == find_tail_node ==
   1. description
      find last node from src_node.
      copy last_node's address to parameter(t_node **last_node)

   2. return value
      number of nodes
*/
int	find_tail_node(t_node *head, t_node **last_node)
{
	int		count_node;

	*last_node = head;
	count_node = 1;
	while ((*last_node)->next_node != NULL)
	{
		*last_node = (*last_node)->next_node;
		count_node++;
	}
	return (count_node);
}

/*
   == node_init ==
   1. description
      memory allocation to received node.
      initialize 'data' and 'next_node' to zero.

   2. return value
      error code
*/
int	init_node(t_node **node)
{
	*node = malloc(sizeof(t_node));
	if (node == 0)
		return (0);
	(*node)->next_node = 0;
	(*node)->data = 0;
	return (0);
}

/*
   == destroy_node ==
   1. description
      it will destroy the node.
	  it will free node's data if data's address isn't zero.
	  and set node's data address to zero.
	  it will free() data after free() node's data.
   2. return value
      none
*/
void	destroy_node(t_node *node)
{
	if (node->data != 0)
		free(node->data);
	free(node);
}
