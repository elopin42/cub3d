/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:25:22 by elopin            #+#    #+#             */
/*   Updated: 2025/08/26 15:19:23 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*en gros stv rajouter des textures de flammes c'est dans frame_for_flame tu va comprendre
et si tu veut rajouter de la rapiditer c'est dans lunch_frame
tu modifie le 1 car la sa change toute les secondes*/

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

static void	calculate_torch_dimensions(t_global *glb, t_torch_data *data)
{
	data->screen_w = glb->w;
	data->screen_h = glb->h;
	data->target_height = (data->screen_h / 3) * 2;
	data->scale = (double)data->target_height / glb->texture.torche.height;
	data->scaled_width = glb->texture.torche.width * data->scale;
	data->scaled_height = data->target_height;
	data->x_offset = data->screen_w - data->screen_w / 2 + (data->screen_w / 2
			- data->scaled_width) / 2;
	data->y_offset = data->screen_h - data->scaled_height;
}

static void	draw_scaled_pixel(t_global *glb, t_torch_data *data, int x, int y,
		unsigned int color)
{
	int	dx;
	int	dy;
	int	screen_x;
	int	screen_y;

	dy = 0;
	while (dy < data->scale)
	{
		dx = 0;
		while (dx < data->scale)
		{
			screen_x = data->x_offset + x * data->scale + dx;
			screen_y = data->y_offset + y * data->scale + dy;
			if (screen_x >= 0 && screen_x < data->screen_w && screen_y >= 0
				&& screen_y < data->screen_h)
				put_pixel(&glb->img, screen_x, screen_y, color);
			dx++;
		}
		dy++;
	}
}

static void	process_torch_pixel(t_global *glb, t_torch_data *data, int x, int y)
{
	char			*pixel;
	unsigned int	color;

	pixel = glb->texture.torche.addr + y * glb->texture.torche.line_length + x
		* (glb->texture.torche.bpp / 8);
	color = *(unsigned int *)pixel;
	if (color != 0xFF000000)
		draw_scaled_pixel(glb, data, x, y, color);
}

void	draw_torch(t_global *glb)
{
	t_torch_data	data;
	int				x;
	int				y;

	if (!glb || !glb->texture.torche.img || !glb->texture.torche.addr)
		return ;
	calculate_torch_dimensions(glb, &data);
	y = 0;
	while (y < glb->texture.torche.height)
	{
		x = 0;
		while (x < glb->texture.torche.width)
		{
			process_torch_pixel(glb, &data, x, y);
			x++;
		}
		y++;
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
