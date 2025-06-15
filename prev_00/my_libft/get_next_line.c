/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:57:41 by hoysong           #+#    #+#             */
/*   Updated: 2024/05/28 13:37:55 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*get_remain(char **tmp, ssize_t *read_len)
{
	size_t	i;
	char	*return_str;
	char	*free_tmp;

	i = 0;
	return_str = 0;
	while ((*tmp)[i] != '\0')
	{
		if ((*tmp)[i] == '\n')
		{
			if (tmp[0][i + 1] != '\0')
			{
				return_str = ft_strdup(&tmp[0][i + 1]);
			}
			tmp[0][i + 1] = '\0';
			*read_len = 0;
			free_tmp = *tmp;
			*tmp = ft_strdup(*tmp);
			free(free_tmp);
			return (return_str);
		}
		i++;
	}
	return (0);
}

static void	setup(ssize_t *read_len, char **tmp, char **buff, char **save)
{
	*read_len = GNL_BUFFER_SIZE;
	*buff = ft_calloc(GNL_BUFFER_SIZE + 1, sizeof(char));
	if (*save != 0 && **save != 0)
	{
		*tmp = ft_strdup(*save);
		free(*save);
	}
	else
		*tmp = ft_strdup("");
}

char	*get_next_line(int fd)
{
	ssize_t			read_len;
	static char		*save;
	char			*buff;
	char			*tmp;

	setup(&read_len, &tmp, &buff, &save);
	while (read_len == GNL_BUFFER_SIZE)
	{
		read_len = read(fd, buff, GNL_BUFFER_SIZE);
		if (read_len >= 0)
			buff[read_len] = '\0';
		save = tmp;
		tmp = ft_strjoin(save, buff);
		free(save);
		save = get_remain(&tmp, &read_len);
		if (save != 0 || GNL_BUFFER_SIZE > read_len)
			break ;
	}
	free(buff);
	if ((read_len < 1 && *tmp == '\0') || read_len < 0)
	{
		free(tmp);
		return (0);
	}
	return (tmp);
}
