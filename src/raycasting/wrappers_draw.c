/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:32:06 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/05 12:36:46 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_flashlight(t_global *glb)
{
	draw_xpm_to_img(&glb->img, &glb->texture.torche, 350, 720);
}

void	draw_overlay(t_global *glb)
{
	make_overlay(&glb->img, &glb->overlay);
	draw_xpm_to_img(&glb->img, &glb->overlay, 0, 0);
}
