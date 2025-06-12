/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:59:08 by hoysong           #+#    #+#             */
/*   Updated: 2024/03/22 11:54:37 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*destptr;
	unsigned char	*srcptr;

	destptr = (unsigned char *)dest;
	srcptr = (unsigned char *)src;
	if (destptr == 0 && srcptr == 0)
		return (0);
	if (src < dest)
		while (n--)
			destptr[n] = srcptr[n];
	else
		while (n--)
			*destptr++ = *srcptr++;
	return (dest);
}
