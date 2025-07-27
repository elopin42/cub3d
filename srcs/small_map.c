/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:57:48 by elopin            #+#    #+#             */
/*   Updated: 2025/07/27 20:53:50 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// le d c'est pour la norme en gros je pouvais pas mettre 5 argument donc j'ai inproviser

void	draw_square(t_global *glb, int x, int y, int d)
{
	int	color;
	int	size;

	if (d == 1 || d == 2 || d == 4)
	{
		size = SQUARE_SIZE;
		if (d == 2)
			color = 0x222222;
		else if (d == 4)
			color = 0x800080;
		else
			color = 0x888888;
	}
	else if (d == 3)
	{
		size = SQUARE_SIZE / 2;
		color = 0xFF0000;
	}
	else
		return ;
	int (dy) = -1;
	while (++dy < size)
	{
		int (dx) = -1;
		while (++dx < size)
			put_pixel(&glb->img, x + dx, y + dy, color);
	}
}

void	draw_minimap(t_global *glb)
{
	int	screen_x;
	int	screen_y;
	int x;

	int (y) = -1;
	while (++y < glb->m_h)
	{
		x = -1;
		while (++x < glb->m_w)
		{
			screen_x = MINIMAP_START_X + x * SQUARE_SIZE;
			screen_y = MINIMAP_START_Y + y * SQUARE_SIZE;
			if (glb->map_clone[y][x] == '1')
				draw_square(glb, screen_x, screen_y, 1);
			else if (glb->map_clone[y][x] == 'D' || glb->map_clone[y][x] == '3')
				draw_square(glb, screen_x, screen_y, 4);
			else
				draw_square(glb, screen_x, screen_y, 2);
		}
	}
	int (px) = MINIMAP_START_X + glb->player.x * SQUARE_SIZE;
	int (py) = MINIMAP_START_Y + glb->player.y * SQUARE_SIZE;
	draw_square(glb, px, py, 3);
}

void	set_map_dimensions(t_global *glb)
{
	int	i;
	int	max_width;
	int	len;

	i = -1;
	max_width = 0;
	while (glb->map[++i])
	{
		len = ft_strlen(glb->map[i]);
		if (len > max_width)
			max_width = len;
	}
	glb->m_h = i;
	glb->m_w = max_width;
}
