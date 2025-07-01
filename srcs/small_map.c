/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:57:48 by elopin            #+#    #+#             */
/*   Updated: 2025/07/01 21:15:56 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_square(t_global *glb, int x, int y, int size, int color)
{
	for (int dy = 0; dy < size; dy++)
	{
		for (int dx = 0; dx < size; dx++)
			put_pixel(&glb->img, x + dx, y + dy, color);
	}
}


void draw_minimap(t_global *glb)
{
	for (int y = 0; y < glb->map.height; y++)
	{
		for (int x = 0; x < glb->map.width; x++)
		{
			int screen_x = MINIMAP_START_X + x * SQUARE_SIZE;
			int screen_y = MINIMAP_START_Y + y * SQUARE_SIZE;
			int color;

			if (glb->map.data[y][x] == '1')
				color = 0x888888; // mur gris
			else
				color = 0x222222; // sol sombre

			draw_square(glb, screen_x, screen_y, SQUARE_SIZE, color);
		}
	}

	// Dessine le joueur au centre de sa case
	int px = MINIMAP_START_X + glb->player.pos_x * SQUARE_SIZE;
	int py = MINIMAP_START_Y + glb->player.pos_y * SQUARE_SIZE;
	draw_square(glb, px, py, SQUARE_SIZE / 2, 0xFF0000); // joueur en rouge
}

