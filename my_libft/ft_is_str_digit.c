/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_str_digit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:58:36 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/26 19:13:15 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 *	return 0 if string is not made with digits.
 *	return 1 if string is made with digits.
 *
 *	otherwise, begining of string is '\0', it will return 0.
 *	cuz string that pointing '\0' is not digit.
 */
int	ft_is_str_digit(char *str)
{
	if (*str == 0)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}
