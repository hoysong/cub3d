#include "./parser/pars_pub.h"

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
		pars_cub_file();
	pars_destroy();
}
