#include "../pars_priv.h"
#include "../../my_libft/libft.h"
#include <fcntl.h>
//#include <stdio.h>

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

static int texture_vld_chk(char *direction, char *texture_line)
{
	char	**buf;

	buf = ft_split(texture_line, ' ');
	if (count_splits(buf) != 2
		|| ft_strncmp(buf[0], direction, 3)
		|| !file_format_chk(".xpm", buf[1])
		|| !try_open(buf[1]))
	{
		free_splits(buf);
		return (0);
	}
	free_splits(buf);
	return (1);
}

static char	*get_textrue_name(char *texture_line)
{
	char	**splits;
	char	*texture_name;

	splits = ft_split(texture_line, ' ');
	texture_name = ft_strdup(splits[1]);
	free_splits(splits);
	return (texture_name);
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

static int	bg_color_vld_chk(char *floor_or_ceiling, char *bg_line)
{
	char	**splits;
	char	**rgb;

	splits = ft_split(bg_line, ' ');
	if (count_splits(splits) != 2
		|| ft_strncmp(splits[0], floor_or_ceiling, 2))
	{
		free_splits(splits);
		return (0);
	}
	rgb = ft_split(splits[1], ',');
	free_splits(splits);
	if (count_splits(rgb) != 3
		|| !color_vld_chk(rgb))
	{
		free_splits(rgb);
		return (0);
	}
	free_splits(rgb);
	return (1);
}

static t_rgb	get_rgb(char *str, char type)
{
	char	**splits;
	char	**rgb_splits;
	t_rgb	rgb;

	splits = ft_split(str, ' ');
	rgb_splits = ft_split(splits[1], ',');
	rgb.red = ft_atoi(rgb_splits[0]);
	rgb.green = ft_atoi(rgb_splits[1]);
	rgb.blue = ft_atoi(rgb_splits[2]);
	free_splits(splits);
	free_splits(rgb_splits);
	if (type == 'F')
		get_pars()->floor_parsed_flag++;
	else if (type == 'C')
		get_pars()->ceiil_parsed_flag++;
	return (rgb);
}

static int	is_data_filled(void)
{
	if (!get_pars()->north_texture
		|| !get_pars()->south_texture
		|| !get_pars()->west_texture
		|| !get_pars()->east_texture
		|| !(get_pars()->floor_parsed_flag <= 1)
		|| !(get_pars()->ceiil_parsed_flag <= 1)
		)
		return (0);
	return (1);
}

static void	pars_tex_bg(t_dnode *node)
{
	while (node)
	{
		if (texture_vld_chk("NO", node->data) && !get_pars()->north_texture)
			get_pars()->north_texture = get_textrue_name(node->data);
		else if (texture_vld_chk("SO", node->data) && !get_pars()->south_texture)
			get_pars()->south_texture = get_textrue_name(node->data);
		else if (texture_vld_chk("WE", node->data) && !get_pars()->west_texture)
			get_pars()->west_texture = get_textrue_name(node->data);
		else if (texture_vld_chk("EA", node->data) && !get_pars()->east_texture)
			get_pars()->east_texture = get_textrue_name(node->data);
		else if (bg_color_vld_chk("F", node->data))
			get_pars()->floor = get_rgb(node->data, 'F');
		else if (bg_color_vld_chk("C", node->data))
			get_pars()->ceiling = get_rgb(node->data, 'C');
		else if (*(char *)(node->data) != '\0')
		{
			if (!is_data_filled())
				get_pars()->pars_errno = 1;
			break ;
		}
		node = node->next_node;
	}
	/*파싱이 진행된 위치까지 이동하기.*/
	while (get_pars()->cub_file_list != node)
		get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
	/*이후의 개행들을 스킵하기.*/
	/*newline들은 \0로 치환되어있다.*/
	while (*(char *)(get_pars()->cub_file_list->data) == '\0')
		get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
//	printf("pars tex/BG: %s\n", (char *)(get_pars()->cub_file_list->data));
}

extern void	gnl_cub_file( void );
extern void	check_xpm_texture_line(void);
extern void	background_vld_chk(void);
extern void	map_vld_chk(void);

int	pars_file_vld_chk( void )
{
	//0. argc check.
	if (get_pars()->argc != 2)
		get_pars()->pars_errno = 1;
	//1. .cub valid check.
	if (get_pars()->pars_errno)
		return (1);
	if (!file_format_chk(".cub", get_pars()->argv[1]))
		get_pars()->pars_errno = 2;
	//2. .cub open check.
	if (!try_open(get_pars()->argv[1]))
		get_pars()->pars_errno = 3;
	if (get_pars()->pars_errno)
		return (get_pars()->pars_errno);
	//3. wall texture check.
	gnl_cub_file();
	pars_tex_bg(get_pars()->cub_file_list);
	//4. floor/ceiling RGB check.
	map_vld_chk();
	return (get_pars()->pars_errno);
}
