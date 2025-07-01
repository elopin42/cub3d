/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:03:41 by elopin            #+#    #+#             */
/*   Updated: 2025/07/01 20:39:26 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_press(int keycode, t_global *glb)
{
  if (keycode == 65307)
	{
		ft_clean_all(glb);
		exit(0);
	}
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
	return (0);
}

int	handle_key(int keycode, void *param)
{
	t_global	*glb;

	glb = (t_global *)param;
	if (keycode == 65307)
		return (printf("echape!\n"), ft_clean_all(glb), 0);
	if (keycode == KEY_LEFT) // exemple : flèche gauche
		rotate_camera(glb, -0.05); // rotation à gauche
	if (keycode == KEY_RIGHT) // exemple : flèche droite
    rotate_camera(glb, 0.05); // rotation à droiteoid	rotate_camera(t_global *glb, double angle)
  if (keycode == KEY_W)
    move_player(glb, 1);
  if (keycode == KEY_S)
    move_player(glb, 2);
  if (keycode == KEY_A)
    move_player(glb, 3);
  if (keycode == KEY_D)
    move_player(glb, 4);

  draw_scene(glb);
	return (1);
}

int	main(int ac, char **av)
{
	t_global	glb = {0};

	if (ac != 2)
		return (printf("argument\nerror\n"), 0);
	if (!ft_init(&glb, av) || !ft_parsing(&glb))
		return (printf("error\n"), ft_clean_all(&glb), 0);
  	mlx_hook(glb.smlx.mlx_win, 2, 1L<<0, key_press, &glb);
	mlx_hook(glb.smlx.mlx_win, 3, 1L<<1, key_release, &glb);
	mlx_loop_hook(glb.smlx.mlx, update, &glb); 
	mlx_hook(glb.smlx.mlx_win, 17, 0, (void *)ft_clean_all, &glb);
	return (mlx_loop(glb.smlx.mlx));

}
