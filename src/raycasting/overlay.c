/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:44:41 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/12 14:43:58 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	update_line_info(t_circle *circle, int radius);
static inline void	put_circle_pixel(t_circle *circle, t_img *overlay,
						t_img *img);

void	make_overlay(t_global *glb, double offset_y, double offset_x,
		double pwr)
{
	t_circle	circle;
	t_img		*overlay;
	t_img		*img;

	overlay = &glb->overlay;
	img = &glb->img;
	if (pwr == 255.0)
		pwr = 1.0;
	if (pwr == 0)
		circle.radius = 0;
	else
		circle.radius = 300;
	circle.inner_radius = circle.radius * 0.8 * pwr;
	circle.cy = overlay->height / 2 + offset_y;
	circle.cx = overlay->width / 2 + offset_x;
	circle.top = ceil(circle.cy - circle.radius);
	circle.bottom = floor(circle.cy + circle.radius);
	circle.y = circle.top;
	circle.dy = circle.y - circle.cy;
	circle.dx = sqrt(circle.radius * circle.radius - circle.dy * circle.dy);
	circle.left = ceil(circle.cx - circle.dx);
	circle.x = circle.left;
	circle.right = floor(circle.cx + circle.dx);
	ft_bzero(overlay->addr, overlay->line_length * overlay->height);
	draw_faded_circle(&circle, overlay, img);
}

void	draw_faded_circle(t_circle *circle, t_img *overlay, t_img *img)
{
	while (circle->y <= circle->bottom)
	{
		update_line_info(circle, circle->radius);
		while (circle->x <= circle->right)
		{
			if (circle->y >= 0 && circle->x >= 0 && circle->y < overlay->height
				&& circle->x < overlay->width)
				put_circle_pixel(circle, overlay, img);
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

static inline void	put_circle_pixel(t_circle *circle, t_img *overlay,
		t_img *img)
{
	circle->color = get_pixel_color(img, circle->y, circle->x);
	circle->distance = sqrt((circle->x - circle->cx) * (circle->x - circle->cx)
			+ (circle->y - circle->cy) * (circle->y - circle->cy));
	if (circle->distance < circle->inner_radius)
		circle->factor = 1.0;
	else if (circle->distance < circle->radius)
		circle->factor = 1.0 - ((circle->distance - circle->inner_radius)
				/ (circle->radius - circle->inner_radius));
	else
		circle->factor = 0.0;
	circle->color = darken_pxl(circle->color, circle->factor);
	put_pixel_to_img(overlay, circle->color, circle->y, circle->x);
}
