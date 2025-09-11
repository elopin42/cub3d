/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:09:25 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/11 17:09:39 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	key_press(int keycode, t_global *glb)
{
	if (keycode == 65307)
		return (ft_clean_all(glb, 0), 0);
	if (keycode == KEY_E)
		return (ft_door(glb), 0);
	if (keycode == KEY_LEFT)
		glb->key_left = true;
	if (keycode == KEY_RIGHT)
		glb->key_right = true;
	if (keycode == KEY_W)
		glb->key_w = true;
	if (keycode == KEY_S)
		glb->key_s = true;
	if (keycode == KEY_A)
		glb->key_a = true;
	if (keycode == KEY_D)
		glb->key_d = true;
	if (keycode == KEY_TABU)
		glb->key_tabu = true;
	return (0);
}
int	key_release(int keycode, t_global *glb)
{
	if (keycode == KEY_TABU)
		glb->key_tabu = false;
	if (keycode == KEY_LEFT)
		glb->key_left = false;
	if (keycode == KEY_RIGHT)
		glb->key_right = false;
	if (keycode == KEY_W)
		glb->key_w = false;
	if (keycode == KEY_S)
		glb->key_s = false;
	if (keycode == KEY_A)
		glb->key_a = false;
	if (keycode == KEY_D)
		glb->key_d = false;
	if (keycode == XK_f)
		switch_bool(&glb->lightoff);
	if (keycode == XK_q)
		switch_bool(&glb->showmap);
	if (keycode == XK_h)
		switch_bool(&glb->showhelp);
	return (0);
}
