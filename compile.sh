cc ./main.c\
	./parser/*.c \
	./parser/pars/*.c \
	./parser/vld_chk/*.c \
	./mlx_stuff/*.c \
	-g -L./my_libft -lft -Lminilibx-linux -lmlx_Linux -lX11 -lXext
