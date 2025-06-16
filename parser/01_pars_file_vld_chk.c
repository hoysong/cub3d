#include "./pars_priv.h"
#include "../my_libft/libft.h"
#include <fcntl.h>

int	try_open(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);

	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

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

/*== 위 함수들은 다른 함수들에서 자주 사용.==.*/
/*둘 곳 없으니 일단 빼두자.*/

static size_t	get_max_length(void)
{
	t_dnode	*node;
	size_t	len;

	node = get_pars()->cub_file_list;
	len = 0;
	while (node)
	{
		if (ft_strlen((char *)node->data) > len)
			len = ft_strlen((char *)node->data);
		node = node->next_node;
	}
	return (len);
}

static size_t	get_max_height(void)
{
	t_dnode	*node;
	size_t	height;

	node = get_pars()->cub_file_list;
	height = 0;
	while (node)
	{
		node = node->next_node;
		height++;
	}
	return (height);
}

static void	copy_str(char *dest, char *src)
{
	while (*src)
	{
		*dest = *src;
		src++;
		dest++;
	}
}

char	**gen_map(size_t max_length, size_t max_height)
{
	size_t	i;
	char	**map;
	t_dnode	*node;

	i = 0;
	node = get_pars()->cub_file_list;
	map = malloc(sizeof(char *) * (max_height + 1));
	map[max_height] = NULL;
	while (i < max_height)
	{
		map[i] = ft_calloc(max_length, sizeof(char) + 1);
		copy_str(map[i], (char *)node->data);
		node = node->next_node;
		i++;
	}
	return (map);
}

void	map_vld_chk(void)
{
	char	**map;

	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
	map = gen_map(get_max_length(), get_max_height());
	print_splits(map);
	/*
	 */
	free_splits(map);
}

extern void	gnl_cub_file( void );
extern void	check_xpm_texture_line(void);
extern void	background_vld_chk(void);

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
	map_vld_chk();
	return (0);
}
