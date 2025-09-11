/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_for_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:52:07 by elopin            #+#    #+#             */
/*   Updated: 2025/09/11 16:48:55 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_ray(t_global *glb, int x)
{
	glb->ray.camera_x = 2 * x / (double)glb->w - 1;
	glb->ray.ray_dir_x = glb->player.dir_x + glb->player.plane_x
		* glb->ray.camera_x;
	glb->ray.ray_dir_y = glb->player.dir_y + glb->player.plane_y
		* glb->ray.camera_x;
	glb->ray.map_x = (int)glb->player.x;
	glb->ray.map_y = (int)glb->player.y;
	glb->ray.delta_dist_x = fabs(1 / glb->ray.ray_dir_x);
	glb->ray.delta_dist_y = fabs(1 / glb->ray.ray_dir_y);
}

void	calculate_step_and_side_dist(t_global *glb)
{
	if (glb->ray.ray_dir_x < 0)
	{
		glb->ray.step_x = -1;
		glb->ray.side_dist_x = (glb->player.x - glb->ray.map_x)
			* glb->ray.delta_dist_x;
	}
	else
	{
		glb->ray.step_x = 1;
		glb->ray.side_dist_x = (glb->ray.map_x + 1.0 - glb->player.x)
			* glb->ray.delta_dist_x;
	}
	if (glb->ray.ray_dir_y < 0)
	{
		glb->ray.step_y = -1;
		glb->ray.side_dist_y = (glb->player.y - glb->ray.map_y)
			* glb->ray.delta_dist_y;
	}
	else
	{
		glb->ray.step_y = 1;
		glb->ray.side_dist_y = (glb->ray.map_y + 1.0 - glb->player.y)
			* glb->ray.delta_dist_y;
	}
}

static int	is_dda_hit(t_global *glb)
{
	int		x;
	int		y;
	char	tile;

	x = glb->ray.map_x;
	y = glb->ray.map_y;
	if (!is_valid_map_position(glb, x, y))
		return (1);
	tile = glb->map[y][x];
	if (tile == '1')
		return (1);
	if (tile == 'D' || tile == '3')
		return (1);
	if (glb->el_muros_invisible && tile == 'Q')
		return (1);
	return (0);
}

void	perform_dda(t_global *glb)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (glb->ray.side_dist_x < glb->ray.side_dist_y)
		{
			glb->ray.side_dist_x += glb->ray.delta_dist_x;
			glb->ray.map_x += glb->ray.step_x;
			glb->ray.side = 0;
		}
		else
		{
			glb->ray.side_dist_y += glb->ray.delta_dist_y;
			glb->ray.map_y += glb->ray.step_y;
			glb->ray.side = 1;
		}
		hit = is_dda_hit(glb);
	}
}

void	calculate_wall_distance(t_global *glb)
{
	if (glb->ray.side == 0)
		glb->ray.perp_wall_dist = (glb->ray.map_x - glb->player.x + (1
					- glb->ray.step_x) / 2) / glb->ray.ray_dir_x;
	else
		glb->ray.perp_wall_dist = (glb->ray.map_y - glb->player.y + (1
					- glb->ray.step_y) / 2) / glb->ray.ray_dir_y;
	glb->ray.line_height = (int)(glb->h / glb->ray.perp_wall_dist);
	glb->ray.draw_start = -glb->ray.line_height / 2 + glb->h / 2;
	glb->ray.draw_end = glb->ray.line_height / 2 + glb->h / 2;
	if (glb->ray.draw_start < 0)
		glb->ray.draw_start = 0;
	if (glb->ray.draw_end >= glb->h)
		glb->ray.draw_end = glb->h - 1;
}
