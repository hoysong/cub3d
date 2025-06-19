#include "../pars_priv.h"
//#include "../../my_libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

extern size_t	get_max_length(void);
extern size_t	get_max_height(void);
extern char		**gen_map(size_t max_length, size_t max_height);
extern void		pars_texture(void);
extern void		pars_floor_ceiling(void);

void	pars_cub_file(void)
{
	// linked list 다시 원점으로.
	get_pars()->cub_file_list = find_head_dubly(get_pars()->cub_file_list);
	// 텍스쳐 파싱하기.
	pars_texture();
	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
	// 바닥/천장 색상 파싱하기.
	pars_floor_ceiling();
	get_pars()->cub_file_list = get_pars()->cub_file_list->next_node;
	// 맵 파싱하기.
	printf("get map from cubfile.\n");
	get_pars()->map = gen_map(get_max_length(), get_max_height());

	printf("north   : %s\n", get_pars()->north_texture);
	printf("south   : %s\n", get_pars()->south_texture);
	printf("west    : %s\n", get_pars()->west_texture);
	printf("east    : %s\n", get_pars()->east_texture);
	printf("floor   : %d %d %d\n", get_pars()->floor.red, get_pars()->floor.green, get_pars()->floor.blue);
	printf("ceiling : %d %d %d\n", get_pars()->ceiling.red, get_pars()->ceiling.green, get_pars()->ceiling.blue);
	print_splits(get_pars()->map);
}
