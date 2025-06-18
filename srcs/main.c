/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:03:41 by elopin            #+#    #+#             */
/*   Updated: 2025/06/07 02:18:08 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	mlx_key_hook(glb.smlx.mlx_win, handle_key, &glb);
	return (draw_scene(&glb), mlx_loop(glb.smlx.mlx), 0);
}
