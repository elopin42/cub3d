/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_draw_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:03:08 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/04 15:09:59 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_transparency(t_img *img, int y, int x)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = (int)0xFF000000;
}

void	draw_xpm_to_img(t_img *dst, t_img *img, int y, int x)
{
	int				i;
	int				j;
	unsigned int	current_color;
	// printf("height: %d\nwidth: %d\n", img->height, img->width);

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			current_color = get_pixel_color(img, i, j);
			put_pixel_to_img(dst, current_color, y + i, x + j);
			j++;
		}
		i++;
	}
	// printf("i: %d\nj: %d\n", i, j)
}

void	put_pixel_to_img(t_img *img, int color, int y, int x)
{
	char	*dst;

	if ((int)color == (int)0xFF000000)
		return ;
	else
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

unsigned int	get_pixel_color(t_img *img, int y, int x)
{
	return (*(unsigned int *)(img->addr + (y * img->line_length) + (x * img->bpp / 8)));
}
