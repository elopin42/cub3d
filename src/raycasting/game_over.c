/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:20:43 by elopin            #+#    #+#             */
/*   Updated: 2025/09/11 18:45:49 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	game_over(t_global *glb)
{
	int	x;
	int	y;
	int	step_x;

	step_x = 200;
	y = 0;
	ft_bzero(glb->img.addr, glb->img.line_length * glb->img.height);
	mlx_put_image_to_window(glb->smlx.mlx, glb->smlx.mlx_win, glb->img.img, 0,
		0);
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win, x, y, 0xFF0000,
				"GAME OVER");
			x += step_x;
		}
		mlx_do_sync(glb->smlx.mlx);
		usleep(300000);
		y += 50;
	}
	sleep(5);
	ft_clean_all(glb, 1);
}
