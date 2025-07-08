/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:18:41 by elopin            #+#    #+#             */
/*   Updated: 2025/07/09 00:15:06 by elopin           ###   ########.fr       */
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

void ft_door(t_global *glb)
{
	if (!glb->anim_door && check_door_acces(glb, glb->player.y, glb->player.x, 'D'))
	{
		glb->anim_door = 1;
		glb->map_clone[glb->d_y][glb->d_x] = '3';
		printf("wsh\n");
		draw_scene(glb);
	}
	else if (!glb->anim_door && check_door_acces(glb, glb->player.y, glb->player.x, '3'))
	{
		glb->map[glb->d_y][glb->d_x] = 'D';
		glb->map_clone[glb->d_y][glb->d_x] = 'D';
		printf("waaa\n");
	}
}
