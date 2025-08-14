/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_hdler_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 04:37:31 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/15 06:12:36 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "./player.h"

int	destroy_notify_hook(void *hi)
{
	(void)hi;
	mlx_loop_end(mlx()->mlx_ptr);
	return (0);
}
