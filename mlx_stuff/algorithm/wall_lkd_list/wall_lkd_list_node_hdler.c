/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_lkd_list_node_hdler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 06:33:20 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 06:38:06 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_algorithm.h"
#include <stdlib.h>

void	wall_swap_node(t_wall_node *a, t_wall_node *b)
{
	t_wall_node	*a_next;
	t_wall_node	*b_prev;

	a_next = a->next;
	b_prev = b->prev;
	if (a->prev != NULL)
		a->prev->next = b;
	b->prev = a->prev;
	if (b->next != NULL)
		b->next->prev = a;
	a->next = b->next;
	if (a_next == b && b_prev == a)
	{
		a->prev = b;
		b->next = a;
	}
	else
	{
		a->prev = b_prev;
		b->next = a_next;
		a_next->prev = b;
		b_prev->next = a;
	}
}

t_wall_node	*wall_init_node(void)
{
	t_wall_node	*node;

	node = malloc(sizeof(t_wall_node));
	if (node == NULL)
		exit(1);
	node->next = NULL;
	node->prev = NULL;
	node->info = NULL;
	node->texture = NULL;
	node->wall_start_cord.x = 0;
	node->wall_start_cord.y = 0;
	node->wall_end_cord.x = 0;
	node->wall_end_cord.y = 0;
	node->start_degree = 0;
	node->end_degree = 0;
	node->correction_flag = 0;
	return (node);
}

t_wall_node	*wall_find_first_node(t_wall_node *node)
{
	while (node->prev != NULL)
		node = node->prev;
	return (node);
}
