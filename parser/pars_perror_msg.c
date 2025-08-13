/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_perror_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 06:44:12 by hoysong           #+#    #+#             */
/*   Updated: 2025/08/14 06:50:08 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	argc_err_msg(void)
{
	printf(
		"Argument error.\n"
		" ├─run program with one argument\n"
		" └─add file name ends with '.cub'\n"
		"   └─example: ./cub3D ./path_to_map/map_name.cub\n"
		);
}

void	type_indent_msg(void)
{
	printf(
		"Type identifier error.\n"
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
		" ├─Each color elements length must be 1 to 3.\n"
		" └─Colors must be seperated by ','.\n");
}

void	map_err_msg(void)
{
	printf(
		"Map error detected.\n"
		" ├─map format must be made of one of below.\n"
		" │ ├─wall        : 1\n"
		" │ ├─empty_space : 0\n"
		" │ └─player      : one of N, S, W, E\n │\n"
		" ├─map must be surrounded by wall(1).\n"
		" │ └─ex)\n"
		" │      111111\n"
		" │      100001\n"
		" │      10N001\n"
		" │      111111\n │\n"
		" ├─map format must not include newline.\n"
		" │ └─wrong ex)\n"
		" │      111111\n"
		" │      100001\n"
		" │                <- must not include new line middle of map format.\n"
		" │      10N001\n"
		" │      111111\n │\n"
		" └─below map is also wrong format.\n"
		"   └─wrong ex)\n"
		"         1111 \n"
		"        100001\n"
		"        10N001\n"
		"         1111 \n");
}

void	same_texture_msg(void)
{
	printf(
		"Same textures detected.\n"
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

void	few_file_content_msg(void)
{
	printf(
		"We need more file content..\n"
		"Add some file content like below.\n"
		" └─good ex)\n"
		"          NO ./path_to_xpm/tex_1.xpm\n"
		"          SO ./path_to_xpm/tex_2.xpm\n"
		"          WE ./path_to_xpm/tex_3.xpm\n"
		"          EA ./path_to_xpm/tex_4.xpm\n"
		"\n"
		"          F 0,42,255\n"
		"          C 0,42,255\n"
		"\n"
		"          111\n"
		"          1N1\n"
		"          111\n");
}
