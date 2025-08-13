/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_pars_perror.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 03:31:50 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 03:32:02 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars_errno.h"
#include "../pars_priv.h"
#include <stdio.h>

extern void	argc_err_msg(void);
extern void	type_indent_msg(void);
extern void	map_err_msg(void);
extern void	same_texture_msg(void);
extern void	few_file_content_msg(void);

static void	put_errmsg(int pars_errno)
{
	printf("Error\n");
	if (pars_errno == ARGC_NOT_TWO)
		argc_err_msg();
	else if (pars_errno == NOT_CUB_FMT)
		printf("Not '.cub' format\n");
	else if (pars_errno == CUB_OPEN_ERR)
		printf("'.cub' file open fail.\n");
	else if (pars_errno == TYPE_IDENTIFIER_ERR)
		type_indent_msg();
	else if (pars_errno == MAP_ERR)
		map_err_msg();
	else if (pars_errno == MULTIPLE_PLAYER)
		printf("Multiple player's detected.\n"
			" └─player must be only one.\n");
	else if (pars_errno == SAME_TEXTURE)
		same_texture_msg();
	else if (pars_errno == NEED_MORE_FILE_ARGS)
		few_file_content_msg();
	else if (pars_errno == GET_XPM_IMGDATA_FAIL)
		printf("Seems you passed wrong xpm image.\n");
}

void	malloc_fail_perror(void)
{
	printf("MALLOC_FAIL_ERROR\n");
	exit(MALLOC_FAIL);
}

void	pars_perror(void)
{
	put_errmsg(get_pars()->pars_errno);
}
