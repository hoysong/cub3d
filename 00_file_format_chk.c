#include <fcntl.h>
#include "./my_libft/libft.h"

static int wall_vld_chk(char *direction, char *file_format)
{
	char	**splits;

	//direction check.
	return (1);
}

/*This function returns 1 if content is not valid.*/
static int	content_vld_chk(t_dnode *file_content)
{
	/*NORTH CHECK*/
	wall_vld_chk("NO", file_content->data);
	/*SOUTH CHECK*/
	/*WEST CHECK*/
	/*EAST CHECK*/
	return (1);
}

static int	is_vld_file_format(char *file_name, char *file_format)
{
	while (*file_name && *file_name != '.')
		file_name ++;
	if (*file_name == '\0')
		return (0);
	else if (ft_strncmp(file_name, file_format, ft_strlen(file_format)) && ft_strlen(file_name) != ft_strlen(file_format))
		return (0);
	return (1);
}

static int	try_open(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	pars_map_vld_chk(int argc, char **argv)
{
	t_dnode	*file_content;
	int	fd;

	if (argc == 1 || argc >= 3)
		return (1);
	argv ++;
	if (is_vld_file_format(*argv, ".cub"))
		return (1);
	else if (!try_open(*argv))
		return (1);
	fd = open(*argv, O_RDONLY);
    // now read file...
        // maybe get gnl lst first.
	file_content = get_gnl_node(fd);
	if (!content_vld_chk(file_content))
	{
		return (1);
	}
            // after get gnl list... read north, south, west, east.
                // these textures will be splist and checked.
                    // 
	return (0);
}
