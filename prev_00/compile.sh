FLAG="-Wall -Wextra -Werror -g"
cc $FLAG \
	./main.c \
	./00_map_vld_chk.c \
	./01_is_vld_file_format.c \
	./my_libft/libft.a
