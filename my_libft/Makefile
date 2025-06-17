SRCS = \
	ft_split.c        \
		split_hdler.c \
	ft_atoi.c       \
	ft_strchr.c     \
	ft_bzero.c      \
	ft_strdup.c     \
	ft_calloc.c     \
	ft_striteri.c   \
	ft_isalnum.c    \
	ft_strjoin.c    \
	ft_isalpha.c    \
	ft_strlcat.c    \
	ft_isascii.c    \
	ft_isdigit.c    \
	ft_strlcpy.c    \
	ft_isprint.c    \
	ft_strlen.c     \
	ft_itoa.c       \
	ft_strmapi.c    \
	ft_memchr.c     \
	ft_strncmp.c    \
	ft_memcmp.c     \
	ft_strnstr.c    \
	ft_memcpy.c     \
	ft_memmove.c    \
	ft_strrchr.c    \
	ft_memset.c     \
	ft_strtrim.c    \
	ft_putchar_fd.c \
	ft_substr.c     \
	ft_putendl_fd.c \
	ft_tolower.c    \
	ft_putnbr_fd.c  \
	ft_toupper.c    \
	ft_putstr_fd.c  \
	ft_is_str_digit.c \
		get_next_line.c \
		get_gnl_node.c  \
			./linked_list/doubly_lkdlist.c         \
			./linked_list/doubly_lkdlist_destroy.c \
			./linked_list/singly_lkdlist.c         \
			./linked_list/insert_doubly_data.c     \
				./ft_printf/ft_printf.c     \
				./ft_printf/libft_fd.c      \
				./ft_printf/nbr_base.c      \
				./ft_printf/sign_nbr_base.c \
				./ft_slice/ft_slice.c       \
				./ft_slice/ft_slice_utils.c \
					name_gen.c

GRN = "\e[1;32m
END = \e[0m"

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

AR = ar -U -r -u -s 

NAME = libft.a

$(NAME): $(OBJS)
	@echo $(GRN)Make libft.a$(END)
	$(AR) $@ $(OBJS)

all: $(NAME)
	@echo $(GRN)Make done.$(END)

RM = rm -f

clean:
	@echo $(GRN)Make clean.$(END)
	$(RM) $(OBJS)
fclean: clean
	@echo $(GRN)Make fclean.$(END)
	$(RM) $(NAME)

re: fclean
	@echo $(GRN)Make re.$(END)
	make all

.PHONY: all clean fclean re
