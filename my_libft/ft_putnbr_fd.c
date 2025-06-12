/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:52:43 by hoysong           #+#    #+#             */
/*   Updated: 2024/03/22 11:56:03 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*insert_digit(char *num_str, long int long_num)
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

void	ft_putnbr_fd(int n, int fd)
{
	long int	long_num;
	char		*digit_str;
	char		num_str[12];

	long_num = n;
	if (long_num == 0)
	{
		write(fd, "0", 1);
	}
	else
	{
		digit_str = insert_digit(num_str, long_num);
		write(fd, digit_str, ft_strlen(digit_str));
	}
}
