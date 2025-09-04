/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:44:41 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/04 18:23:43 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	update_line_info(t_circle *circle, int radius);

void	make_overlay(t_img *img, t_img *overlay)
{
	int			radius;
	t_circle	circle;

	radius = 250;
	circle.cy = overlay->height / 2;
	circle.cx = overlay->width / 2;
	circle.top = ceil(circle.cy - radius);
	circle.bottom = floor(circle.cy + radius);
	circle.y = circle.top;
	circle.dy = circle.y - circle.cy;
	circle.dx = sqrt(radius * radius - circle.dy * circle.dy);
	circle.left = ceil(circle.cx - circle.dx);
	circle.x = circle.left;
	circle.right = floor(circle.cx + circle.dx);
	ft_bzero(overlay->addr, overlay->line_length * overlay->height);
	draw_transparent_zone(&circle, overlay, img, radius);
}

void	draw_transparent_zone(t_circle *circle, t_img *overlay, t_img *img, int radius)
{
	while (circle->y <= circle->bottom)
	{
		update_line_info(circle, radius);
		while (circle->x <= circle->right)
		{
			if (circle->y >= 0 && circle->x >= 0
				&& circle->y <= overlay->height
				&& circle->x <= overlay->width)
				put_transparency(overlay, circle->y, circle->x);
			circle->x++;
		}
		circle->y++;
	}
}

static inline void	update_line_info(t_circle *circle, int radius)
{
	circle->dy = circle->y - circle->cy;
	circle->dx = sqrt(radius * radius - circle->dy * circle->dy);
	circle->left = ceil(circle->cx - circle->dx);
	circle->right = floor(circle->cx + circle->dx);
	circle->x = circle->left;
}
