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

extern int	pars_map_vld_chk(int argc, char **argv);

/*Allowed functions.*/
//• open, close, read, write, printf, malloc, free, perror, strerror, exit
//• math 라이브러리 내의 모든 함수들 (-lm man man 3 math)
//• MinilibX 라이브러리 내의 모든 함수들

/*format checker.*/
// This function returns 1 if format is file_name is ends with file_format.
// Will use for '.xpm', '.cub'.
static int	show_err_msg( void )
{
	perror("");
	printf("Something went wrong..\n");
	printf("├─1. Only one argument required.\n");
	printf("├─2. Argument must be exist filename.\n");
	printf("└─3. It must ends with '.cub'.\n");
	return (1);
}

int	main(int argc, char **argv)
{
	if (pars_map_vld_chk(argc, argv))
		return (show_err_msg());
	return (0);
}
