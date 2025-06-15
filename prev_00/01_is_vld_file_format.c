#include <fcntl.h>
#include <stdio.h>
#include "./my_libft/libft.h"

int	is_vld_file_format(char *file_name, char *file_format)
{
	int	i;

	i = 0;
	while (file_name[i])
		i++;
	while (file_name[i] != '.')
		i--;
	if (ft_strncmp(&(file_name[i]), file_format, ft_strlen(file_format) + 1))
		return (0);
	return (1);
}

/*this function returns 0 if open fail.*/
int	try_open(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		return (0);
		printf("%s: open fail\n", file_name);
	}
	close(fd);
	printf("%s: open success\n", file_name);
	return (1);
}