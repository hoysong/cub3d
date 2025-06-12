/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lkdlist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:51:24 by hoysong           #+#    #+#             */
/*   Updated: 2024/12/04 16:20:10 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LKDLIST_H
# define LKDLIST_H
# include <stdlib.h>
/* == Singly_linked_list == */
typedef struct s_node
{
	struct s_node	*next_node;
	void			*data;
}	t_node;

int		init_node(t_node **node);
void	insert_node(t_node *dest, t_node *new_node);
int		find_tail_node(t_node *head, t_node **last_node);
void	destroy_node(t_node *node);

/* == Doubly_linked_list == */
typedef struct s_doubly_node
{
	struct s_doubly_node	*next_node;
	struct s_doubly_node	*prev_node;
	void					*data;
}	t_dnode;

/*
	== init_dubl ==
	1. description
		this function will memory allocate to doubly list's node.
		and also initialize it's data to zero.
		(data means: next_node, prev_node, node's data.)
		(like next_node, prev_node, data).
	2. return value
		memory allocated node
 */
t_dnode	*init_dubl(void);
/*
	1. description
		this function will reutrn head_node
	2. return value
		head_node
 */
t_dnode	*find_head_dubly(t_dnode *doubly_node);
/*
	1. description
		this function will reutrn tail_node
	2. return value
		tail_node
 */
t_dnode	*find_tail_dubly(t_dnode *doubly_node);

/*
	== doubly_node ==
	1. description.
		If doubly_node's next_node is NULL,
		function will init_dubl() to next_node.
		and then, insert src to next_node's data.
		If next_node is not null function will check prev_node.
		If prev_node is null it will init_dubl() prev_node.
		and insert src to prev_node's data
	2. return value
		next_node or prev_node.
		If prev_node and next_node isn't null it will return zero.
 */
t_dnode	*insert_data_dubl(t_dnode *doubly_node, void *src);

void	insert_dubl(t_dnode *dest, t_dnode *new_node);
/*
	1. Description
		This function can insert linked nodes
		in the middle of the doubly linked-list.
		parameter's can be...
		- node in the middle of the doubly linked-list.
		- head or tail node.
		The next node of dest will become src_node's head_node.
		In other words src_node's prev_node become dest_node.
	2. return value
		none
 */
void	insert_chain(t_dnode *dest, t_dnode *linked_node);
/*
	== destroy_next_chain ==
	1. description
		this function destory next chains.
		works for doubly linked list.
		recommand parameter is like node->next_node.
	2. return value
		none
 */
void	destroy_next_chain(t_dnode *doubly_node);
/*
	== destroy_prev_chain ==
	1. description
		this function destory prev chains.
		works for doubly linked list.
		recommand parameter is like node->prev_node.
	2. return value
		none
 */
void	destroy_prev_chain(t_dnode *doubly_node);
/*
	== destroy_doubly_list ==
	1. Description
		This function destroy doubly linked list.
		All the nodes linked with parameter will be freed.
	2. return value
		none
 */
void	destroy_doubly_list(t_dnode *doubly_node);

/*
 *	== destroy_doubly_node ==.
 *	1. Description.
 *		this function destroy dest node 
 *		and if prev or next is exists, link them together.
 *	2. return value.
 *		head_node of the list.
 *		if there is no nodes left, returns NULL.
 */
t_dnode	*destroy_doubly_node(t_dnode *dest);

#endif
