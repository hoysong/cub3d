/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:07:21 by hoysong           #+#    #+#             */
/*   Updated: 2024/12/04 17:38:35 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include "./linked_list/lkdlist.h"
# include "./ft_printf/libftprintf.h"
# include "./ft_slice/slice.h"
# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void		*content;
	void		*next;
}				t_list;
int		ft_isalpha(int num);
int		ft_isdigit(int num);
int		ft_isalnum(int num);
int		ft_isascii(int num);
int		ft_isprint(int num);
size_t	ft_strlen(const char *dest);
void	*ft_calloc(size_t num, size_t size);
void	*ft_memset(void *dest, int n_src, unsigned long len);
void	ft_bzero(void *dest, size_t num);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t maxlen);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *s);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*get_next_line(int fd);
t_dnode	*get_gnl_node(int fd);
int		ft_is_str_digit(char *str);

/*
 *	1. Description.
 *	For print split elements.
 *	Parameter type is (char **).
 *	This means, 'this function is not only for splits'.
 *	'Any char **str can be printed'.
 */
void	print_splits(char **str);

/*
 *	1. Description.
 *	This function can free ft_split's return value(char **).
 *	This means, any char **str can be freed.
 *	NOTICE! last of element MUST be NULL.
 *	ex).
 *	 str[0]hello.
 *	 str[1]world!.
 *	 str[2](NULL)
 */
void	free_splits(char **splits);

/*
 *	1. Description.
 *	This function split argv.
 *	after split, put (char **)str to 'node->data'.
 *	2. return_value.
 *	head of split_lkd_list.
 *	NULL(0) if malloc fail.
 */
t_dnode	*make_split_lkd_list(char **argv);

/*
 *	1. Description.
 *	This function will print split_lkd_list.
 *	print with 'ft_printf'.
 *	2. return_value
 *	none.
 */
void	print_split_lkd_list(t_dnode *split_node);

/*
 *	1. Description.
 *	This function free split lkd_list.
 *	perfect parameter: return value of 'make_split_lkd_list'.
 *	for this function, t_dnode's data 'MUST BE' char **.
 */
void	free_split_lkd_list(t_dnode *split_node);
#endif
