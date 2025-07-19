clang ./main.c\
	./parser/*.c \
	./parser/pars/*.c \
	./parser/vld_chk/*.c \
	./mlx_stuff/*.c \
	./mlx_stuff/algorithm/*.c\
	./mlx_stuff/algorithm/wall_lkd_list/*.c\
	-g -lm -L./my_libft -lft -Lminilibx-linux -lmlx_Linux -lX11 -lXext
