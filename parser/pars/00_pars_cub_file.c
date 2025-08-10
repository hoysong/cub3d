#include "../pars_priv.h"
#include "../pars_pub.h"
#include <stdio.h>
#include <fcntl.h>

inline char	**get_map(void)
{
	return (get_pars()->map);
}

extern char		**gen_map(size_t max_length, size_t max_height);

static void	print_map_info()
{
	printf("north   : %s\n", get_pars()->north_texture);
	printf("south   : %s\n", get_pars()->south_texture);
	printf("west    : %s\n", get_pars()->west_texture);
	printf("east    : %s\n", get_pars()->east_texture);
	printf("floor   : %d %d %d\n", get_pars()->floor.red, get_pars()->floor.green, get_pars()->floor.blue);
	printf("ceiling : %d %d %d\n", get_pars()->ceiling.red, get_pars()->ceiling.green, get_pars()->ceiling.blue);
	print_splits(get_pars()->map);
}

void	pars_cub_file(void)
{
	get_pars()->map_max_length = get_max_length();
	get_pars()->map_max_height = get_max_height();
	get_pars()->map = gen_map(get_max_length(), get_max_height());
	print_map_info();
}
