/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:21:58 by hoysong           #+#    #+#             */
/*   Updated: 2024/12/19 23:23:17 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	up_value(char *alpha)
{
	if (ft_isdigit(*alpha) && *alpha < '9')
		(*alpha)++;
	else if (*alpha == '9')
		*alpha = 'a';
	else if (ft_isalpha(*alpha) && *alpha < 'z')
		(*alpha)++;
}

static int	is_upable(char alpha)
{
	if (ft_isdigit(alpha))
	{
		if (alpha <= '9')
			return (1);
	}
	else if (ft_isalpha(alpha))
	{
		if (alpha < 'z')
			return (1);
	}
	return (0);
}

static char	*expand_name(char *name)
{
	char	*buff;

	buff = name;
	ft_memset(name, '0', ft_strlen(name));
	name = ft_strjoin(name, "0");
	free(buff);
	return (name);
}

static char	*name_hdl(char *name)
{
	int	i;

	i = 0;
	while (name[i] != '\0')
	{
		if (is_upable(name[i]))
		{
			up_value(&(name[i]));
			break ;
		}
		i++;
	}
	if (name[i] == '\0')
		name = expand_name(name);
	return (name);
}

char	*gen_name(int cmd)
{
	static char	*name;

	if (name == NULL)
		name = ft_strdup("0");
	if (cmd < 1)
	{
		free(name);
		name = NULL;
	}
	else
		name = name_hdl(name);
	return (name);
}
