/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:03:41 by elopin            #+#    #+#             */
/*   Updated: 2025/07/09 00:29:29 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_press(int keycode, t_global *glb)
{
	if (keycode == 65307)
		return (printf("echape!\n"), ft_clean_all(glb), 0);
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
	return (0);
}

int	key_release(int keycode, t_global *glb)
{
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
	return (0);
}

int	update(t_global *glb)
{
	lunch_frame(glb);
	if (glb->key_w)
		move_player(glb, 1);
	if (glb->key_s)
		move_player(glb, 2);
	if (glb->key_a)
		move_player(glb, 3);
	if (glb->key_d)
		move_player(glb, 4);
	if (glb->key_left)
		rotate_camera(glb, -0.08);
	if (glb->key_right)
		rotate_camera(glb, 0.08);
	draw_scene(glb);
	if (glb->anim_door > 0)
	{
		glb->anim_door += 10;
		if (glb->anim_door >= glb->ray.line_height)
		{
			glb->anim_door = 0;
			glb->map[glb->d_y][glb->d_x] = '0'; 
		}
	}

	return (0);
}

int	main(int ac, char **av)
{
	t_global	glb = {0};

	if (ac != 2)
		return (printf("argument\nerror\n"), 0);
	if (!ft_init(&glb, av) || !ft_parsing(&glb))
		return (printf("error\n"), ft_clean_all(&glb), 0);
	mlx_hook(glb.smlx.mlx_win, 2, 1L << 0, key_press, &glb);
	mlx_hook(glb.smlx.mlx_win, 3, 1L << 1, key_release, &glb);
	mlx_loop_hook(glb.smlx.mlx, update, &glb);
	mlx_hook(glb.smlx.mlx_win, 17, 0, (void *)ft_clean_all, &glb);
	return (mlx_loop(glb.smlx.mlx));
}
