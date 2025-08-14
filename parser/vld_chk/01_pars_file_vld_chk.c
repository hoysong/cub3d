/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_pars_file_vld_chk.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 03:04:10 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 05:45:32 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars_priv.h"
#include "../../my_libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

static int	is_data_filled(void)
{
	if (!get_pars()->north_texture
		|| !get_pars()->south_texture
		|| !get_pars()->west_texture
		|| !get_pars()->east_texture
		|| (get_pars()->floor_parsed_flag != 1)
		|| (get_pars()->ceiil_parsed_flag != 1)
	)
	{
		return (0);
	}
	return (1);
}

static void	set_node_ptr_to_map_line(t_dnode *node)
{
	if (node == NULL)
	{
		get_pars()->cub_file_list = find_tail_dubly(get_pars()->cub_file_list);
		printf("set_node_ptr_to_map_line_ERR");
		get_pars()->pars_errno = MAP_ERR;
		return ;
	}
	while (get_pars()->cub_file_list != node)
		get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
	while (*(char *)(get_pars()->cub_file_list->data) == '\0')
		get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
}

extern int		texture_vld_chk(char *direction, char *texture_line);
extern char		*get_textrue_name(char *texture_line);
extern int		bg_color_vld_chk(char *floor_or_ceiling, char *bg_line);
extern t_rgb	get_rgb(char *str, char type);

static int	run_pars_with_vld_chk(t_dnode *node)
{
	t_pars	*pars_struct;

	pars_struct = get_pars();
	if (texture_vld_chk("NO", node->data) && !get_pars()->north_texture)
		pars_struct->north_texture = get_textrue_name(node->data);
	else if (texture_vld_chk("SO", node->data)
		&& !get_pars()->south_texture)
		pars_struct->south_texture = get_textrue_name(node->data);
	else if (texture_vld_chk("WE", node->data) && !get_pars()->west_texture)
		pars_struct->west_texture = get_textrue_name(node->data);
	else if (texture_vld_chk("EA", node->data) && !get_pars()->east_texture)
		pars_struct->east_texture = get_textrue_name(node->data);
	else if (bg_color_vld_chk("F", node->data))
		pars_struct->floor = get_rgb(node->data, 'F');
	else if (bg_color_vld_chk("C", node->data))
		pars_struct->ceiling = get_rgb(node->data, 'C');
	else if (*(char *)(node->data) != '\0')
	{
		if (!is_data_filled())
			pars_struct->pars_errno = TYPE_IDENTIFIER_ERR;
		return (1);
	}
	return (0);
}

static void	pars_with_vld_chk(t_dnode *node)
{
	int		flag;

	flag = 0;
	while (node)
	{
		flag = run_pars_with_vld_chk(node);
		if (flag)
			break ;
		node = node->next_node;
	}
	set_node_ptr_to_map_line(node);
}

extern int		try_open(char *file_name);
extern int		file_format_chk(char *format, char *file_name);
extern void		gnl_cub_file( void );
extern void		map_vld_chk(void);

int	pars_file_vld_chk( void )
{
	if (get_pars()->argc != 2)
		get_pars()->pars_errno = 1;
	if (get_pars()->pars_errno)
		return (1);
	if (!file_format_chk(".cub", get_pars()->argv[1]))
		get_pars()->pars_errno = 2;
	if (get_pars()->pars_errno)
		return (get_pars()->pars_errno);
	if (!try_open(get_pars()->argv[1]))
		get_pars()->pars_errno = 3;
	if (get_pars()->pars_errno)
		return (get_pars()->pars_errno);
	gnl_cub_file();
	if (get_pars()->pars_errno)
		return (get_pars()->pars_errno);
	pars_with_vld_chk(get_pars()->cub_file_list);
	map_vld_chk();
	return (get_pars()->pars_errno);
}
