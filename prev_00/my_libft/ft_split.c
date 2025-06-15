/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@42gyeongsan.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:23:10 by hoysong           #+#    #+#             */
/*   Updated: 2024/03/24 20:34:20 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**make_arr(char const *s, char c, int *words)
{
	int		count_alpha;
	char	**arr;

	count_alpha = 0;
	while (1)
	{
		if (*s != c && *s != '\0')
			count_alpha++;
		else if (*s == c || *s == '\0')
		{
			if (count_alpha > 0)
			{
				(*words)++;
				count_alpha = 0;
			}
		}
		if (!*s++)
			break ;
	}
	arr = malloc(sizeof(char *) * (*words + 1));
	if (arr == 0)
		return (0);
	arr[*words] = NULL;
	return (arr);
}

static int	insert_alpha(char const *s, char c, char **splits_arr, int *index)
{
	int	i;

	i = 0;
	while (1)
	{
		if (s[i] == c || s[i] == '\0')
		{
			if (i > 0)
			{
				splits_arr[*index] = ft_substr(s, 0, i);
				if (splits_arr[*index] == NULL)
					return (0);
				(*index)++;
				s = &s[i];
				i = 0;
			}
			if (s[i] == '\0')
				break ;
			s++;
		}
		else if (s[i] != c)
			i++;
	}
	return (1);
}

static void	ft_free(char **splits, int *index)
{
	int	i;

	i = 0;
	while (i < *index)
		free(splits[i++]);
	free(splits);
	splits = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		split_count;
	int		index;
	char	**splits;

	if (s == 0)
		return (0);
	split_count = 0;
	index = 0;
	splits = make_arr(s, c, &split_count);
	if (insert_alpha(s, c, splits, &index) == 0)
		ft_free(splits, &index);
	return (splits);
}
