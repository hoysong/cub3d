/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:30:11 by hoysong           #+#    #+#             */
/*   Updated: 2024/03/22 11:55:36 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int n_src, size_t len)
{
	unsigned char	*ptr;

	ptr = dest;
	while (len)
		ptr[--len] = n_src;
	return (dest);
}
