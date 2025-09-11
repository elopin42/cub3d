/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_tex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:57:45 by elopin            #+#    #+#             */
/*   Updated: 2025/09/11 14:10:40 by elopin           ###   ########.fr       */
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

unsigned int	draw_wall_behind_door(t_global *glb, int y)
{
	double			tmp_wall_x;
	double			tmp_step;
	int				tmp_tex_x;
	int				tmp_tex_y;
	unsigned int	color;
	t_ray			*r = &glb->door_params.tmp_ray;
	t_img			*tex = glb->door_params.tmp_tex;

	if (r->side == 0)
		tmp_wall_x = glb->player.y + glb->door_params.tmp_dist * r->ray_dir_y;
	else
		tmp_wall_x = glb->player.x + glb->door_params.tmp_dist * r->ray_dir_x;
	tmp_wall_x -= floor(tmp_wall_x);
	tmp_tex_x = (int)(tmp_wall_x * tex->width);
	if (r->side == 0 && r->ray_dir_x > 0)
		tmp_tex_x = tex->width - tmp_tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		tmp_tex_x = tex->width - tmp_tex_x - 1;
	if (tmp_tex_x < 0) tmp_tex_x = 0;
	if (tmp_tex_x >= tex->width) tmp_tex_x = tex->width - 1;
	tmp_step = (double)tex->height / (double)glb->door_params.tmp_line_height;
	tmp_tex_y = (int)((y - glb->door_params.tmp_draw_start) * tmp_step);
	if (tmp_tex_y < 0) tmp_tex_y = 0;
	if (tmp_tex_y >= tex->height) tmp_tex_y = tex->height - 1;

	color = *(unsigned int *)(tex->addr
		+ tmp_tex_y * tex->line_length
		+ tmp_tex_x * (tex->bpp / 8));

	return apply_distance_effect(color, glb->door_params.tmp_dist, glb->light_pwr);
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

	double dist = (double)glb->h / (2.0 * (double)y - (double)glb->h);
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
