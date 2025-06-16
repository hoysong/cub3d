#include "./pars_priv.h"
#include "../my_libft/libft.h"
#include <fcntl.h>

static int	try_open(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);

	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	file_format_chk(char *format, char *file_name)
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

static void	del_null_data(void)
{
	t_dnode	*node;

	node = get_pars()->cub_file_list;
	while (node->next_node != NULL)
	{
		node = node->next_node;
		if (node->prev_node->data == NULL)
			destroy_doubly_node(node->prev_node);
	}
	get_pars()->cub_file_list = find_head_dubly(node);
	if (find_tail_dubly(node)->data == NULL)
		destroy_doubly_node(find_tail_dubly(node));
}

#include <stdio.h>

void	gnl_cub_file( void )
{
	t_dnode *gnl_node;

	get_pars()->cub_file_list = get_gnl_node(open(get_pars()->argv[1], O_RDONLY));
	del_null_data();
	gnl_node = get_pars()->cub_file_list;
	while (gnl_node)
	{
		*ft_strchr((char *)gnl_node->data, '\n') = '\0';
		gnl_node = gnl_node->next_node;
	}
		/*DEBUG.*/
		t_dnode	*node = get_pars()->cub_file_list;
		while (node)
		{
			printf("%s\n", (char *)node->data);
			node = node->next_node;
		}
		/*=====.*/
}

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

static void	bg_color_vld_chk(char *floor_or_ceiling, char *bg_line)
{
	char	**splits;
	char	**rgb;

	splits = ft_split(bg_line, ' ');
	if (count_splits(splits) != 2
		|| ft_strncmp(splits[0], floor_or_ceiling, 2)
		|| get_pars()->pars_errno)
	{
		get_pars()->pars_errno = 5;
		free_splits(splits);
		return ;
	}

	rgb = ft_split(splits[1], ',');
	free_splits(splits);
	if (count_splits(rgb) != 3
		|| !color_vld_chk(rgb)
		|| get_pars()->pars_errno)
	{
		get_pars()->pars_errno = 5;
		free_splits(rgb);
		return ;
	}
	free_splits(rgb);
	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
}

void	background_vld_chk(void)
{
	bg_color_vld_chk("F", get_pars()->cub_file_list->data);
	bg_color_vld_chk("C", get_pars()->cub_file_list->data);
	if (get_pars()->pars_errno)
		printf("bad_background..\n");
	else
		printf("good background!\n");
}

/*파싱은 진행 안하고 함수명 그대로 유효성검사 먼저 진행한다.*/
/*errno가 참이면 무조건 스킵하도록 만들면 편할 듯.*/
int	pars_file_vld_chk( void )
{
	//0. argc check.
	if (get_pars()->argc != 2)
	{
		get_pars()->pars_errno = 1;
		return (1);
	}
	//1. .cub valid check.
	if (!file_format_chk(".cub", get_pars()->argv[1]))
	{
		get_pars()->pars_errno = 2;
		return (2);
	}
	//2. .cub open check.
	if (!try_open(get_pars()->argv[1]))
	{
		get_pars()->pars_errno = 3;
		return (3);
	}
	//3. wall texture check.
	gnl_cub_file();
	check_xpm_texture_line();
	//4. floor/ceiling RGB check.
	background_vld_chk();
	return (0);
}
