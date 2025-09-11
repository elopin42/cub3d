/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_tex_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:39:34 by elopin            #+#    #+#             */
/*   Updated: 2025/09/11 17:01:59 by elopin           ###   ########.fr       */
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

unsigned int	handle_sky_part(t_global *glb, int x, int y)
{
	int		tex_x_sky;
	int		tex_y_sky;
	char	*pixel_sky;

	tex_x_sky = (x * glb->texture.sky.width) / glb->w;
	tex_y_sky = (y * glb->texture.sky.height) / (glb->h / 2);
	pixel_sky = glb->texture.sky.addr + (tex_y_sky
			* glb->texture.sky.line_length + tex_x_sky * (glb->texture.sky.bpp
				/ 8));
	return (*(unsigned int *)pixel_sky);
}

unsigned int	handle_floor_part(t_global *glb, int y)
{
	double			floor_x;
	double			floor_y;
	unsigned int	color;
	int				tex_x_floor;
	int				tex_y_floor;

	double (dist) = (double)glb->h / (2.0 * (double)y - (double)glb->h);
	if (dist < 0.0)
		dist = 0.0;
	if (glb->texture.sol.is_rgb == false)
	{
		floor_x = glb->player.x + dist * glb->ray.ray_dir_x;
		floor_y = glb->player.y + dist * glb->ray.ray_dir_y;
		tex_x_floor = (int)(floor_x * glb->texture.sol.width)
			% glb->texture.sol.width;
		tex_y_floor = (int)(floor_y * glb->texture.sol.height)
			% glb->texture.sol.height;
		color = *(unsigned int *)(glb->texture.sol.addr + tex_y_floor
				* glb->texture.sol.line_length + tex_x_floor
				* (glb->texture.sol.bpp / 8));
	}
	else
		color = ft_uni(glb->texture.sol.rgb);
	return (apply_distance_effect(color, dist, glb->light_pwr));
}
