/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_tex_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:39:34 by elopin            #+#    #+#             */
/*   Updated: 2025/09/10 17:10:54 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_texture_vars(t_global *glb, t_img *tex, t_texture_vars *vars)
{
	calculate_texture_params(glb, tex, &vars->tex_x, &vars->step);
	vars->tex_pos = (glb->ray.draw_start - glb->h / 2 + glb->ray.line_height
			/ 2) * vars->step;
	vars->door_anim = (glb->map_clone[glb->ray.map_y][glb->ray.map_x] == '3');
	vars->clip_height = glb->anim_door;
	if (vars->clip_height > glb->door_height)
		vars->clip_height = glb->door_height;
	vars->white_start = glb->door_start_y;
	vars->white_end = vars->white_start + vars->clip_height;
}

static unsigned int	get_wall_pixel_color(t_global *glb, t_img *tex,
		t_texture_vars *vars)
{
	unsigned int	color;

	if (vars->door_anim && vars->y >= vars->white_start
		&& vars->y < vars->white_end)
		color = handle_door_opening(glb, vars->x, vars->y);
	else
	{
		glb->el_muros_invisible = 1;
		color = get_normal_wall_color(glb, tex, vars->tex_x, vars->tex_y);
	}
	return (color);
}

void	draw_wall_texture(t_global *glb, int x, t_img *tex)
{
	t_texture_vars	vars;
	unsigned int	color;
	int				y;

	init_texture_vars(glb, tex, &vars);
	glb->door_params.ray_calculated = false;
	y = glb->ray.draw_start - 1;
	while (++y < glb->ray.draw_end)
	{
		vars.tex_y = (int)vars.tex_pos % tex->height;
		if (vars.tex_y < 0)
			vars.tex_y += tex->height;
		vars.tex_pos += vars.step;
		vars.y = y;
		vars.x = x;
		color = get_wall_pixel_color(glb, tex, &vars);
		put_pixel(&glb->img, x, y, color);
	}
}
