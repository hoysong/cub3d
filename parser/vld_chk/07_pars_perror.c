#include "../pars_errno.h"
#include "../pars_priv.h"
#include <stdio.h>

static void	put_errmsg(int pars_errno)
{
	printf("Error\n");
	if (pars_errno == ARGC_NOT_TWO)
		printf("Argument error.\n");
	else if (pars_errno == NOT_CUB_FMT)
		printf("Not '.cub' format\n");
	else if (pars_errno == CUB_OPEN_ERR)
		printf("'.cub' file open fail.\n");
	else if (pars_errno == XPM_TEXTURE_ERR)
		printf("XPM Texture error.\n");
	else if (pars_errno == FLOOR_CEILING_ERR)
		printf("Floor or ceiling err.\n");
	else if (pars_errno == MAP_ERR)
		printf("Map not surrounded by wall.\n");
	else if (pars_errno == MULTIPLE_PLAYER)
		printf("Multiple player's detected.\n");
}

void pars_perror(void)
{
	put_errmsg(get_pars()->pars_errno);
}
