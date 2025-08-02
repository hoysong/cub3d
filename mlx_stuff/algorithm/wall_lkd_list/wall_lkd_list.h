#ifndef WALL_LKD_LIST_H
# define WALL_LKD_LIST_H
#include "../my_algorithm.h"

t_wall_node	*wall_init_node(void);
t_wall_node	*wall_find_first_node(t_wall_node *node);
t_wall_node	*wall_find_lst_node(t_wall_node *node);
t_wall_node	*wall_init_last_node(t_wall_node *node);
void		wall_destroy_list(t_wall_node *node);
int			wall_count_nodes(t_wall_node *node);
void		wall_swap_node(t_wall_node *a, t_wall_node *b);

#endif
