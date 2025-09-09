/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_tex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:57:45 by elopin            #+#    #+#             */
/*   Updated: 2025/09/09 17:25:24 by elopin           ###   ########.fr       */
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
	double		tmp_wall_x;
	double		tmp_step;
	int			tmp_tex_x;
	int			tmp_tex_y;
	char		*pixel_tmp;
	unsigned int	color;

	if (glb->door_params.tmp_ray.side == 0)
		tmp_wall_x = glb->player.y + glb->door_params.tmp_dist
			* glb->door_params.tmp_ray.ray_dir_y;
	else
		tmp_wall_x = glb->player.x + glb->door_params.tmp_dist
			* glb->door_params.tmp_ray.ray_dir_x;
	tmp_wall_x -= floor(tmp_wall_x);
	tmp_tex_x = get_tex_x(glb, tmp_wall_x);
	tmp_step = (double)glb->door_params.tmp_tex->height
		/ glb->door_params.tmp_line_height;
	tmp_tex_y = get_tex_y(glb, y, tmp_step);
	pixel_tmp = glb->door_params.tmp_tex->addr
		+ tmp_tex_y * glb->door_params.tmp_tex->line_length
		+ tmp_tex_x * (glb->door_params.tmp_tex->bpp / 8);
	color = *(unsigned int *)pixel_tmp;
	return (apply_distance_effect(color, glb->door_params.tmp_dist,
			glb->light_pwr));
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
	double			dist;
	double			floor_x;
	double			floor_y;
	char			*pixel_floor;
	unsigned int	color;

	dist = glb->h / (2.0 * y - glb->h);
	if (glb->texture.sol.is_rgb == false)
	{
		floor_x = glb->player.x + dist * glb->ray.ray_dir_x;
		floor_y = glb->player.y + dist * glb->ray.ray_dir_y;
		int (tex_x_floor) = (int)(floor_x * glb->texture.sol.width)
			% glb->texture.sol.width;
		int (tex_y_floor) = (int)(floor_y * glb->texture.sol.height)
			% glb->texture.sol.height;
		pixel_floor = glb->texture.sol.addr + tex_y_floor
			* glb->texture.sol.line_length + tex_x_floor * (glb->texture.sol.bpp
			/ 8);
		color = *(unsigned int *)pixel_floor;
	}
	else
		color = ft_uni(glb->texture.sol.rgb);
	return (apply_distance_effect(color, dist, glb->light_pwr));
}

void	draw_wall_texture(t_global *glb, int x, t_img *tex)
{
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	unsigned int	color;

	calculate_texture_params(glb, tex, &tex_x, &step);
	tex_pos = (glb->ray.draw_start - glb->h / 2 + glb->ray.line_height / 2)
		* step;
	bool (door_anim) = (glb->map_clone[glb->ray.map_y][glb->ray.map_x] == '3');
	int (clip_height) = glb->anim_door;
	if (clip_height > glb->door_height)
		clip_height = glb->door_height;
	int (white_start) = glb->door_start_y;
	int (white_end) = white_start + clip_height;
	glb->door_params.ray_calculated = false;
	int (y) = glb->ray.draw_start - 1;
	while (++y < glb->ray.draw_end)
	{
		tex_y = (int)tex_pos % tex->height;
		if (tex_y < 0)
			tex_y += tex->height;
		tex_pos += step;
		if (door_anim && y >= white_start && y < white_end)
			color = handle_door_opening(glb, x, y);
		else
		{
			glb->el_muros_invisible = 1;
			color = get_normal_wall_color(glb, tex, tex_x, tex_y);
		}
		put_pixel(&glb->img, x, y, color);
	}
}
