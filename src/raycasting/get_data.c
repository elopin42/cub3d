#include "../../include/cub3d.h"

int	get_tex_x(t_global *glb, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * glb->door_params.tmp_tex->width);
	if (glb->door_params.tmp_ray.side == 0
		&& glb->door_params.tmp_ray.ray_dir_x > 0)
		tex_x = glb->door_params.tmp_tex->width - tex_x - 1;
	if (glb->door_params.tmp_ray.side == 1
		&& glb->door_params.tmp_ray.ray_dir_y < 0)
		tex_x = glb->door_params.tmp_tex->width - tex_x - 1;
	return (tex_x);
}

int	get_tex_y(t_global *glb, int y, double step)
{
	double	tex_pos;
	int		tex_y;

	tex_pos = (glb->door_params.tmp_draw_start - glb->h / 2
			+ glb->door_params.tmp_line_height / 2) * step;
	tex_pos += (y - glb->door_params.tmp_draw_start) * step;
	tex_y = (int)tex_pos % glb->door_params.tmp_tex->height;
	if (tex_y < 0)
		tex_y += glb->door_params.tmp_tex->height;
	return (tex_y);
}

