/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slice_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:19:39 by hoysong           #+#    #+#             */
/*   Updated: 2024/12/04 17:32:26 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

extern t_dnode	*slice_init_node(char *str);

void	fill_null_in_dest(char **dest, char *slice_str)
{
	int	slice_len;

	slice_len = ft_strlen(slice_str);
	while (slice_len--)
		*(*dest)++ = '\0';
	return ;
}

t_dnode	*get_sliced_list(char *dest, char *slice_str)
{
	t_dnode	*sliced_node;

	fill_null_in_dest(&dest, slice_str);
	sliced_node = slice_init_node(slice_str);
	sliced_node->next_node = slice_init_node(dest);
	sliced_node->next_node->prev_node = sliced_node;
	return (sliced_node);
}

int	is_thr_same(t_dnode *node, char *slice_str)
{
	t_dnode	*sliced_list;
	char	*dest;

	dest = (char *)node->data;
	if (ft_strlen(dest) == ft_strlen(slice_str)
		&& !ft_strncmp(dest, slice_str, ft_strlen(slice_str)))
	{
		return (0);
	}
	while (*dest)
	{
		if (!ft_strncmp(dest, slice_str, ft_strlen(slice_str)))
		{
			sliced_list = get_sliced_list(dest, slice_str);
			insert_chain(node, sliced_list);
			return (1);
		}
		dest++;
	}
	return (0);
}

void	logic_start(t_dnode *node, char *slice_str)
{
	while (node != NULL)
	{
		if (is_thr_same(node, slice_str))
			node = find_head_dubly(node);
		node = node->next_node;
	}
}

void	free_empty_node(t_dnode *head_node)
{
	t_dnode	*node;

	node = head_node;
	while (node->next_node != NULL)
	{
		if (*(char *)node->next_node->data == '\0')
		{
			head_node = destroy_doubly_node(node->next_node);
			node = find_head_dubly(head_node);
		}
		node = node->next_node;
		if (node == NULL)
			break ;
	}
}
