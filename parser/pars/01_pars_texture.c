#include "../pars_priv.h"
#include "../../my_libft/libft.h"

//static char	*get_textrue_name(char *texture_line)
//{
//	char	**splits;
//	char	*texture_name;
//
//	splits = ft_split(get_pars()->cub_file_list->data, ' ');
//	if (splits == NULL)
//		malloc_fail_perror();
//	texture_name = ft_strdup(splits[1]);
//	if (texture_name == NULL)
//		malloc_fail_perror();
//	free_splits(splits);
//	return (texture_name);
//}
//
//void	pars_texture(void)
//{
//	get_pars()->north_texture = get_textrue_name((char *)get_pars()->cub_file_list->data);
//	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
//	get_pars()->south_texture = get_textrue_name((char *)get_pars()->cub_file_list->data);
//	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
//	get_pars()->west_texture = get_textrue_name((char *)get_pars()->cub_file_list->data);
//	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
//	get_pars()->east_texture = get_textrue_name((char *)get_pars()->cub_file_list->data);
//	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
//}
