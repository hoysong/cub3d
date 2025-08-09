#include "../algorithm/wall_lkd_list/wall_lkd_list.h"
#include <stdio.h>

static inline void	init_vars(t_wall_node *a, t_wall_node *b, float	*a_val, float *b_val)
{
	if (a->start_point.y > a->end_point.y)
		*a_val = a->start_point.y;
	else
		*a_val = a->end_point.y;

	if (b->start_point.y > b->end_point.y)
		*b_val = b->start_point.y;
	else
		*b_val = b->end_point.y;

	if (*a_val == *b_val)
	{
		if (a->start_point.y > a->end_point.y)
			*a_val = a->end_point.y;
		else
			*a_val = a->start_point.y;

		if (b->start_point.y > b->end_point.y)
			*b_val = b->end_point.y;
		else
			*b_val = b->start_point.y;
	}
}

static t_wall_node	*go_deeper(t_wall_node *node, int depth)
{
	t_wall_node	*a;
	t_wall_node	*b;
	float		a_val;
	float		b_val;

	a = node;
	b = node->next;
	while (b)
	{
		init_vars(a, b, &a_val, &b_val);
		if (a_val < b_val)
		{
			wall_swap_node(a, b);
			a = go_deeper(b, depth + 1);
			b = a;
		}
		b = b->next;
		if (depth == 0 &&
			(a->next != NULL && b == NULL))
		{
			a = a->next;
			b = a;
		}
	}
	return (a);
}

/*
 * This function exists for wrapping function named 'go_deeper'.
 * go_deeper() function will sort wall list.
 * (cuz the nodes getting closer must be drawn later).
 * go_depper() function will compare two nodes and keep swap until end.
 */
void	sort_wall_list(t_wall_node *node)
{
	go_deeper(node, 0);
}
