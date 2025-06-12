/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:07:21 by hoysong           #+#    #+#             */
/*   Updated: 2024/12/05 16:30:48 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLICE_H
# define SLICE_H
# include "../linked_list/lkdlist.h"
/*
 *	== slice_init_node ==.
 *	1. description.
 *		this function initialize node and insert it's data with 'str'.
 *	2. return value.
 *		allocated node and strdup 'str' it's data.
 */
t_dnode	*slice_init_node(char *str);

/*
 *	== slice ==.
 *	1. description.
 *		This function slice node's string with slice_str.
 *	2. return value.
 *		returns head of sliced nodes.
 *		The return value can be free by destroy_doubly_list() in lkdlist.h.
 */
t_dnode	*slice(t_dnode *node, char *slice_str);
/*
 *	== print_slice_list ==.
 *	1. description.
 *		this function print slice_list.
 *	2. return value.
 *		none.
 */
void	print_slice_list(t_dnode *node);
#endif
