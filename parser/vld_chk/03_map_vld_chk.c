/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_map_vld_chk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 03:23:14 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 03:23:29 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../my_libft/libft.h"
#include "../pars_priv.h"
#include <stdio.h>

extern size_t	get_max_length(void);
extern size_t	get_max_height(void);
extern void		copy_str(char *dest, char *src);
extern void		good_map_chk(char **map);

static char	**gen_outline_map(size_t max_length, size_t max_height)
{
	size_t	i;
	char	**map;
	t_dnode	*node;

	i = 0;
	node = get_pars()->cub_file_list;
	map = malloc(sizeof(char *) * (max_height + 2 + 1));
	if (map == NULL)
		malloc_fail_perror();
	map[max_height + 2] = NULL;
	while (i < max_height + 2)
	{
		map[i] = malloc(sizeof(char) * (max_length + 2 + 1));
		if (map[i] == NULL)
			malloc_fail_perror();
		map[i] = ft_memset(map[i], ' ', max_length + 2);
		map[i][max_length + 2] = '\0';
		if (node != NULL && i != 0)
		{
			copy_str((map[i]) + 1, node->data);
			node = node->next_node;
		}
		i++;
	}
	return (map);
}

/*map must not seperated my newline.*/
static int	map_newline_check(t_dnode *node)
{
	while (node)
	{
		if (*(char *)node->data == '\0')
			return (1);
		node = node->next_node;
	}
	return (0);
}

void	map_vld_chk(void)
{
	char	**map;

	if (get_pars()->pars_errno)
		return ;
	if (map_newline_check(get_pars()->cub_file_list))
	{
		get_pars()->pars_errno = MAP_ERR;
	}
	map = gen_outline_map(get_max_length(), get_max_height());
	print_splits(map);
	good_map_chk(map);
	if (get_pars()->pars_errno == 0)
		printf("good map!\n");
	else
		printf("bad map..\n");
	free_splits(map);
}
