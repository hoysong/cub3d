#include "../my_libft/libft.h"
#include "./pars_priv.h"
#include <fcntl.h>

static void	del_null_data(void)
{
	t_dnode	*node;

	node = get_pars()->cub_file_list;
	while (node->next_node != NULL)
	{
		node = node->next_node;
		if (node->prev_node->data == NULL)
			destroy_doubly_node(node->prev_node);
	}
	get_pars()->cub_file_list = find_head_dubly(node);
	if (find_tail_dubly(node)->data == NULL)
		destroy_doubly_node(find_tail_dubly(node));
}

void	gnl_cub_file( void )
{
	t_dnode *gnl_node;

	get_pars()->cub_file_list = get_gnl_node(open(get_pars()->argv[1], O_RDONLY));
	del_null_data();
	gnl_node = get_pars()->cub_file_list;
	while (gnl_node)
	{
		*ft_strchr((char *)gnl_node->data, '\n') = '\0';
		gnl_node = gnl_node->next_node;
	}
}
