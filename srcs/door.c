/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:18:41 by elopin            #+#    #+#             */
/*   Updated: 2025/07/27 20:37:18 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <unistd.h>

bool	set_xy(t_global *glb, int y, int x)
{
	glb->d_y = y;
	glb->d_x = x;
	return (true);
}

bool	check_door_acces(t_global *glb, int y, int x, char c)
{
	if (glb->map_clone[y][x + 1] == c)
		return (set_xy(glb, y, x + 1));
	if (glb->map_clone[y][x - 1] == c)
		return (set_xy(glb, y, x - 1));
	if (glb->map_clone[y + 1][x] == c)
		return (set_xy(glb, y + 1, x));
	if (glb->map_clone[y - 1][x] == c)
		return (set_xy(glb, y - 1, x));
	return (false);
}

void	ft_door(t_global *glb)
{
	int	mid;

	mid = glb->w / 2;
	if (!glb->anim_door && check_door_acces(glb, glb->player.y, glb->player.x,
			'D'))
	{
		glb->door_timing = get_current_time_ms();
		init_ray(glb, mid);
		calculate_step_and_side_dist(glb);
		perform_dda(glb);
		calculate_wall_distance(glb);
		glb->door_start_y = glb->ray.draw_start;
		glb->door_height = glb->ray.line_height;
		glb->anim_door = 1;
		glb->map_clone[glb->d_y][glb->d_x] = '3';
		draw_scene(glb);
	}
	else if (!glb->anim_door && check_door_acces(glb, glb->player.y,
			glb->player.x, '3'))
	{
		glb->map[glb->d_y][glb->d_x] = 'D';
		glb->map_clone[glb->d_y][glb->d_x] = 'D';
	}
}
