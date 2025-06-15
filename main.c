
typedef struct	s_pars
{
	int	argc;
	char	**argv;
	int	pars_errno;
}	t_pars;

void	pars_init(t_pars *pars)
{
	pars->pars_errno = 0;
}

void	pars_map_vld_chk(int argc, char **argv)
{
	if (argc != 2)
		return (2);
	return (1);
}

int	pars_get_errno(void *arg)
{
	static t_pars	*pars;

	if (pars != NULL)
		pars = arg;
	return (pars->pars_errno);
}

void	pars_perror(int pars_errno)
{
	int	(*pars_init)(void *);
}

/*
 * All valid check functions will return 1 if case is valid.
 * Otherwise it will return bigger then 1.
 * bigger then 1 can be error code.
 * 2: argument error
 * 	arguments must be only one.
 * 3: 
 */

int	main(int argc, char **argv)
{
	t_pars	pars;

	pars_init(argc, argv);
	pars_vld_chk(argc, argv);
}
