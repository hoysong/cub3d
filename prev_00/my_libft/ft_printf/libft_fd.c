/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:17:42 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/26 14:13:18 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libftprintf.h"

int	ft_putstr_fd_printf(const char *s, int fd)
{
	const char	*start;
	int			s_len;

	start = s;
	while (*s++)
		;
	s_len = --s - start;
	write(fd, start, s_len);
	return (s_len);
}

int	ft_putchar_fd_printf(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}
