/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_tex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:57:45 by elopin            #+#    #+#             */
/*   Updated: 2025/09/11 17:02:15 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	calculate_secondary_ray(t_global *glb)
{
	if (glb->door_params.ray_calculated)
		return ;
	glb->door_params.tmp_ray = glb->ray;
	perform_dda_ignoring_doors(glb, &glb->door_params.tmp_ray);
	if (glb->door_params.tmp_ray.side == 0)
		glb->door_params.tmp_dist = (glb->door_params.tmp_ray.map_x
				- glb->player.x + (1 - glb->door_params.tmp_ray.step_x) / 2)
			/ glb->door_params.tmp_ray.ray_dir_x;
	else
		glb->door_params.tmp_dist = (glb->door_params.tmp_ray.map_y
				- glb->player.y + (1 - glb->door_params.tmp_ray.step_y) / 2)
			/ glb->door_params.tmp_ray.ray_dir_y;
	glb->door_params.tmp_line_height = (int)(glb->h
			/ glb->door_params.tmp_dist);
	glb->door_params.tmp_draw_start = -glb->door_params.tmp_line_height / 2
		+ glb->h / 2;
	glb->door_params.tmp_draw_end = glb->door_params.tmp_line_height / 2
		+ glb->h / 2;
	if (glb->door_params.tmp_draw_start < 0)
		glb->door_params.tmp_draw_start = 0;
	if (glb->door_params.tmp_draw_end >= glb->h)
		glb->door_params.tmp_draw_end = glb->h - 1;
	glb->door_params.tmp_tex = select_wall_texture_from_ray(glb,
			&glb->door_params.tmp_ray);
	glb->door_params.ray_calculated = true;
}

static double	door_wall_x(t_global *glb)
{
	t_ray	*r;
	double	w;

	r = &glb->door_params.tmp_ray;
	if (r->side == 0)
		w = glb->player.y
			+ glb->door_params.tmp_dist * r->ray_dir_y;
	else
		w = glb->player.x
			+ glb->door_params.tmp_dist * r->ray_dir_x;
	w -= floor(w);
	return (w);
}

static int	door_tex_x(t_global *glb, double wall_x)
{
	t_ray	*r;
	t_img	*tex;
	int		tx;

	r = &glb->door_params.tmp_ray;
	tex = glb->door_params.tmp_tex;
	tx = (int)(wall_x * tex->width);
	if (r->side == 0 && r->ray_dir_x > 0)
		tx = tex->width - tx - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		tx = tex->width - tx - 1;
	if (tx < 0)
		tx = 0;
	if (tx >= tex->width)
		tx = tex->width - 1;
	return (tx);
}

static int	door_tex_y(t_global *glb, int y)
{
	t_img	*tex;
	double	step;
	int		ty;

	tex = glb->door_params.tmp_tex;
	step = (double)tex->height
		/ (double)glb->door_params.tmp_line_height;
	ty = (int)((y - glb->door_params.tmp_draw_start) * step);
	if (ty < 0)
		ty = 0;
	if (ty >= tex->height)
		ty = tex->height - 1;
	return (ty);
}

unsigned int	draw_wall_behind_door(t_global *glb, int y)
{
	t_img			*tex;
	double			wall_x;
	int				tx;
	int				ty;
	unsigned int	color;

	tex = glb->door_params.tmp_tex;
	wall_x = door_wall_x(glb);
	tx = door_tex_x(glb, wall_x);
	ty = door_tex_y(glb, y);
	color = *(unsigned int *)(tex->addr
			+ ty * tex->line_length
			+ tx * (tex->bpp / 8));
	return (apply_distance_effect(color,
			glb->door_params.tmp_dist, glb->light_pwr));
}
