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
	printf("==== WALL VLD CHECK ====\n");
	printf("direction: %s\n", direction);
	printf("full line: %s\n", wall_info);
	splits = ft_split(wall_info, ' ');
	if (count_index(splits) != 2)
	{
		printf("not a 2 arguments\n");
		return (0);
	}
	printf("there is two argument. good!\n");
	if (ft_strncmp(splits[0], direction, 3))
	{
		printf("direction not match..\n");
		printf("direction must be %s\n", direction);
		printf("but file is %s\n", splits[0]);
		return (0);
	}
	del_newline(splits[1]);
	printf("try open file: %s\n", splits[1]);
	if (!try_open(splits[1]))
	{
		printf("try open fail..\n");
		return (0);
	}
	printf("open success!\n");
	free_splits(splits);
	printf("good line!\n");
	return (1);
}

/*This function returns 1 if content is not valid.*/
static int	file_content_vld_chk(t_dnode *file_content)
{
	if (wall_vld_chk("NO", file_content->data))
		return (0);
	file_content = file_content->next_node;
	if (wall_vld_chk("SO", file_content->data))
		return (0);
	file_content = file_content->next_node;
	if (wall_vld_chk("WE", file_content->data))
		return (0);
	file_content = file_content->next_node;
	if (wall_vld_chk("EA", file_content->data))
		return (0);
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
	{
		return (0);
		printf("%s: open fail\n", file_name);
	}
	close(fd);
	printf("%s: open success\n", file_name);
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
	printf("==== FORMAT(.cub) CHECK ====\n");
	if (!is_vld_file_format(*argv, ".cub"))
	{
		printf("not a .cub file...\n");
		return (1);
	}
	printf("good format!\n");
	if (!try_open(*argv))
	{
		printf("bad format..\n");
		return (1);
	}
	fd = open(*argv, O_RDONLY);
    // now read file...
        // maybe get gnl lst first.
	file_content = get_gnl_node(fd);
	file_content = file_content->next_node;
	if (!file_content_vld_chk(file_content))
	{
		return (1);
	}
            // after get gnl list... read north, south, west, east.
                // these textures will be splist and checked.
                    // 
	return (0);
}
