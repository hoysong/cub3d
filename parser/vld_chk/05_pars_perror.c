#include "../pars_errno.h"
#include "../pars_priv.h"
#include <stdio.h>

static void	put_type_identifier_err_msg(void)
{
		printf("Type identifier error.\n"
				" Check example format of texture line below.\n"
				" ├─example: NO ./path_to_xpm/test_texture.xpm\n"
				" ├─Textures filetype must be '.xpm'.\n"
				" └─Textures type identifier must be one of below..\n"
				"   ├─north: NO\n"
				"   ├─south: SO\n"
				"   ├─west : WE\n"
				"   ├─east : EA\n"
				"   └─good ex)\n"
				"             NO ./path_to_xpm/tex_1.xpm\n"
				"             SO ./path_to_xpm/tex_2.xpm\n"
				"             WE ./path_to_xpm/tex_3.xpm\n"
				"             EA ./path_to_xpm/tex_4.xpm\n"
				"\n	or.. Floor or ceiling err.\n\n"
				" Example of format of floor/ceiling color below..\n"
				" ├─F 0,42,255\n"
				" ├─C 0,42,255\n"
				" ├─Floor ceiling type identifier must be F or C.\n"
				" │ ├─floor   : F\n"
				" │ └─ceiling : C\n"
				" ├─Each color range must be 0 to 255.\n"
				" └─Colors must be seperated by ','.\n");
}

static void	put_map_err_msg(void)
{
		printf("Map error detected.\n"
				" ├─map format must be made of one of below.\n"
				" │ ├─wall/empty  : 1 or 0\n"
				" │ └─player      : one of N, S, W, E\n"
				" ├─map must be surrounded by wall(1).\n"
				" │ └─ex)\n"
				" │      111111\n"
				" │      100001\n"
				" │      10N001\n"
				" │      111111\n"
				" │\n"
				" ├─map format must not include newline.\n"
				" │ └─wrong ex)\n"
				" │      111111\n"
				" │      100001\n"
				" │                <- must not include new line middle of map format.\n"
				" │      10N001\n"
				" │      111111\n"
				" │\n"
				" └─below map is also wrong format.\n"
				"   └─wrong ex)\n"
				"         1111 \n"
				"        100001\n"
				"        10N001\n"
				"         1111 \n");
}

static void	put_same_texture_err_msg(void)
{
	printf("Same textures detected.\n"
			" └─all textures must be defferent\n"
			"   ├─good ex)\n"
			"   │         NO ./path_to_xpm/tex_1.xpm\n"
			"   │         SO ./path_to_xpm/tex_2.xpm\n"
			"   │         WE ./path_to_xpm/tex_3.xpm\n"
			"   │         EA ./path_to_xpm/tex_4.xpm\n"
			"   │\n"
			"   └─bad ex)\n"
			"             NO ./path_to_xpm/tex_1.xpm\n"
			"             SO ./path_to_xpm/tex_1.xpm <- same with with NO texture.\n"
			"             WE ./path_to_xpm/tex_3.xpm\n"
			"             EA ./path_to_xpm/tex_4.xpm\n");
}

static void	put_errmsg(int pars_errno)
{
	printf("Error\n");
	if (pars_errno == ARGC_NOT_TWO)
		printf("Argument error.\n"
				" ├─run program with one argument\n"
				" └─add file name ends with '.cub'\n"
				"   └─example: ./cub3D ./path_to_map/map_name.cub\n");
	else if (pars_errno == NOT_CUB_FMT)
		printf("Not '.cub' format\n");
	else if (pars_errno == CUB_OPEN_ERR)
		printf("'.cub' file open fail.\n");
	else if (pars_errno == TYPE_IDENTIFIER_ERR)
		put_type_identifier_err_msg();
	else if (pars_errno == MAP_ERR)
		put_map_err_msg();
	else if (pars_errno == MULTIPLE_PLAYER)
		printf("Multiple player's detected."
				" └─player must be only one.");
	else if (pars_errno == SAME_TEXTURE)
		put_same_texture_err_msg();
}

void	malloc_fail_perror(void)
{
	printf("MALLOC_FAIL_ERROR\n");
	exit(MALLOC_FAIL);
}

void pars_perror(void)
{
	put_errmsg(get_pars()->pars_errno);
}
