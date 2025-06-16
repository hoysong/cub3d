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
	return (0);
}
