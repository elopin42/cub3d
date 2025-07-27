/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_tex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:57:45 by elopin            #+#    #+#             */
/*   Updated: 2025/07/27 17:13:45 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calculate_texture_params(t_global *glb, t_img *tex, int *tex_x,
		double *step, double *tex_pos)
{
	double	wall_x;

	wall_x = (glb->ray.side == 0) ? glb->player.y + glb->ray.perp_wall_dist
		* glb->ray.ray_dir_y : glb->player.x + glb->ray.perp_wall_dist
		* glb->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * tex->width);
	if ((glb->ray.side == 0 && glb->ray.ray_dir_x > 0) || (glb->ray.side == 1
			&& glb->ray.ray_dir_y < 0))
		*tex_x = tex->width - *tex_x - 1;
	*step = (double)tex->height / glb->ray.line_height;
	*tex_pos = (glb->ray.draw_start - glb->h / 2 + glb->ray.line_height / 2)
		* *step;
}

void	calculate_secondary_ray(t_global *glb)
{
	if (glb->door_params->ray_calculated)
		return ;
	glb->door_params->tmp_ray = glb->ray;
	perform_dda_ignoring_doors(glb, &glb->door_params->tmp_ray);
	glb->door_params->tmp_dist = (glb->door_params->tmp_ray.side == 0) ? (glb->door_params->tmp_ray.map_x
			- glb->player.x + (1 - glb->door_params->tmp_ray.step_x) / 2)
		/ glb->door_params->tmp_ray.ray_dir_x : (glb->door_params->tmp_ray.map_y
			- glb->player.y + (1 - glb->door_params->tmp_ray.step_y) / 2)
		/ glb->door_params->tmp_ray.ray_dir_y;
	glb->door_params->tmp_line_height = (int)(glb->h
			/ glb->door_params->tmp_dist);
	glb->door_params->tmp_draw_start = -glb->door_params->tmp_line_height / 2
		+ glb->h / 2;
	glb->door_params->tmp_draw_end = glb->door_params->tmp_line_height / 2
		+ glb->h / 2;
	if (glb->door_params->tmp_draw_start < 0)
		glb->door_params->tmp_draw_start = 0;
	if (glb->door_params->tmp_draw_end >= glb->h)
		glb->door_params->tmp_draw_end = glb->h - 1;
	glb->door_params->tmp_tex = select_wall_texture_from_ray(glb,
			&glb->door_params->tmp_ray);
	glb->door_params->ray_calculated = true;
}

unsigned int	draw_wall_behind_door(t_global *glb, int y)
{
	double			tmp_wall_x;
	char			*pixel_tmp;
	unsigned int	color;
	double			d;
	double			factor;

	int tmp_tex_x, tmp_tex_y;
	double tmp_step, tmp_tex_pos;
	tmp_wall_x = (glb->door_params->tmp_ray.side == 0) ? glb->player.y
		+ glb->door_params->tmp_dist
		* glb->door_params->tmp_ray.ray_dir_y : glb->player.x
		+ glb->door_params->tmp_dist * glb->door_params->tmp_ray.ray_dir_x;
	tmp_wall_x -= floor(tmp_wall_x);
	tmp_tex_x = (int)(tmp_wall_x * glb->door_params->tmp_tex->width);
	if ((glb->door_params->tmp_ray.side == 0
			&& glb->door_params->tmp_ray.ray_dir_x > 0)
		|| (glb->door_params->tmp_ray.side == 1
			&& glb->door_params->tmp_ray.ray_dir_y < 0))
		tmp_tex_x = glb->door_params->tmp_tex->width - tmp_tex_x - 1;
	tmp_step = (double)glb->door_params->tmp_tex->height
		/ glb->door_params->tmp_line_height;
	tmp_tex_pos = (glb->door_params->tmp_draw_start - glb->h / 2
			+ glb->door_params->tmp_line_height / 2) * tmp_step;
	tmp_tex_pos += (y - glb->door_params->tmp_draw_start) * tmp_step;
	tmp_tex_y = ((int)tmp_tex_pos) & (glb->door_params->tmp_tex->height - 1);
	pixel_tmp = glb->door_params->tmp_tex->addr + tmp_tex_y
		* glb->door_params->tmp_tex->line_length + tmp_tex_x
		* (glb->door_params->tmp_tex->bpp / 8);
	color = *(unsigned int *)pixel_tmp;
	if (glb->door_params->tmp_dist > 1.0)
	{
		d = glb->door_params->tmp_dist - 1.0;
		factor = 1.0 / (d * d * d + 1.0);
		if (factor < 0.02)
			factor = 0.02;
		color = effet_noir(color, factor);
	}
	return (color);
}

unsigned int	handle_door_opening(t_global *glb, int x, int y)
{
	unsigned int	color;

	int tex_x_sky, tex_y_sky, tex_x_floor, tex_y_floor;
	double dist, floor_x, floor_y, d, factor;
	char *pixel_sky, *pixel_floor;
	glb->el_muros_invisible = 0;
	calculate_secondary_ray(glb);
	if (y >= glb->door_params->tmp_draw_start
		&& y <= glb->door_params->tmp_draw_end)
		return (draw_wall_behind_door(glb, y));
	else if (y < glb->door_params->tmp_draw_start)
	{
		tex_x_sky = (x * glb->texture.sky.width) / glb->w;
		tex_y_sky = (y * glb->texture.sky.height) / (glb->h / 2);
		pixel_sky = glb->texture.sky.addr + (tex_y_sky
				* glb->texture.sky.line_length + tex_x_sky
				* (glb->texture.sky.bpp / 8));
		return (*(unsigned int *)pixel_sky);
	}
	else
	{
		dist = glb->h / (2.0 * y - glb->h);
		floor_x = glb->player.x + dist * glb->ray.ray_dir_x;
		floor_y = glb->player.y + dist * glb->ray.ray_dir_y;
		tex_x_floor = (int)(floor_x * glb->texture.sol.width)
			% glb->texture.sol.width;
		tex_y_floor = (int)(floor_y * glb->texture.sol.height)
			% glb->texture.sol.height;
		pixel_floor = glb->texture.sol.addr + tex_y_floor
			* glb->texture.sol.line_length + tex_x_floor * (glb->texture.sol.bpp
				/ 8);
		color = *(unsigned int *)pixel_floor;
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
}

void	draw_wall_texture(t_global *glb, int x, t_img *tex)
{
	unsigned int	color;
	bool			door_anim;
	char			*pixel;
	double			d;
	double			factor;

	int tex_x, tex_y, y, clip_height, white_start, white_end;
	double step, tex_pos;
	calculate_texture_params(glb, tex, &tex_x, &step, &tex_pos);
	door_anim = (glb->map_clone[glb->ray.map_y][glb->ray.map_x] == '3');
	clip_height = glb->anim_door;
	if (clip_height > glb->door_height)
		clip_height = glb->door_height;
	white_start = glb->door_start_y;
	white_end = white_start + clip_height;
	glb->door_params->ray_calculated = false;
	y = glb->ray.draw_start - 1;
	while (++y < glb->ray.draw_end)
	{
		tex_y = ((int)tex_pos) & (tex->height - 1);
		tex_pos += step;
		if (door_anim && y >= white_start && y < white_end)
			color = handle_door_opening(glb, x, y);
		else
		{
			glb->el_muros_invisible = 1;
			pixel = tex->addr + tex_y * tex->line_length + tex_x * (tex->bpp
					/ 8);
			color = *(unsigned int *)pixel;
			if (glb->ray.perp_wall_dist > 1.0)
			{
				d = glb->ray.perp_wall_dist - 1.0;
				factor = 1.0 / (d * d * d + 1.0);
				if (factor < 0.02)
					factor = 0.02;
				color = effet_noir(color, factor);
			}
		}
		put_pixel(&glb->img, x, y, color);
	}
}

/*void draw_wall_texture(t_global *glb, int x, t_img *tex)
{
	unsigned int color;
	// 1) Calcul de wall_x et tex_x
	double wall_x = (glb->ray.side == 0)
		? glb->player.y + glb->ray.perp_wall_dist * glb->ray.ray_dir_y
		: glb->player.x + glb->ray.perp_wall_dist * glb->ray.ray_dir_x;
	wall_x -= floor(wall_x);

	int tex_x = (int)(wall_x * tex->width);
	if ((glb->ray.side == 0 && glb->ray.ray_dir_x > 0) ||
		(glb->ray.side == 1 && glb->ray.ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;

	// 2) Préparation du pas vertical dans la texture
	double step    = (double)tex->height / glb->ray.line_height;
	double tex_pos = (glb->ray.draw_start - glb->h / 2
					+ glb->ray.line_height / 2) * step;

	// 3) Paramètres de l'animation de porte
	bool  door_anim      = (glb->map_clone[glb->ray.map_y][glb->ray.map_x] == '3');
	int   clip_height    = glb->anim_door;
	if (clip_height > glb->door_height)
		clip_height = glb->door_height;
	int   white_start    = glb->door_start_y;
	int   white_end      = white_start + clip_height;

	// Variables pour le rayon secondaire
	t_ray tmp_ray;
	double tmp_dist;
	t_img *tmp_tex;
	int tmp_line_height, tmp_draw_start, tmp_draw_end;
	bool ray_calculated = false;

	// 4) Boucle de dessin de la ligne verticale
	for (int y = glb->ray.draw_start; y < glb->ray.draw_end; y++)
	{
		int tex_y = ((int)tex_pos) & (tex->height - 1);
		tex_pos += step;

		char *pixel;
		if (door_anim && y >= white_start && y < white_end)
		{
			glb->el_muros_invisible = 0;

			// Calculer le rayon secondaire une seule fois
			if (!ray_calculated)
			{
				tmp_ray = glb->ray;
				perform_dda_ignoring_doors(glb, &tmp_ray);

				// Recalcule de la distance
				tmp_dist = (tmp_ray.side == 0)
					? (tmp_ray.map_x - glb->player.x + (1 - tmp_ray.step_x) / 2)
						/ tmp_ray.ray_dir_x
					: (tmp_ray.map_y - glb->player.y + (1 - tmp_ray.step_y) / 2)
						/ tmp_ray.ray_dir_y;

				// Calculer les paramètres de rendu pour le mur derrière
				tmp_line_height = (int)(glb->h / tmp_dist);
				tmp_draw_start = -tmp_line_height / 2 + glb->h / 2;
				tmp_draw_end = tmp_line_height / 2 + glb->h / 2;
				if (tmp_draw_start < 0)
					tmp_draw_start = 0;
				if (tmp_draw_end >= glb->h)
					tmp_draw_end = glb->h - 1;

				tmp_tex = select_wall_texture_from_ray(glb, &tmp_ray);
				ray_calculated = true;
			}

			// Vérifier si on est dans la zone du mur derrière
			if (y >= tmp_draw_start && y <= tmp_draw_end)
			{
				// Dessiner le mur derrière
				double tmp_wall_x = (tmp_ray.side == 0)
					? glb->player.y + tmp_dist * tmp_ray.ray_dir_y
					: glb->player.x + tmp_dist * tmp_ray.ray_dir_x;
				tmp_wall_x -= floor(tmp_wall_x);

				int tmp_tex_x = (int)(tmp_wall_x * tmp_tex->width);
				if ((tmp_ray.side == 0 && tmp_ray.ray_dir_x > 0) ||
					(tmp_ray.side == 1 && tmp_ray.ray_dir_y < 0))
					tmp_tex_x = tmp_tex->width - tmp_tex_x - 1;

				double tmp_step = (double)tmp_tex->height / tmp_line_height;
				double tmp_tex_pos = (tmp_draw_start - glb->h / 2
						+ tmp_line_height / 2) * tmp_step;
				tmp_tex_pos += (y - tmp_draw_start) * tmp_step;
				int tmp_tex_y = ((int)tmp_tex_pos) & (tmp_tex->height - 1);

				char *pixel_tmp = tmp_tex->addr
					+ tmp_tex_y * tmp_tex->line_length
					+ tmp_tex_x * (tmp_tex->bpp / 8);

				color = *(unsigned int *)pixel_tmp;

				// Appliquer l'effet de distance
				if (tmp_dist > 1.0)
				{
					double d = tmp_dist - 1.0;
					double factor = 1.0 / (d * d * d + 1.0);
					if (factor < 0.02) factor = 0.02;
					color = effet_noir(color, factor);
				}
			}
			else if (y < tmp_draw_start)
			{
				// Zone de plafond/ciel
					- utiliser la même logique que draw_ceiling_and_sky
				int tex_x_sky = (x * glb->texture.sky.width) / glb->w;
				int tex_y_sky = (y * glb->texture.sky.height) / (glb->h / 2);

				char *pixel_sky = glb->texture.sky.addr +
					(tex_y_sky * glb->texture.sky.line_length + tex_x_sky
						* (glb->texture.sky.bpp / 8));
				color = *(unsigned int *)pixel_sky;
			}
			else
			{
				// Zone de sol - utiliser la même logique que draw_floor
				double dist = glb->h / (2.0 * y - glb->h);
				double floor_x = glb->player.x + dist * glb->ray.ray_dir_x;
				double floor_y = glb->player.y + dist * glb->ray.ray_dir_y;

				int tex_x_floor = (int)(floor_x * glb->texture.sol.width)
					% glb->texture.sol.width;
				int tex_y_floor = (int)(floor_y * glb->texture.sol.height)
					% glb->texture.sol.height;

				char *pixel_floor = glb->texture.sol.addr
					+ tex_y_floor * glb->texture.sol.line_length
					+ tex_x_floor * (glb->texture.sol.bpp / 8);

				color = *(unsigned int *)pixel_floor;

				// Appliquer l'effet de distance pour le sol
				if (dist > 1.0)
				{
					double d = dist - 1.0;
					double factor = 1.0 / (d * d * d + 1.0);
					if (factor < 0.02)
						factor = 0.02;
					color = effet_noir(color, factor);
				}
			}

			put_pixel(&glb->img, x, y, color);
			continue ;
		}
		else
		{
			glb->el_muros_invisible = 1;
			pixel = tex->addr
					+ tex_y * tex->line_length
					+ tex_x * (tex->bpp / 8);
			color = *(unsigned int *)pixel;
		}

		if (glb->ray.perp_wall_dist > 1.0)
		{
			double d      = glb->ray.perp_wall_dist - 1.0;
			double factor = 1.0 / (d * d * d + 1.0);
			if (factor < 0.02) factor = 0.02;
			color = effet_noir(color, factor);
		}

		put_pixel(&glb->img, x, y, color);
	}
}*/
