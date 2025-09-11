/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flashlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:25:22 by elopin            #+#    #+#             */
/*   Updated: 2025/09/11 16:17:18 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	switch_bool(bool *state)
{
	if (*state == true)
		*state = false;
	else
		*state = true;
}

void	update_light_state(t_global *glb)
{
	if (glb->lightoff == true)
	{
		glb->texture.cur_hand = &glb->texture.hand[0];
		glb->light_pwr = glb->texture.hand[0].light_pwr;
	}
	else
		handle_torch_on(glb);
}

void	handle_torch_on(t_global *glb)
{
	static long	last_glitch = 0;
	static bool	in_glitch = false;
	static long	glitch_end = 0;
	long		now;

	now = glb->now;
	if (in_glitch == true)
	{
		if (now >= glitch_end)
			in_glitch = false;
		else
		{
			handle_glitch_effect(glb, now);
			return ;
		}
	}
	if (now - last_glitch >= 8000)
	{
		in_glitch = true;
		glitch_end = now + 1000 + (rand() % 2000);
		last_glitch = now;
	}
	glb->texture.cur_hand = &glb->texture.hand[9];
	glb->light_pwr = glb->texture.hand[9].light_pwr;
}

void	handle_glitch_effect(t_global *glb, long now)
{
	int			i;
	static long	last_change = 0;

	if (now - last_change > (100 + rand() % 1000))
	{
		i = 1 + rand() % 9;
		glb->texture.cur_hand = &glb->texture.hand[i];
		glb->light_pwr = glb->texture.hand[i].light_pwr;
		last_change = now;
	}
}
