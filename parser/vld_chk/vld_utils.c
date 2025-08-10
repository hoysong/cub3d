#include "../pars_priv.h"
#include "../../my_libft/libft.h"
#include <fcntl.h>

/*
 * This function just try open file_name.
 * return 1 if success.
 * exists for check '.cub', '.xpm'file is exists.
 */
int	try_open(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

/*
 * return 1 if file_name is ends with format.
 */
int	file_format_chk(char *format, char *file_name)
{
	char	*name_start;

	name_start = file_name;
	while (*file_name)
		file_name++;
	while (file_name != name_start && *file_name != '.')
		file_name--;
	if (ft_strncmp(file_name, file_name, ft_strlen(format) + 1)
		|| file_name == name_start)
	{
		return (0);
	}
	return (1);
}

/*
 * return number of splits elements.
 */
int	count_splits(char **splits)
{
	int	i;

	i = 0;
	while (*splits)
	{
		splits++;
		i++;
	}
	return (i);
}
