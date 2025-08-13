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

static void	put_errmsg(int pars_errno)
{
	printf("Error\n");
	if (pars_errno == ARGC_NOT_TWO)
		printf(ARGC_NOT_TWO_MSG);
	else if (pars_errno == NOT_CUB_FMT)
		printf(NOT_CUB_FMT_MSG);
	else if (pars_errno == CUB_OPEN_ERR)
		printf(CUB_OPEN_ERR_MSG);
	else if (pars_errno == TYPE_IDENTIFIER_ERR)
		printf(TYPE_IDENTIFIER_ERR_MSG);
	else if (pars_errno == MAP_ERR)
		printf(MAP_ERR_MSG);
	else if (pars_errno == MULTIPLE_PLAYER)
		printf(MULTIPLE_PLAYER_MSG);
	else if (pars_errno == SAME_TEXTURE)
		printf(SAME_TEXTURE_MSG);
	else if (pars_errno == NEED_MORE_FILE_ARGS)
		printf(NEED_MORE_FILE_ARGS_MSG);
	else if (pars_errno == GET_XPM_IMGDATA_FAIL)
		printf(GET_XPM_IMGDATA_FAIL_MSG);
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
