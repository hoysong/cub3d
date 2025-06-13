#include <fcntl.h>
#include <stdio.h>
#include "./my_libft/libft.h"

static int	count_index(char **splits)
{
	int	i;

	i = 0;
	while (splits[i])
		i++;
	return (i);
}

static int	is_vld_file_format(char *file_name, char *file_format);
static int	try_open(char *file_name);

static void	del_newline(char *str)
{
	while (*str && (*str != '\n'))
		str++;
	*str = '\0';
}

static int wall_vld_chk(char *direction, char *wall_info)
{
	char	**splits;

	//direction check.
	printf("line: %s\n", wall_info);
	splits = ft_split(wall_info, ' ');
	if (count_index(splits) != 2)
		return (0);
	else if (ft_strncmp(splits[0], "NO\0", 3))
		return (0);
	del_newline(splits[1]);
	if (!try_open(splits[1]))
		return (0);
	free_splits(splits);
	printf("good line!\n");
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
	int	i;

	i = 0;
	while (file_name[i])
		i++;
	while (file_name[i] != '.')
		i--;
	if (ft_strncmp(&(file_name[i]), file_format, ft_strlen(file_format) + 1))
		return (0);
	//while (*file_name && *file_name != '.')
	//	file_name ++;
	//if (*file_name == '\0')
	//	return (0);
	//else if (ft_strncmp(file_name, file_format, ft_strlen(file_format)) && ft_strlen(file_name) != ft_strlen(file_format))
	//	return (0);
	return (1);
}

/*this function returns 0 if open fail.*/
static int	try_open(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	{
		printf("%s: open fail\n", file_name);
	close(fd);
	}
	return (1);
}

int	pars_map_vld_chk(int argc, char **argv)
{
	t_dnode	*file_content;
	int	fd;

	if (argc == 1 || argc >= 3)
	{
		return (1);
	}
	argv ++;
	printf("Is this .cub file?\n");
	if (!is_vld_file_format(*argv, ".cub"))
	{
		printf("");
		return (1);
	}
	else if (!try_open(*argv))
		return (1);
	fd = open(*argv, O_RDONLY);
    // now read file...
        // maybe get gnl lst first.
	file_content = get_gnl_node(fd);
	file_content = file_content->next_node;
	if (!content_vld_chk(file_content))
	{
		return (1);
	}
            // after get gnl list... read north, south, west, east.
                // these textures will be splist and checked.
                    // 
	return (0);
}
