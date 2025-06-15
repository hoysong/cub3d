/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_hdler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 07:18:31 by hoysong           #+#    #+#             */
/*   Updated: 2024/10/18 16:09:22 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./libft.h"

void	print_splits(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		ft_printf("%s\n", str[i++]);
	return ;
}

void	free_splits(char **splits)
{
	int	i;

	i = 0;
	while (splits[i] != NULL)
		free(splits[i++]);
	free(splits);
	return ;
}

t_dnode	*make_split_lkd_list(char **argv)
{
	char	**str;
	t_dnode	*split_node;

	split_node = init_dubl();
	if (split_node == NULL)
		return (0);
	while (*argv != NULL)
	{
		str = ft_split(*argv, ' ');
		if (str == NULL)
			return (0);
		split_node = insert_data_dubl(split_node, (void *)str);
		if (split_node == NULL)
			return (0);
		argv++;
	}
	split_node = find_head_dubly(split_node)->next_node;
	free(split_node->prev_node);
	split_node->prev_node = NULL;
	return (split_node);
}

void	free_split_lkd_list(t_dnode *split_node)
{
	split_node = find_head_dubly(split_node);
	while (split_node->next_node != NULL)
	{
		if (split_node->data != NULL)
		{
			free_splits((char **)split_node->data);
			split_node->data = NULL;
		}
		split_node = split_node->next_node;
	}
	free_splits((char **)split_node->data);
	split_node->data = NULL;
	destroy_doubly_list(split_node);
}

void	print_split_lkd_list(t_dnode *split_node)
{
	int	i;

	i = 0;
	split_node = find_head_dubly(split_node);
	while (split_node->next_node != NULL)
	{
		ft_printf("node %d:\n", i++);
		print_splits((char **)split_node->data);
		split_node = split_node->next_node;
	}
	ft_printf("node %d:\n", i++);
	print_splits((char **)split_node->data);
	split_node = split_node->next_node;
}
