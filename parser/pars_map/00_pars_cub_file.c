#include "../pars_priv.h"
#include "../pars_pub.h"
#include <stdio.h>
#include <fcntl.h>

inline char	**get_map(void)
{
	return (get_pars()->map);
}

extern char		**gen_map(size_t max_length, size_t max_height);

void	pars_map(void)
{
	get_pars()->map_max_length = get_max_length();
	get_pars()->map_max_height = get_max_height();
	get_pars()->map = gen_map(get_max_length(), get_max_height());
}
