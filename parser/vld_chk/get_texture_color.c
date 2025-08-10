#include "../pars_priv.h"
#include "../../my_libft/libft.h"

char	*get_textrue_name(char *texture_line)
{
	char	**splits;
	char	*texture_name;

	splits = ft_split(texture_line, ' ');
	if (splits == NULL)
		malloc_fail_perror();
	texture_name = ft_strdup(splits[1]);
	if (texture_name == NULL)
		malloc_fail_perror();
	free_splits(splits);
	return (texture_name);
}

static t_rgb	get_color(char **rgb_splits)
{
	t_rgb rgb;

	rgb.red = ft_atoi(rgb_splits[0]);
	rgb.green = ft_atoi(rgb_splits[1]);
	rgb.blue = ft_atoi(rgb_splits[2]);
	return (rgb);
}

t_rgb	get_rgb(char *str, char type)
{
	char	**splits;
	char	**rgb_splits;
	t_rgb	rgb;

	splits = ft_split(str, ' ');
	if (splits == NULL)
		malloc_fail_perror();
	rgb_splits = ft_split(splits[1], ',');
	if (rgb_splits == NULL)
		malloc_fail_perror();
	rgb = get_color(rgb_splits);
	free_splits(splits);
	free_splits(rgb_splits);
	if (type == 'F')
		get_pars()->floor_parsed_flag++;
	else if (type == 'C')
		get_pars()->ceiil_parsed_flag++;
	return (rgb);
}
