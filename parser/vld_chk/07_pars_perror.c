#include "../pars_errno.h"
#include "../pars_priv.h"
#include <stdio.h>

static void	put_errmsg(int pars_errno)
{
	printf("Error\n");
	if (pars_errno == ARGC_NOT_TWO)
		printf("%s\n%s\n",
				"Argument error.",
				"add file name ends with '.cub'"
				);
	else if (pars_errno == NOT_CUB_FMT)
		printf("Not '.cub' format\n");
	else if (pars_errno == CUB_OPEN_ERR)
		printf("'.cub' file open fail.\n");
	else if (pars_errno == XPM_TEXTURE_ERR)
		printf(
				"Type identifier error.\n"
				"Check example of format of texture line below.\n"
				"	example: NO ./path_to_xpm/test_texture.xpm\n"
				"	Textures filetype must be '.xpm'.\n"
				"	Textures type identifier must be one of below..\n"
				"		NO, SO, WE, EA\n"
				"or.. Floor or ceiling err.\n"
				"Example of format of floor/ceiling color below..\n"
				"	F 0,42,255\n"
				"	C 0,42,255\n"
				"	Floor ceiling type identifier must be F or C.\n"
				"	color range must be 0 to 255.\n"
				);
	else if (pars_errno == MAP_ERR)
		printf("Map not surrounded by wall.\n");
	else if (pars_errno == MULTIPLE_PLAYER)
		printf("%s\n%s\n",
				"Multiple player's detected.",
				"player must be only one."
				);
	else if (pars_errno == SAME_TEXTURE)
		printf("%s\n%s\n",
				"Same textures detected.",
				"all textures must be defferent");
}

void pars_perror(void)
{
	put_errmsg(get_pars()->pars_errno);
}
