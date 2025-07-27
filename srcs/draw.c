/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 02:12:56 by elopin            #+#    #+#             */
/*   Updated: 2025/07/27 17:08:42 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_ceiling_and_sky(t_global *glb, int x)
{
	int (y) = -1;
	
	while (++y < glb->h / 2)
	{
		int tex_x = (x * glb->texture.sky.width) / glb->w;
		int tex_y = (y * glb->texture.sky.height) / (glb->h / 2);
		
		char *pixel = glb->texture.sky.addr + (tex_y * glb->texture.sky.line_length + tex_x * (glb->texture.sky.bpp / 8));
		unsigned int color = *(unsigned int *)pixel;
		put_pixel(&glb->img, x, y, color);
	}
}
// donc c'est la que je dois faire une boucle while pour le mur;

void draw_floor(t_global *glb, int x)
{
	int y = glb->ray.draw_end + 1;
	double dist;
	double floor_x, floor_y;
	char *pix;

	while (y < glb->h)
	{
		dist = glb->h / (2.0 * y - glb->h);

		floor_x = glb->player.x + dist * glb->ray.ray_dir_x;
		floor_y = glb->player.y + dist * glb->ray.ray_dir_y;

		int tex_x = (int)(floor_x * glb->texture.sol.width) % glb->texture.sol.width;
		int tex_y = (int)(floor_y * glb->texture.sol.height) % glb->texture.sol.height;

		pix = glb->texture.sol.addr
			+ tex_y * glb->texture.sol.line_length
			+ tex_x * (glb->texture.sol.bpp / 8);

		unsigned int color = *(unsigned int *)pix;

    	if (dist > 1.0)
    	{
	    	double d = dist - 1.0;
	    	double factor = 1.0 / (d * d * d + 1.0);
	    	if (factor < 0.02)
		    	factor = 0.02;
	    	color = effet_noir(color, factor);
    	}

		put_pixel(&glb->img, x, y, color);
		y++;
	}
}

void	draw_vertical_line(t_global *glb, int x)
{
	t_img *tex;
	
	init_ray(glb, x);
	calculate_step_and_side_dist(glb);
	perform_dda(glb);
	calculate_wall_distance(glb);
	draw_ceiling_and_sky(glb, x);
	tex = select_wall_texture(glb);
	draw_wall_texture(glb, x, tex);
	draw_floor(glb, x);
}


void	draw_scene(t_global *glb)
{
	int (x) = -1;
	while (++x < glb->w)
		draw_vertical_line(glb, x);
	draw_torch(glb);
  	draw_minimap(glb);
	mlx_put_image_to_window(glb->smlx.mlx, glb->smlx.mlx_win, glb->img.img, 0, 0);
}


