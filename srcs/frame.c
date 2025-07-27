/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:25:22 by elopin            #+#    #+#             */
/*   Updated: 2025/07/27 16:47:43 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*en gros stv rajouter des textures de flammes c'est dans frame_for_flame tu va comprendre et si tu veut rajouter de la rapiditer c'est dans lunch_frame tu modifie le 1 car la sa change toute les secondes*/

void	frame_for_flame(t_global *glb)
{
	static int	i = -1;

	i++;
	if (i == 0)
		load_texture(glb->smlx.mlx, &glb->texture.torche,
			"textures/torche.xpm");
	if (i == 1)
		load_texture(glb->smlx.mlx, &glb->texture.torche,
			"textures/torche1.xpm");
	if (i == 2)
		load_texture(glb->smlx.mlx, &glb->texture.torche,
			"textures/torche2.xpm");
	if (i == 3)
	{
		load_texture(glb->smlx.mlx, &glb->texture.torche,
			"textures/torche3.xpm");
		i = -1;
	}
}

void draw_torch(t_global *glb)
{
	if (!glb || !glb->texture.torche.img || !glb->texture.torche.addr)
		return;

	int screen_w = glb->w;
	int screen_h = glb->h;

	int target_height = (screen_h / 3) * 2;
	double scale = (double)target_height / glb->texture.torche.height;

	int scaled_width = glb->texture.torche.width * scale;
	int scaled_height = target_height;

	int x_offset = screen_w - screen_w / 2 + (screen_w / 2 - scaled_width) / 2;
	int y_offset = screen_h - scaled_height;

	for (int y = 0; y < glb->texture.torche.height; y++)
	{
		for (int x = 0; x < glb->texture.torche.width; x++)
		{
			char *pixel = glb->texture.torche.addr
				+ y * glb->texture.torche.line_length
				+ x * (glb->texture.torche.bpp / 8);
			unsigned int color = *(unsigned int *)pixel;

			if (color != 0xFF000000)
			{
				for (int dy = 0; dy < scale; dy++)
				{
					for (int dx = 0; dx < scale; dx++)
					{
						int screen_x = x_offset + x * scale + dx;
						int screen_y = y_offset + y * scale + dy;

						if (screen_x >= 0 && screen_x < screen_w && screen_y >= 0 && screen_y < screen_h)
							put_pixel(&glb->img, screen_x, screen_y, color);
					}
				}
			}
		}
	}
}

int	lunch_frame(t_global *glb)
{
	static time_t	last_time = 0;
	time_t			current_time;

	current_time = time(NULL);
	if (current_time - last_time >= 1)
	{
		frame_for_flame(glb);
		last_time = current_time;
	}
	return (0);
}
