/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation_getline_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyjeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 06:51:02 by jinyjeon          #+#    #+#             */
/*   Updated: 2025/08/14 07:00:56 by jinyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../player.h"
#include "../algorithm/my_algorithm.h"
#include <math.h>

float	get_vertlen(t_point a, t_point b, t_point c)
{
	float	m;
	float	result;

	if (b.x - a.x == 0)
		m = (b.y - a.y) / ((b.x + 0.01) - a.x);
	else
		m = (b.y - a.y) / (b.x - a.x);
	result = my_abs(m * c.x - c.y + (a.y - (m * a.x))) / sqrt(pow(m, 2) + 1);
	return (result);
}

/*convert texture point.y coordinate to screen coordinate.*/
float	get_line_y(t_point point)
{
	float	vert_len;
	float	inverse;

	vert_len = get_vertlen(
			player()->cord,
			rotate_point(player()->cord, player()->view_point, 90),
			point);
	inverse = (SIZE_OF_BLOCK * WIN_HEIGHT) / vert_len;
	inverse = (float)(HALF_WIN_HEIGHT - (inverse / 2));
	return (inverse);
}

/*convert texture point.x coordinate to screen coordinate.*/
int	get_line_x(float degree)
{
	float	degree_to_percent;
	float	line_location;

	degree_to_percent = degree / PLAYER_FOV * 100;
	line_location = WIN_WIDTH * (degree_to_percent / 100);
	if (line_location == WIN_WIDTH)
		line_location = WIN_WIDTH - 1;
	return (line_location);
}
