/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@42gyeongsan.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:05:09 by hoysong           #+#    #+#             */
/*   Updated: 2024/03/25 23:11:14 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*ptr;
	size_t			i;
	size_t			total;

	total = size * num;
	if (num == 0 || size == 0)
		return (malloc(0));
	if (total / size != num)
		return (0);
	ptr = malloc(size * num);
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < size * num)
		ptr[i++] = 0;
	return (ptr);
}
