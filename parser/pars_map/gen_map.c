#include "../pars_priv.h"
#include "../../my_libft/libft.h"

size_t	get_max_length(void)
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

size_t	get_max_height(void)
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

void	copy_str(char *dest, char *src)
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
	if (map == NULL)
		malloc_fail_perror();
	map[max_height] = NULL;
	while (i < max_height)
	{
		map[i] = ft_calloc(max_length, sizeof(char) + 1);
		if (map[i] == NULL)
			malloc_fail_perror();
		ft_memset(map[i], ' ', max_length);
		copy_str(map[i], (char *)node->data);
		node = node->next_node;
		i++;
	}
	return (map);
}
