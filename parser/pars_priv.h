#ifndef PARS_PRIV_H
# define PARS_PRIV_H
# include "../my_libft/libft.h"
# include "./pars_errno.h"

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
} t_rgb;

typedef struct	s_pars
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
}	t_pars;

t_pars	*get_pars( void );

#endif
