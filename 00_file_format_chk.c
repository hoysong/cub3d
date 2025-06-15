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
		return (0);
	printf("open success!\n");
	free_splits(splits);
	printf("good line!\n");
	return (1);
}

static int	background_vld_chk(char *floor_for_ceiling, char *background_info)
{
	printf("===== BG check =====\n");
	int		i;
	char	**bg_info;
	char	**rgb_split;

	i = 0;
	printf("checkoug BG info: %s", background_info);
	bg_info = ft_split(background_info, ' ');
	printf("%d\n", count_index(bg_info));
	if (count_index(bg_info) != 2)
	{
		printf("not valid\n");
		return (0);
	}
	if (ft_strncmp(bg_info[0], floor_for_ceiling, 2))
		return (0);
	printf("valid!\n");
	printf("bg argument check\n");
	printf("will split %s\n", bg_info[1]);
	// 이제 콤마로 스플릿 해야 함.
	// 인자 갯수를 세야 겠지??
	del_newline(bg_info[1]);
	rgb_split = ft_split(bg_info[1], ',');
	printf("rgb split done.\n");
	if (count_index(rgb_split) != 3)
	{
		printf("bad rgb file\n");
		return (0);
	}
	printf("good rgb file\n");
	//	그 다음 is_numeric을 통해 측정 해야겠지????
	//	여기서는 rgb_split를 안담을 것임.
	//	맵 유효성 검사 이후 담는 것이 좋을 듯 하다.
	while (rgb_split[i] != NULL)
	{
		if (!ft_is_str_digit(rgb_split[i])
		|| ft_strlen(rgb_split[i]) > 3
		|| ft_atoi(rgb_split[i]) > 255
		|| ft_atoi(rgb_split[i]) < 0
		// || is_overflowed..
		)
			break ;
		i++;
	}
	if (rgb_split[i] != NULL)
		return (0);
	free_splits(bg_info);
	free_splits(rgb_split);
	return (1);
}

size_t	get_map_length(t_dnode *node)
{
	size_t map_length;

	map_length = 0;
	while (node)
	{
		if (node->data != NULL)
		{
			del_newline(node->data);
			if (ft_strlen((char *)node->data) > map_length)
				map_length = ft_strlen((char *)node->data);
		}
		node = node->next_node;
	}
	return (map_length);
}

size_t	get_map_height(t_dnode *node)
{
	size_t i;

	i = 0;
	while (node)
	{
		node = node->next_node;
		i++;
	}
	return (i);
}

static int	is_surrounded(t_dnode *node)
{
	/*GET DOUBLE ARR SIZE.*/
	printf("== is_surrounded ==\n");
	size_t	map_length;
	size_t	map_height;
	map_length = get_map_length(node);
	map_height = get_map_height(node);
	printf("map length: %zu\n", map_length);
	printf("map height: %zu\n", map_height);
	/*GET ARR SIZE.*/
	char **map = malloc(sizeof(char *) * (map_height + 1));
	size_t	i;

	i = 0;
	while (i < map_height)
	{
		map[i] = ft_strdup((char *)node->data);
		node = node->next_node;
		i++;
	}
	printf("%zu\n", map_height);
	map[i] = NULL;
	print_splits(map);
	free_splits(map);
	return (1);
}

/*This function returns 1 if content is not valid.*/
static int	file_content_vld_chk(t_dnode *file_content)
{
	/*WALL VLD CHECK.*/
	if (!wall_vld_chk("NO", file_content->data))
		return (0);
	file_content = file_content->next_node;
	if (!wall_vld_chk("SO", file_content->data))
		return (0);
	file_content = file_content->next_node;
	if (!wall_vld_chk("WE", file_content->data))
		return (0);
	file_content = file_content->next_node;
	if (!wall_vld_chk("EA", file_content->data))
		return (0);
	file_content = file_content->next_node;
	file_content = file_content->next_node;
	/*FLOOR/CEILING COLOR.*/
	if (!background_vld_chk("F", file_content->data))
	{
		printf("bad Floor\n");
		return (0);
	}
	file_content = file_content->next_node;
	if (!background_vld_chk("C", file_content->data))
	{
		printf("bad Ceiling\n");
		return (0);
	}
	file_content = file_content->next_node;
	file_content = file_content->next_node;
	/*CLOSED MAP CHECK.*/
	is_surrounded(file_content);
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

t_dnode *del_null_data_node(t_dnode *node)
{
	node = find_head_dubly(node);
	while (node->next_node != NULL)
	{
		node = node->next_node;
		if (node->prev_node->data == NULL)
			destroy_doubly_node(node->prev_node);
	}
	if (node->data == NULL)
	{
		node = node->prev_node;
		destroy_doubly_node(node->next_node);
	}
	return (find_head_dubly(node));
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
	printf("%d\n", fd);
	file_content = get_gnl_node(fd);
	file_content = del_null_data_node(file_content);
	if (!file_content_vld_chk(file_content))
	{
		return (1);
	}
	file_content = find_head_dubly(file_content);
	while(file_content->next_node != NULL)
	{
		file_content = file_content->next_node;
		destroy_doubly_node(file_content->prev_node);
	}
	destroy_doubly_node(file_content);
                    // 
	return (0);
}
