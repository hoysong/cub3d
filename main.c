#include "pars_pub.h"

int	pars_file_vld_chk( void );

int	main(int argc, char **argv)
{
	int	flag;

	pars_init(argc, argv);
	if (pars_file_vld_chk() != 0)
	{
		pars_destroy();
		return (1);
	}
	pars_destroy();
}
