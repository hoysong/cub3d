/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_gnl_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 00:51:13 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/19 00:57:49 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dnode	*get_gnl_node(int fd)
{
	t_dnode	*node_head;
	t_dnode	*gnl_node;

	gnl_node = init_dubl();
	node_head = gnl_node;
	while (1)
	{
		gnl_node = insert_data_dubl(gnl_node, get_next_line(fd));
		if (gnl_node->data == NULL)
			break ;
	}
	return (node_head);
}
