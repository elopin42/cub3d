/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 00:34:36 by elopin            #+#    #+#             */
/*   Updated: 2025/06/07 01:52:41 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_clean_all(t_global *glb)
{
	if (glb->smlx.mlx && glb->smlx.mlx_win)
		mlx_destroy_window(glb->smlx.mlx, glb->smlx.mlx_win);
	if (glb->smlx.mlx)
	{
		mlx_destroy_display(glb->smlx.mlx);
		free(glb->smlx.mlx);
	}
	exit(0);
}
