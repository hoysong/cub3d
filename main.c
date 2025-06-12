/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 03:04:02 by hoysong           #+#    #+#             */
/*   Updated: 2025/06/13 07:37:40 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "./mlx/mlx.h"
#include "./my_libft/libft.h"

/*Allowed functions.*/
//• open, close, read, write, printf, malloc, free, perror, strerror, exit
//• math 라이브러리 내의 모든 함수들 (-lm man man 3 math)
//• MinilibX 라이브러리 내의 모든 함수들

/*format checker.*/
// This function returns 1 if format is file_name is ends with file_format.
// Will use for '.xpm', '.cub'.

static int	is_vld_file_format(char *file_name, char *file_format)
{
	while (*file_name || *file_name != '.')
		file_name ++;
	if (*file_name == '\0')
		return (0);
	else if (ft_strncmp(file_name, file_format, ft_strlen(file_format)) && ft_strlen(file_name) != ft_strlen(file_format))
	{
		return (0);
	}
	return (1);
}

static int	pars_map_vld_chk(int argc, char **argv)
{
	if (argc == 1 || argc >= 3)
		return (1);
	argv ++;
	if (is_vld_file_format(*argv, ".cub"))
		printf("vld_format!");
	return (0);
}

int	main(int argc, char **argv)
{
	if (pars_map_vld_chk(argc, argv))
	{
		printf("file_name must be .cub\n");
		return (1);
	}
	return (0);
}
