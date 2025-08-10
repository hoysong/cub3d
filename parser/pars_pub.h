#ifndef PARS_PUB_H
# define PARS_PUB_H
# include "pars_errno.h"
# include <stddef.h>

/* initialize/destroy pars struct.*/
void	pars_init(int argc, char **argv);
void	pars_destroy( void );

/*run valid check.*/
int		pars_file_vld_chk( void );

/*pars_perror.*/
void	pars_perror(void);

/* after validation check ray_pars.*/
/* with get_pars() function can contact to t_pars struct.*/
/* to use get_pars() function, you must include pars_priv.h */
void	pars_cub_file(void);

/*it return (char **)map.*/
char	**get_map(void);

/*get longest length of (char **)map string.*/
size_t	get_max_length(void);

/* get height of (char **)map.*/
size_t	get_max_height(void);

#endif
