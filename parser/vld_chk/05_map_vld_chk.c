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
	map[max_height + 2] = NULL;
	while (i < max_height + 2)
	{
		map[i] = malloc(sizeof(char) * (max_length + 2 + 1));
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

void	map_vld_chk(void)
{
	char	**map;

	if (get_pars()->pars_errno)
		return ;
	//get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
	map = gen_outline_map(get_max_length(), get_max_height());
	print_splits(map);
	good_map_chk(map);
	if (get_pars()->pars_errno == 0)
		printf("good map!\n");
	else
		printf("bad map..\n");
	free_splits(map);
}
