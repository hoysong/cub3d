#ifndef WALL_LKD_LIST_H
# define WALL_LKD_LIST_H

t_wall_node	*wall_init_node(void);
t_wall_node	*wall_find_first_node(t_wall_node *node);
t_wall_node	*wall_find_lst_node(t_wall_node *node);
t_wall_node	*wall_init_last_node(t_wall_node *node);
void		wall_destroy_list(t_wall_node *node);
#endif
