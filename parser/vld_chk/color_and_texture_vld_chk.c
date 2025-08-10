#include "../pars_priv.h"
#include "../../my_libft/libft.h"

extern int	try_open(char *file_name);
extern int	file_format_chk(char *format, char *file_name);
extern int	count_splits(char **splits);

int texture_vld_chk(char *direction, char *texture_line)
{
	char	**buf;

	buf = ft_split(texture_line, ' ');
	if (buf == NULL)
		malloc_fail_perror();
	if (count_splits(buf) != 2
		|| ft_strncmp(buf[0], direction, 3)
		|| !file_format_chk(".xpm", buf[1])
		|| !try_open(buf[1]))
	{
		free_splits(buf);
		return (0);
	}
	free_splits(buf);
	return (1);
}

/*
 * RGB formats looks like.. 'F 123,123,123'.
 * So, counting comma's result must be 2.
 */
static int	count_comma(char *str)
{
	int	i = 0;
	while (*str)
	{
		if (*str == ',')
			i++;
		str++;
	}
	return (i);
}

/*
 * Each rgb color's valid range is 0 to 255.
 * It must contains only digit.
 */
static int	color_vld_chk(char **rgb)
{
	while (*rgb)
	{
		if (!ft_is_str_digit(*rgb)
			|| ft_strlen(*rgb) > 3
			|| !(ft_atoi(*rgb) >= 0 && ft_atoi(*rgb) <= 255))
			return (0);
		rgb++;
	}
	return (1);
}


int	bg_color_vld_chk(char *floor_or_ceiling, char *bg_line)
{
	char	**splits;
	char	**rgb;

	splits = ft_split(bg_line, ' ');
	if (splits == NULL)
		malloc_fail_perror();
	if (count_splits(splits) != 2
		|| count_comma(splits[1]) != 2
		|| ft_strncmp(splits[0], floor_or_ceiling, 2))
	{
		free_splits(splits);
		return (0);
	}
	rgb = ft_split(splits[1], ',');
	if (rgb == NULL)
		malloc_fail_perror();
	free_splits(splits);
	if (count_splits(rgb) != 3
		|| !color_vld_chk(rgb))
	{
		free_splits(rgb);
		return (0);
	}
	free_splits(rgb);
	return (1);
}
