#include "../pars_priv.h"
#include "../../my_libft/libft.h"

static t_rgb	get_rgb(void)
{
	char	**splits;
	char	**rgb_splits;
	t_rgb	rgb;

	splits = ft_split(get_pars()->cub_file_list->data, ' ');
	rgb_splits = ft_split(splits[1], ',');
	rgb.red = ft_atoi(rgb_splits[0]);
	rgb.green = ft_atoi(rgb_splits[1]);
	rgb.blue = ft_atoi(rgb_splits[2]);
	free_splits(splits);
	free_splits(rgb_splits);
	return (rgb);
}

void	pars_floor_ceiling(void)
{
	get_pars()->floor = get_rgb();
	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
	get_pars()->ceiling = get_rgb();
	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
}
