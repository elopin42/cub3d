/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:41:37 by elopin            #+#    #+#             */
/*   Updated: 2025/08/26 15:19:23 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_img	*select_wall_texture(t_global *glb)
{
	if (glb->map[glb->ray.map_y][glb->ray.map_x] == 'D')
		return (&glb->texture.door);
	if (glb->ray.side == 0 && glb->ray.ray_dir_x > 0)
		return (&glb->texture.ouest);
	if (glb->ray.side == 0 && glb->ray.ray_dir_x < 0)
		return (&glb->texture.est);
	if (glb->ray.side == 1 && glb->ray.ray_dir_y > 0)
		return (&glb->texture.nord);
	return (&glb->texture.sud);
}

t_img	*select_wall_texture_from_ray(t_global *glb, t_ray *ray)
{
	if (glb->map[ray->map_y][ray->map_x] == 'D')
		return (&glb->texture.door);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (&glb->texture.ouest);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		return (&glb->texture.est);
	if (ray->side == 1 && ray->ray_dir_y > 0)
		return (&glb->texture.nord);
	return (&glb->texture.sud);
}
