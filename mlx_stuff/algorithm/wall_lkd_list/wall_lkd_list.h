#ifndef WALL_LKD_LIST_H
# define WALL_LKD_LIST_H
#include "../my_algorithm.h"

/*This function init wall node.*/
t_wall_node	*wall_init_node(void);

/*Find first wall node and retern it.*/
t_wall_node	*wall_find_first_node(t_wall_node *node);

/*Find last wall node and return it.*/
t_wall_node	*wall_find_lst_node(t_wall_node *node);

/*Init list's last node and return initialized node.*/
t_wall_node	*wall_init_last_node(t_wall_node *node);

/*destroy(free) wall list.*/
void		wall_destroy_list(t_wall_node *node);

/*This count nodes.*/
int			wall_count_nodes(t_wall_node *node);

/*This function swap a and b.*/
void		wall_swap_node(t_wall_node *a, t_wall_node *b);

/*Send param node to list's last.*/
void		wall_to_last(t_wall_node *node);

#endif
