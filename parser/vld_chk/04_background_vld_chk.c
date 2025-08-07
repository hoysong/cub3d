//#include "../pars_priv.h"
//#include "../../my_libft/libft.h"
//#include <fcntl.h>
//#include <stdio.h>

//extern int	count_splits(char **splits);
//
//static int	color_vld_chk(char **rgb)
//{
//	while (*rgb)
//	{
//		if (!ft_is_str_digit(*rgb)
//			|| ft_strlen(*rgb) > 3
//			|| !(ft_atoi(*rgb) >= 0 && ft_atoi(*rgb) <= 255))
//			return (0);
//		rgb++;
//	}
//	return (1);
//}
//
//static void	bg_color_vld_chk(char *floor_or_ceiling, char *bg_line)
//{
//	char	**splits;
//	char	**rgb;
//
//	splits = ft_split(bg_line, ' ');
//	if (count_splits(splits) != 2
//		|| ft_strncmp(splits[0], floor_or_ceiling, 2)
//		|| get_pars()->pars_errno)
//	{
//		get_pars()->pars_errno = 5;
//		free_splits(splits);
//		return ;
//	}
//
//	rgb = ft_split(splits[1], ',');
//	free_splits(splits);
//	if (count_splits(rgb) != 3
//		|| !color_vld_chk(rgb)
//		|| get_pars()->pars_errno)
//	{
//		get_pars()->pars_errno = 5;
//		free_splits(rgb);
//		return ;
//	}
//	free_splits(rgb);
//	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
//}
//
//void	background_vld_chk(void)
//{
//	if (get_pars()->pars_errno)
//		return ;
//	bg_color_vld_chk("F", get_pars()->cub_file_list->data);
//	bg_color_vld_chk("C", get_pars()->cub_file_list->data);
//	if (get_pars()->pars_errno)
//		printf("bad_background..\n");
//	else
//		printf("good background!\n");
//}
