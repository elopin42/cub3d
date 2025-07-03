/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:18:41 by elopin            #+#    #+#             */
/*   Updated: 2025/07/03 20:27:05 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	acces_sorti(t_global *glb, char **map, int y, int x)
{
	if (map[y] == NULL || map[y][x] == '\0' || x < 0 || y < 0)
		return ;
	if (map[y][x] == '1' || map[y][x] == '2')
		return ;
	if (!glb->count_door && map[y][x] == 'D')
	{
		glb->d_x = x;
		glb->d_y = y;
		glb->count_door = 1;
		return ;
	}
	if (map[y][x] == '0')
		map[y][x] = '2';
	else
		map[y][x] += 32;
	acces_sorti(glb, map, y + 1, x);
	acces_sorti(glb, map, y - 1, x);
	acces_sorti(glb, map, y, x + 1);
	acces_sorti(glb, map, y, x - 1);
}

void ft_door(t_global *glb)
{
	
}
