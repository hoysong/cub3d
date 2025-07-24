#include "./wall_lkd_list/wall_lkd_list.h"

static inline int	try_sort(t_wall_node *node)
{
	t_wall_node	*a = node;
	t_wall_node	*b = node;
	while (node)
	{
		node = node->next;
	}
	if (a->prev == NULL && b->next == NULL)
		return (1);
	else
		return (0);
}

void	sort_wall_list(t_wall_node *node)
{
	while (!try_sort(node))
	{
	}
}
