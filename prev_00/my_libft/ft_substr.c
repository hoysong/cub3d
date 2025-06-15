/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@42gyeongsan.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:07:04 by hoysong           #+#    #+#             */
/*   Updated: 2024/03/22 11:57:23 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new_str;

	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == 0)
		return (0);
	ft_strlcpy(new_str, &s[start], len + 1);
	return (new_str);
}
