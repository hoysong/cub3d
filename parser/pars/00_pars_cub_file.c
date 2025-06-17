#include "../pars_priv.h"
//#include "../../my_libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

extern size_t	get_max_length(void);
extern size_t	get_max_height(void);
extern char		**gen_map(size_t max_length, size_t max_height);

void	pars_cub_file(void)
{
	get_pars()->cub_file_list = find_head_dubly(get_pars()->cub_file_list);
	printf("get map from cubfile.\n");
	get_pars()->map = gen_map(get_max_length(), get_max_height());
}
