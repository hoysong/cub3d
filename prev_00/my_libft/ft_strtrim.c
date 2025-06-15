/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@42gyeongsan.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:44:57 by hoysong           #+#    #+#             */
/*   Updated: 2024/03/22 11:57:18 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_front(const char *s1, const char *set)
{
	size_t	i;

	while (*s1)
	{
		i = 0;
		while (*s1 != set[i] && set[i])
			i++;
		if (set[i] == '\0')
			break ;
		else if (set[i] == *s1)
			s1++;
	}
	return ((char *)s1);
}

static size_t	find_end(const char *set, char *start_ptr, char *end_ptr)
{
	size_t	i;
	size_t	find;

	find = 0;
	while (start_ptr != end_ptr)
	{
		i = 0;
		while (set[i] != *end_ptr && set[i])
			i++;
		if (set[i] == '\0')
			break ;
		else if (set[i] == *end_ptr)
			find++;
		end_ptr--;
	}
	return (find);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start_ptr;
	char	*end_ptr;
	char	*new_str;
	size_t	end_count;

	start_ptr = (char *)s1;
	end_ptr = (char *)s1;
	while (*end_ptr)
		end_ptr++;
	end_ptr--;
	start_ptr = find_front(s1, set);
	if (*start_ptr == '\0')
	{
		new_str = malloc(sizeof(char) * 1);
		if (new_str == NULL)
			return (0);
		*new_str = '\0';
		return (new_str);
	}
	end_count = find_end(set, start_ptr, end_ptr);
	new_str = ft_substr(start_ptr, 0, (ft_strlen(start_ptr) - end_count));
	return (new_str);
}
