#include "./player.h"
#include "./mlx_hdler.h"
#include <math.h>
#include <stdio.h>

static float	my_abs(float num)
{
	if (num < 0)
		return (num *= -1);
	return (num);
}

void shoot_ray()
{
  float x;
  float y;
  float x1 = player()->x * get_minimap_ratio();
  float y1 = player()->y * get_minimap_ratio();
  float x2 = player()->ratio;
  float y2 = player()->ratio;
  float dx, dy, step;
  int	i = 0;
  
  dx = (x2 - x1);
  dy = (y2 - y1);

  if (my_abs(dx) >= my_abs(dy))
    step = my_abs(dx);
  else
    step = my_abs(dy);

  dx = dx / step;
  dy = dy / step;
  x = x1;
  y = y1;
  i = 0;

	while (i <= step)
	{
		put_pixel_to_img(&(mlx()->minimap), x, y,0x0000ff);
		printf("%f %f\n", round(x), round(y));
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
}
