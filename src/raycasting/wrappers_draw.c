/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:32:06 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/09 23:41:16 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_player_moving(t_global *glb)
{
	return (glb->key_a == true || glb->key_d == true
		|| glb->key_s == true || glb->key_w == true);
}

void	update_offset(t_global *glb, double *offset_x, double *offset_y)
{
	static double	time = 0.0;
	double			freq;
	double			amp;

	if (is_player_moving(glb) == true)
	{
		freq = 5.0;
		amp = 10.0;
	}
	else
	{
		freq = 3.0;
		amp = 5.0;
	}
	time += 0.05;
	*offset_x = sin(time * freq) * amp;
	*offset_y = cos(time * freq * 0.5) * (amp / 2.0);
}

void	draw_flashlight(t_global *glb, double offset_y, double offset_x)
{
	static double	hand_x = 0;
	static double	hand_y = 0;
	double			k;

	k = 0.08;
	hand_x += (offset_x - hand_x) * k;
	hand_y += (offset_y - hand_y) * k;
	draw_xpm_to_img(&glb->img, glb->texture.cur_hand,
		350 + hand_y, 720 + hand_x);
}

void	draw_overlay(t_global *glb, double offset_y, double offset_x)
{
	make_overlay(glb, offset_y, offset_x, glb->light_pwr);
	draw_xpm_to_img(&glb->img, &glb->overlay, 0, 0);
}
