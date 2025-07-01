/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:25:22 by elopin            #+#    #+#             */
/*   Updated: 2025/07/01 20:44:22 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	frame_for_flame(t_global *glb)
{
	static int	i = -1;

	i++;
	if (i == 0)
		load_texture(glb->smlx.mlx, &glb->texture.torche, "textures/torche.xpm");
	if (i == 1)
		load_texture(glb->smlx.mlx, &glb->texture.torche, "textures/torche1.xpm");
	if (i == 2)
		load_texture(glb->smlx.mlx, &glb->texture.torche, "textures/torche2.xpm");
	if (i == 3)
	{
		load_texture(glb->smlx.mlx, &glb->texture.torche, "textures/torche3.xpm");
		i = -1;
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
