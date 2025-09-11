/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 02:12:56 by elopin            #+#    #+#             */
/*   Updated: 2025/09/11 11:44:45 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_ceiling_and_sky(t_global *glb, int x)
{
	int				tex_x;
	int				tex_y;
	unsigned int	color;
	int				y;

	y = -1;
	while (++y < glb->h / 2)
	{
		if (glb->texture.sky.is_rgb == false)
		{
			tex_x = (x * glb->texture.sky.width) / glb->w;
			tex_y = (y * glb->texture.sky.height) / (glb->h / 2);
			color = get_pixel_color(&glb->texture.sky, tex_y, tex_x);
		}
		else
			color = ft_uni(glb->texture.sky.rgb);
		put_pixel(&glb->img, x, y, color);
	}
}

void	draw_floor(t_global *glb, int x)
{
	double			dist;
	int				tex_x;
	int				tex_y;
	unsigned int	color;
	int				y;

	y = glb->ray.draw_end;
	while (++y < glb->h)
	{
		dist = glb->h / (2.0 * y - glb->h);
		if (glb->texture.sol.is_rgb == false)
		{
			glb->dec.floor_x = glb->player.x + dist * glb->ray.ray_dir_x;
			glb->dec.floor_y = glb->player.y + dist * glb->ray.ray_dir_y;
			tex_x = (int)(glb->dec.floor_x * glb->texture.sol.width)
				% glb->texture.sol.width;
			tex_y = (int)(glb->dec.floor_y * glb->texture.sol.height)
				% glb->texture.sol.height;
			color = get_pixel_color(&glb->texture.sol, tex_y, tex_x);
		}
		else
			color = ft_uni(glb->texture.sol.rgb);
		color = apply_distance_effect(color, dist, glb->light_pwr);
		put_pixel(&glb->img, x, y, color);
	}
}

/* Fait l'image entière, call par draw_scene */
void	draw_vertical_line(t_global *glb, int x)
{
	t_img	*tex;

	init_ray(glb, x);
	calculate_step_and_side_dist(glb);
	perform_dda(glb);
	calculate_wall_distance(glb);
	draw_ceiling_and_sky(glb, x);
	tex = select_wall_texture(glb);
	draw_wall_texture(glb, x, tex);
	draw_floor(glb, x);
}

void	put_timer(t_global *glb)
{
	const long total = 120000;
	long elapsed = glb->now - glb->start;
	long remaining = total - elapsed;
	long minutes = (remaining / 1000) / 60;
	long sec = (remaining / 1000) % 60;
	mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win, 400, 400, 0x11111111, ft_itoa(minutes));
	mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win, 450, 400, 0x11111111, ft_itoa(sec));
}

void	draw_scene(t_global *glb)
{
	int				x;
	int				width;
	static double	offset_x = 0;
	static double	offset_y = 0;

	update_light_state(glb);
	update_offset(glb, &offset_x, &offset_y);
	x = 350 + offset_x;
	width = 930 + offset_x;
	while (++x < width)
		draw_vertical_line(glb, x);
	draw_overlay(glb, offset_y, offset_x);
	draw_flashlight(glb, offset_y, offset_x);
	if (glb->key_q)
		draw_minimap(glb);
	mlx_put_image_to_window(glb->smlx.mlx, glb->smlx.mlx_win, glb->img.img, 0,
		0);
	put_fps_counter(glb);
	put_timer(glb);
}
