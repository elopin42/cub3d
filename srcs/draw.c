/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 02:12:56 by elopin            #+#    #+#             */
/*   Updated: 2025/06/26 14:21:58 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void draw_scene(t_global *glb)
{
	int w = glb->w;
	int h = glb->h;
	int x = -1;

	while (++x < w)
	{
		double camera_x = 2 * x / (double)w - 1;
		double ray_dir_x = glb->player.dir_x + glb->player.plane_x * camera_x;
		double ray_dir_y = glb->player.dir_y + glb->player.plane_y * camera_x;

		int map_x = (int)glb->player.x;
		int map_y = (int)glb->player.y;

		double side_dist_x;
		double side_dist_y;
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
		double perp_wall_dist;

		int step_x, step_y, hit = 0, side;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (glb->player.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - glb->player.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (glb->player.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - glb->player.y) * delta_dist_y;
		}

		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (glb->map[map_y][map_x] == '1')
				hit = 1;
		}

		if (side == 0)
			perp_wall_dist = (map_x - glb->player.x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - glb->player.y + (1 - step_y) / 2) / ray_dir_y;

		int line_height = (int)(h / perp_wall_dist);
		int draw_start = -line_height / 2 + h / 2;
		int draw_end = line_height / 2 + h / 2;
		if (draw_start < 0) draw_start = 0;
		if (draw_end >= h) draw_end = h - 1;

		// -- PLAFOND
		for (int y = 0; y < draw_start; y++)
		{
			if (rand() % 100 < 2)
				put_pixel(&glb->img, x, y, 0xFFFF00);
			else
				put_pixel(&glb->img, x, y, 0x444444);
		}
		for (int y = 0; y < h / 2; y++) // afficher le haut de l’écran
		{
			int tex_x = (x * glb->texture.sky.width) / w;
			int tex_y = (y * glb->texture.sky.height) / (h / 2);
	
			char *pixel = glb->texture.sky.addr + (tex_y * glb->texture.sky.line_length + tex_x * (glb->texture.sky.bpp / 8));
			unsigned int color = *(unsigned int *)pixel;
			put_pixel(&glb->img, x, y, color);
		}


		// -- TEXTURE MURALE
		t_img *tex;
		if (side == 0 && ray_dir_x > 0)
			tex = &glb->texture.ouest;
		else if (side == 0 && ray_dir_x < 0)
			tex = &glb->texture.est;
		else if (side == 1 && ray_dir_y > 0)
			tex = &glb->texture.nord;
		else
			tex = &glb->texture.sud;

		double wall_x;
		if (side == 0)
			wall_x = glb->player.y + perp_wall_dist * ray_dir_y;
		else
			wall_x = glb->player.x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);

		int tex_x = (int)(wall_x * tex->width);
		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
			tex_x = tex->width - tex_x - 1;

		double step = 1.0 * tex->height / line_height;
		double tex_pos = (draw_start - h / 2 + line_height / 2) * step;

		for (int y = draw_start; y < draw_end; y++)
		{
			int tex_y = (int)tex_pos & (tex->height - 1);
			tex_pos += step;
			char *pixel = tex->addr + (tex_y * tex->line_length + tex_x * (tex->bpp / 8));
			unsigned int color = *(unsigned int *)pixel;
			put_pixel(&glb->img, x, y, color);
		}

		// -- SOL
		for (int y = draw_end; y < h; y++)
			put_pixel(&glb->img, x, y, 0x880000);
	}

	// Affichage de l'image finale
	mlx_put_image_to_window(glb->smlx.mlx, glb->smlx.mlx_win, glb->img.img, 0, 0);
}

