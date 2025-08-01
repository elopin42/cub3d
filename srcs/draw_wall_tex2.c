/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_tex2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:56:14 by elopin            #+#    #+#             */
/*   Updated: 2025/07/27 17:56:39 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

unsigned int	apply_distance_effect(unsigned int color, double dist)
{
	double	d;
	double	factor;

	if (dist > 1.0)
	{
		d = dist - 1.0;
		factor = 1.0 / (d * d * d + 1.0);
		if (factor < 0.02)
			factor = 0.02;
		color = effet_noir(color, factor);
	}
	return (color);
}

unsigned int	get_normal_wall_color(t_global *glb, t_img *tex,
		int tex_x, int tex_y)
{
	char			*pixel;
	unsigned int	color;

	pixel = tex->addr + tex_y * tex->line_length + tex_x * (tex->bpp / 8);
	color = *(unsigned int *)pixel;
	return (apply_distance_effect(color, glb->ray.perp_wall_dist));
}

unsigned int	handle_door_opening(t_global *glb, int x, int y)
{
	glb->el_muros_invisible = 0;
	calculate_secondary_ray(glb);
	if (y >= glb->door_params->tmp_draw_start
		&& y <= glb->door_params->tmp_draw_end)
		return (draw_wall_behind_door(glb, y));
	else if (y < glb->door_params->tmp_draw_start)
		return (handle_sky_part(glb, x, y));
	else
		return (handle_floor_part(glb, y));
}

void	calculate_texture_params(t_global *glb, t_img *tex, int *tex_x,
		double *step)
{
	double	wall_x;

	if (glb->ray.side == 0)
		wall_x = glb->player.y + glb->ray.perp_wall_dist
			* glb->ray.ray_dir_y;
	else
		wall_x = glb->player.x + glb->ray.perp_wall_dist
			* glb->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * tex->width);
	if (glb->ray.side == 0 && glb->ray.ray_dir_x > 0)
		*tex_x = tex->width - *tex_x - 1;
	if (glb->ray.side == 1 && glb->ray.ray_dir_y < 0)
		*tex_x = tex->width - *tex_x - 1;
	*step = (double)tex->height / glb->ray.line_height;
}
