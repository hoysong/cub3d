/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:00:37 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/26 14:19:37 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	s_option(va_list *ap)
{
	int		len;
	char	*s_flag;

	s_flag = (va_arg(*ap, char *));
	if (s_flag == NULL)
		return (ft_putstr_fd_printf("(null)", 1));
	len = ft_putstr_fd_printf(s_flag, 1);
	return (len);
}

static int	p_option(va_list *ap)
{
	int		len;
	void	*p_flag;

	p_flag = va_arg(*ap, void *);
	if (p_flag == 0)
		return (ft_putstr_fd_printf("(nil)", 1));
	len = ft_putstr_fd_printf("0x", 1);
	len += nbrbase_printf((unsigned long long)p_flag, "0123456789abcdef");
	return (len);
}

static int	options_1(char *args, va_list *ap, int *err)
{
	int			len;

	len = 0;
	if (*args == 'c')
		len = ft_putchar_fd_printf(va_arg(*ap, int), 1);
	else if (*args == 'd' || *args == 'i')
		len = sign_nbr_base_printf((int)va_arg(*ap, int), "0123456789");
	else if (*args == 'u')
		len = nbrbase_printf((unsigned int)va_arg(*ap, int), "0123456789");
	else if (*args == '%')
		len = ft_putchar_fd_printf('%', 1);
	else if (*args == 'x')
		len = nbrbase_printf(
				(long long)va_arg(*ap, unsigned int), "0123456789abcdef");
	else if (*args == 'X')
		len = nbrbase_printf(
				(long long)va_arg(*ap, unsigned int),
				"0123456789ABCDEF");
	else if (*args == 's')
		return (s_option(ap));
	else if (*args == 'p')
		return (p_option(ap));
	else
		*err = -1;
	return (len);
}

static void	initialize(int *str_len, int *total_len, int *err)
{
	*str_len = 0;
	*total_len = 0;
	*err = 0;
}

int	ft_printf(const char *args, ...)
{
	int		total_len;
	int		str_len;
	va_list	ap;
	int		err;

	if (write(1, "return -1 if stdout is dead", 0))
		return (write(1, "", 0));
	initialize(&str_len, &total_len, &err);
	va_start(ap, args);
	while (*args)
	{
		if (*args == '%')
		{
			total_len += options_1((char *)++args, &ap, &err);
			if (*args == '\0')
				break ;
		}
		else
			str_len += ft_putchar_fd_printf(*args, 1);
		args++;
	}
	if (err == -1)
		return (-1);
	return (str_len + total_len);
}
