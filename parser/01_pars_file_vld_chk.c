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

char	**gen_map(void)
{
	size_t	i;
	char	**map_ptr;

	i = 0;
	//가로 최대길이 구하기.
	//세로 최대길이 구하기.
	//ft_calloc으로 가로세로 넓이의 더블포인터 동적할당.
	//	단, 위, 아래, 왼쪽, 오른쪽 4면을 '\0'로 덮어줘야 안전할 듯 하다.
	//	그렇다면 실제로는 +2 +2씩 가로세로에 더해줘야 할 듯 하다.
	map_ptr = malloc(sizeof(char *) * (get_max_height() + 3));
	map_ptr[get_max_height() + 2] = NULL;
	while (map_ptr[i])
	{
		i++;
	}
	return (map_ptr);
}

void	map_vld_chk(void)
{
	char	**map;
	map = gen_map();
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
