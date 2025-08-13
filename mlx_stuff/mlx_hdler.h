/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hdler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 04:46:21 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 04:47:47 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_HDLER_H
# define MLX_HDLER_H
# include "./cub_defs.h"
# include "../parser/pars_priv.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stddef.h>

typedef struct s_point	t_point;

/*
 * data_addr: img's actual start address.
 * img_ptr: this contains img's mlx content.
 */
typedef struct s_img
{
	char	*data_addr;
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		xpm_width;
	int		xpm_height;
}t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_window;
	t_img	xpm_north;
	t_img	xpm_south;
	t_img	xpm_west;
	t_img	xpm_east;
	int		ceiling_color;
	int		floor_color;
	t_img	background;
	t_img	minimap;
	int		toggle_mouse;
	int		toggle_minimap;
	t_pars	*pars;
	size_t	minimap_square;
}t_mlx;
/*setup t_mlx struct*/
int		setup_mlx(void);
/*It returns t_mlx struct*/
t_mlx	*mlx(void);
/*This Function destroys t_mlx struct.*/
void	mlx_destroy(void);
/*this funetion invoke 'mlx_get_data_addr()' internally.*/
void	get_img_data(t_img *img);
/*put pixel on images hoiz and vert loation.*/
void	put_pixel_to_img(t_img *img, int horiz, int vert, int color);
/*deploy prepared image to window.*/
void	put_background(t_mlx *mlx_strc);
/*reutrns minimap's ratio.*/
size_t	get_minimap_ratio(void);
/*put_minimap to window.*/
void	put_minimap(t_mlx *mlx_strc);
/*put_player to window.*/
void	put_player(void);
/*Put frame..*/
void	put_frame(void);
/*Get xpm img's pixel color..*/
int		get_xpm_pixel_color(t_img xpm, t_point pixel);

#endif
