#include "../cub_defs.h"
#include "../algorithm/my_algorithm.h"

/*ray를 가로 대각선으로 조사하며 세로축의 선을 그려내는 로직이다.*/
static inline int	put_texture(t_point ray, t_point y, void *param)
{
	ray.y = (int)ray.y;
	float		lower_point = ((float)(WIN_HEIGHT >> 1)) + (((float)(WIN_HEIGHT >> 1)) - ray.y);
	t_wall_node	*node = param;
	t_point		start_ray = ray;
	t_point		pixel = ray;

	if (ray.x < 0)
		return (0);
	else if (ray.x >= WIN_WIDTH)
		return (1);
	if (node->start_degree <= 0)
		pixel.x = node->texture->xpm_width * ((ray.x - (node->end_point.x - node->wall_width)) / node->wall_width);
	else
		pixel.x = node->texture->xpm_width * ((ray.x - node->start_point.x) / node->wall_width);
	if (ray.y < 0)
		ray.y = 0;
	while ((ray.y < lower_point) && ray.y < WIN_HEIGHT)
	{
		//pixel.y = node->texture->xpm_height * ((ray.y - start_ray.y) / ((WIN_HEIGHT >> 1) + ((WIN_HEIGHT >> 1) - start_ray.y) - start_ray.y));
		pixel.y = node->texture->xpm_height * ((ray.y - start_ray.y) / (HALF_WIN_HEIGHT + (HALF_WIN_HEIGHT - start_ray.y) - start_ray.y));
		put_pixel_to_img(&(node->info->mlx->background), ray.x, ray.y,
				get_xpm_pixel_color(*(node->texture), pixel)
				);
		ray.y += 1;
	}
//	put_background(mlx());
//	usleep(6000);
	return (0);
}

/*This function will put textures.*/
void	draw_wall_lkd_list(t_wall_node *node)
{
	t_mlx	*mlx_ptr = mlx();

	while (node)
	{
		shoot_ray(node->start_point, node->end_point, node, put_texture);
		node = node->next;
	}
}
