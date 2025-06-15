/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:14:50 by hoysong           #+#    #+#             */
/*   Updated: 2024/03/22 11:53:16 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*insert_digit(char *num_str, long long long_num)
{
	int		i;
	char	num_sign;

	i = 10;
	num_sign = '\0';
	num_str[11] = '\0';
	if (long_num < 0)
	{
		long_num *= -1;
		num_sign = '-';
	}
	while (long_num > 0)
	{
		num_str[i] = long_num % 10 + '0';
		long_num /= 10;
		i--;
	}
	num_str[i] = num_sign;
	if (num_str[i] == '\0')
		i++;
	return (&num_str[i]);
}

char	*ft_itoa(int n)
{
	long long	long_num;
	char		*digit_str;
	char		num_str[12];
	char		*new_str;

	long_num = n;
	if (long_num == 0)
	{
		new_str = ft_strdup("0");
	}
	else
	{
		digit_str = insert_digit(num_str, long_num);
		new_str = ft_strdup(digit_str);
	}
	return (new_str);
}
