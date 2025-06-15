/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:33:25 by hoysong           #+#    #+#             */
/*   Updated: 2024/03/25 21:04:42 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	bigint;
	size_t			i;

	i = 0;
	bigint = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (*ptr == bigint)
			return (ptr);
		i++;
		ptr++;
	}
	return (0);
}
