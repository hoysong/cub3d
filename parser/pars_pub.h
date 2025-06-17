#ifndef PARS_PUB_H
# define PARS_PUB_H
# include "pars_errno.h"

/*pars를 생성하거나 파괴합니다.*/
void	pars_init(int argc, char **argv);
void	pars_destroy( void );

/*유효성 검사를 실행합니다.*/
int		pars_file_vld_chk( void );

/*에러가 있는 경우 에러를 출력합니다.*/
void	pars_perror(void);

/* 파싱합니다.
 * 유효성 검사 이후 사용합니다.
 */
void	pars_cub_file(void);

#endif
