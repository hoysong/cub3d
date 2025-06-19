#ifndef PARS_PUB_H
# define PARS_PUB_H
# include "pars_errno.h"
# include <stddef.h>

/*pars를 생성하거나 파괴합니다.*/
void	pars_init(int argc, char **argv);
void	pars_destroy( void );

/*유효성 검사를 실행합니다.*/
int		pars_file_vld_chk( void );

/*에러가 있는 경우 에러를 출력합니다.*/
void	pars_perror(void);

/* 파싱합니다.*/
/* 유효성 검사 이후 사용합니다.*/
/* get_pars()함수를 통해 파싱 데이터에 접근할 수 있습니다.*/
/* get_pars()는 pars_priv.h 헤더를 include하면 사용 가능합니다.*/
void	pars_cub_file(void);

/*(char **)map을 리턴합니다.*/
char	**get_map(void);

/*맵의 최대 폭을 구합니다.*/
/* map은 get_pars()의 char ** 타입으로 저장되어 있습니다.*/
size_t	get_max_length(void);
/* 맵의 최대 높이를 구합니다.*/
/* map은 get_pars()의 char ** 타입으로 저장되어 있습니다.*/
size_t	get_max_height(void);

#endif
