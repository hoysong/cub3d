/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:25:51 by hoysong           #+#    #+#             */
/*   Updated: 2025/06/13 03:13:29 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

extern void		fill_null_in_dest(char **dest, char *slice_str);
extern t_dnode	*get_sliced_list(char *dest, char *slice_str);
extern int		is_thr_same(t_dnode *node, char *slice_str);
extern void		logic_start(t_dnode *node, char *slice_str);
extern void		free_empty_node(t_dnode *head_node);

void	print_slice_list(t_dnode *node)
{
	int	i;

	i = 1;
	while (node->next_node != NULL)
	{
		ft_printf("%d: %s\n", i++, (char *)node->data);
		node = node->next_node;
	}
	ft_printf("%d: %s\n", i, (char *)node->data);
}

t_dnode	*slice_init_node(char *str)
{
	t_dnode	*node;

	node = init_dubl();
	node->data = ft_strdup(str);
	return (node);
}

t_dnode	*slice(t_dnode *node, char *slice_str)
{
	t_dnode	*head_node;

	head_node = find_head_dubly(node);
	logic_start(head_node, slice_str);
	free_empty_node(head_node);
	if (*(char *)head_node->data == '\0')
	{
		head_node = head_node->next_node;
		destroy_doubly_node(head_node->prev_node);
	}
	return (head_node);
}
