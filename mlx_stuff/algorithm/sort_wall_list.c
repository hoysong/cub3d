#include "./wall_lkd_list/wall_lkd_list.h"
#include <stdio.h>

static void	print_tex(t_img *img)
{
	printf("Texture: ");
	if (&(mlx()->xpm_north) == img)
		printf("NORTH\n");
	else if (&(mlx()->xpm_south) == img)
		printf("SOUTH\n");
	else if (&(mlx()->xpm_west) == img)
		printf("WEST\n");
	else if (&(mlx()->xpm_east) == img)
		printf("east\n");
}

static void	print_list(t_wall_node *node)
{
	int	node_num = 0;
	while (node)
	{
		//printf("%d: ", node_num);
		//printf("%p: %f | %f\n", node, node->start_point.y, node->end_point.y);
		//print_tex(node->texture);
		node = node->next;
		node_num++;
	}
}

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

t_wall_node	*go_deeper(t_wall_node *node, int depth)
{
	t_wall_node	*a = node;
	t_wall_node	*b = node->next;
	float		a_val;
	float		b_val;

	//printf("depth: %d\n", depth);
	while (b)
	{

		init_vars(a, b, &a_val, &b_val);
		//printf("diff: %p: %f | %p: %f\n", a, a_val, b, b_val);
		if (a_val < b_val)
		{
			//printf("swap!\n");
			wall_swap_node(a, b);
			//print_list(wall_find_first_node(node));
			//printf("=======deeper!=======\n");
			a = go_deeper(b, depth + 1);
			b = a;
			//printf("out to depth: %d\n", depth);
		}
		b = b->next;
		if (depth == 0 &&
				(a->next != NULL && b == NULL)
				)
		{
			a = a->next;
			b = a;
		}
	}
	return (a);
}

void	sort_wall_list(t_wall_node *node)
{
	//printf("====SORT_START====\n");
	print_list(node);
	go_deeper(node, 0);
	//printf("SORTED!\n");
	node = wall_find_first_node(node);
	print_list(node);
	//printf("\n");
}
