#include "./pars_priv.h"
#include "../my_libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

extern int	count_splits(char **splits);
extern int	file_format_chk(char *format, char *file_name);
extern int	try_open(char *file_name);

static void texture_vld_chk(char *direction, char *texture_line)
{
	char	**buf;

	buf = ft_split(texture_line, ' ');
	if (count_splits(buf) != 2
		|| !file_format_chk(".xpm", buf[1])
		|| !try_open(buf[1])
		|| get_pars()->pars_errno)
	{
		get_pars()->pars_errno = 4;
		free_splits(buf);
		return ;
	}
	free_splits(buf);
	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
}

void	check_xpm_texture_line(void)
{
	texture_vld_chk("NO", get_pars()->cub_file_list->data);
	texture_vld_chk("SO", get_pars()->cub_file_list->data);
	texture_vld_chk("WE", get_pars()->cub_file_list->data);
	texture_vld_chk("EA", get_pars()->cub_file_list->data);
	if (get_pars()->pars_errno)
		printf("bad_texture..\n");
	else
		printf("good texture.\n");
	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
}
