/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:03:41 by elopin            #+#    #+#             */
/*   Updated: 2025/07/27 21:06:53 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	mouse_moved_advanced(int x, int y, void *param)
{
	t_global	*glb;
	double		sensitivity;
	int			center_x;
	int			center_y;
	static int	mouse_locked = 1;

	(void)y;
	glb = (t_global *)param;
	sensitivity = 0.003;
	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	if (glb->key_tab)
	{
		mouse_locked = 0;
		glb->key_tab = false;
	}
	if (!mouse_locked)
		return (0);
	int (delta_x) = x - center_x;
	if (abs(delta_x) < 3)
		return (0);
	rotate_camera(glb, -delta_x * sensitivity);
	mlx_mouse_move(glb->smlx.mlx, glb->smlx.mlx_win, center_x, center_y);
	return (0);
}

int	key_press(int keycode, t_global *glb)
{
	if (keycode == 65307)
		return (printf("echape!\n"), ft_clean_all(glb, 0), 0);
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
		if (get_current_time_ms() - glb->door_timing >= 1500)
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
		return (printf("error\n"), ft_clean_all(&glb, 1), 0);
	mlx_hook(glb.smlx.mlx_win, 2, 1L << 0, key_press, &glb);
	mlx_hook(glb.smlx.mlx_win, 3, 1L << 1, key_release, &glb);
	mlx_hook(glb.smlx.mlx_win, 6, 1L << 6, mouse_moved_advanced, &glb);
	mlx_loop_hook(glb.smlx.mlx, update, &glb);
	mlx_hook(glb.smlx.mlx_win, 17, 0, (void *)ft_clean_all, &glb);
	mlx_mouse_move(glb.smlx.mlx, glb.smlx.mlx_win, WIN_WIDTH / 2, WIN_HEIGHT
		/ 2);
	return (mlx_loop(glb.smlx.mlx));
}
