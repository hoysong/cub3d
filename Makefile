# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/15 02:44:18 by jinyjeon          #+#    #+#              #
#    Updated: 2025/08/15 07:05:00 by jinyjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = ./parser/00_pars_init.c \
	  ./parser/pars_perror_msg.c \
	  ./parser/pars_map/00_pars_cub_file.c \
	  ./parser/pars_map/gen_map.c \
	  ./parser/vld_chk/01_pars_file_vld_chk.c \
	  ./parser/vld_chk/02_gnl_cub_file.c \
	  ./parser/vld_chk/03_map_vld_chk.c \
	  ./parser/vld_chk/04_surround_chk.c \
	  ./parser/vld_chk/04_surround_chk_utils.c \
	  ./parser/vld_chk/05_pars_perror.c \
	  ./parser/vld_chk/color_and_texture_vld_chk.c \
	  ./parser/vld_chk/get_texture_color.c \
	  ./parser/vld_chk/vld_utils.c \
	  ./mlx_stuff/00_setup_mlx.c \
	  ./mlx_stuff/00_setup_mlx_utils.c \
	  ./mlx_stuff/01_set_get_mlx.c \
	  ./mlx_stuff/02_make_floor_ceiling_image.c \
	  ./mlx_stuff/04_make_minimap.c \
	  ./mlx_stuff/04_make_minimap_utils.c \
	  ./mlx_stuff/05_player_init.c \
	  ./mlx_stuff/99_my_utils.c \
	  ./mlx_stuff/99_put_xxx.c \
	  ./mlx_stuff/hook_hdler.c \
	  ./mlx_stuff/hook_hdler_utils.c \
	  ./mlx_stuff/player_hdler.c \
	  ./mlx_stuff/algorithm/algorithm_utils.c \
	  ./mlx_stuff/algorithm/detect_wall_hit.c \
	  ./mlx_stuff/algorithm/ray_functions.c \
	  ./mlx_stuff/algorithm/wall_lkd_list/wall_lkd_list_hdler.c \
	  ./mlx_stuff/algorithm/wall_lkd_list/wall_lkd_list_node_hdler.c \
	  ./mlx_stuff/raycasting/calculation.c \
	  ./mlx_stuff/raycasting/calculation_getline_utils.c \
	  ./mlx_stuff/raycasting/draw_wall_lkd_list.c \
	  ./mlx_stuff/raycasting/draw_wall_lkd_list_utils.c \
	  ./mlx_stuff/raycasting/ray_casting.c \
	  ./mlx_stuff/raycasting/shoot_fov_ray.c \
	  ./mlx_stuff/raycasting/shoot_fov_ray_utils.c \
	  ./mlx_stuff/raycasting/sort_wall_list.c \
	  ./main.c

OBJ = $(SRC:%.c=%.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
		make -C my_libft all
		make -C minilibx-linux all
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm -L./my_libft -lft

clean :
		rm -rf $(OBJ)
		make -C my_libft fclean
		make -C minilibx-linux clean

fclean : clean
		rm -rf $(NAME)

re :
		$(MAKE) fclean
		$(MAKE) all

.PHONY: clean fclean re all
