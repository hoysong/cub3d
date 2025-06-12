/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_nbr_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:05:28 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/26 14:23:23 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	str_len(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		j = i + 1;
		while (str[j] != '\0')
			if (str[i] == str[j])
				return (0);
		else
			j++;
		i++;
	}
	if (i < 2)
		return (0);
	return (i);
}

static int	initial(long long *nbr, long long *power, int *total_len)
{
	*power = 1;
	*total_len = 0;
	if (*nbr < 0)
	{
		*total_len = 1;
		*nbr *= -1;
		write(1, "-", 1);
	}
	else if (*nbr == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	return (0);
}

int	sign_nbr_base_printf(long long nbr, char *base)
{
	long long			power;
	int					base_len;
	int					total_len;

	if (initial(&nbr, &power, &total_len))
		return (1);
	base_len = str_len(base);
	if (base_len == 0)
		return (1);
	while (nbr >= power && nbr / power >= base_len)
		power *= base_len;
	while (power > 0)
	{
		write(1, &base[nbr / power], 1);
		nbr %= power;
		power /= base_len;
		total_len++;
	}
	return (total_len);
}
