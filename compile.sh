FLAG="-Wall -Wextra -Werror -g"
cc $FLAG \
	./main.c \
	./00_file_format_chk.c \
	./my_libft/libft.a
