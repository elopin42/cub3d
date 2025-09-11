/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:20:43 by elopin            #+#    #+#             */
/*   Updated: 2025/09/11 16:20:48 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	game_over(t_global *glb)
{
    int x;
    int y;
    int step_x;
    int step_y;

    step_x = 200;
    step_y = 50;
    y = 0;
    ft_bzero(glb->img.addr, glb->img.line_length * glb->img.height);
    mlx_put_image_to_window(glb->smlx.mlx, glb->smlx.mlx_win, glb->img.img, 0, 0);
    while(y < WIN_HEIGHT)
    {
        while(x < WIN_WIDTH)
        {
            mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win, x, y, 0xFF0000, "GAME OVER");
            x += step_x;
        }
        mlx_do_sync(glb->smlx.mlx);
        usleep(300000);
        y += step_y;
        x = 0;
    }
    sleep(5);
    ft_clean_all(glb, 0);
}
