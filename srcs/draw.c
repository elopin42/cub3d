/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 02:12:56 by elopin            #+#    #+#             */
/*   Updated: 2025/06/25 16:21:09 by elopin           ###   ########.fr       */
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
	int w = 2560;
	int h = 1440;

	for (int x = 0; x < w; x++)
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

		int step_x;
		int step_y;

		int hit = 0;
		int side;

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
			if (glb->map[map_y][map_x] == '1') hit = 1;
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

    for (int y = 0; y < draw_start; y++)
	    put_pixel(&glb->img, x, y, 0x444444);

    for (int y = draw_end; y < h; y++)
	    put_pixel(&glb->img, x, y, 0x880000);

    for (int y = draw_start; y < draw_end; y++)
	    put_pixel(&glb->img, x, y, 0xAAAAAA);
	}
	mlx_put_image_to_window(glb->smlx.mlx, glb->smlx.mlx_win, glb->img.img, 0, 0);
}

