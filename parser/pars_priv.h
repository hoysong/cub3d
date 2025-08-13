/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_priv.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:32:33 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 02:34:08 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_PRIV_H
# define PARS_PRIV_H
# include "../my_libft/libft.h"
# include "./pars_errno.h"

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_pars
{
	int		argc;
	char	**argv;
	int		pars_errno;
	t_dnode	*cub_file_list;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_rgb	floor;
	t_rgb	ceiling;
	char	**map;
	size_t	map_max_length;
	size_t	map_max_height;
	int		floor_parsed_flag;
	int		ceiil_parsed_flag;
}	t_pars;

t_pars	*get_pars( void );
int		is_player(char c);
void	malloc_fail_perror(void);

#endif
