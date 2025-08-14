/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 07:33:18 by hoysong           #+#    #+#             */
/*   Updated: 2025/08/15 07:33:19 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser/pars_pub.h"
#include "./mlx_stuff/mlx_hdler.h"
#include "./minilibx-linux/mlx.h"

int	main(int argc, char **argv)
{
	pars_init(argc, argv);
	if (pars_file_vld_chk())
	{
		pars_perror();
		pars_destroy();
		return (1);
	}
	else
		pars_map();
	if (setup_mlx())
	{
		pars_perror();
		mlx_destroy();
		pars_destroy();
		return (1);
	}
	put_frame();
	mlx_loop(mlx()->mlx_ptr);
	mlx_destroy();
	pars_destroy();
}
