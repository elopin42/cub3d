/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:15:55 by elopin            #+#    #+#             */
/*   Updated: 2025/06/06 23:32:44 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	ft_init(t_global *glb)
{

	glb->smlx.mlx = mlx_init();
	glb->smlx.mlx_win = mlx_new_window(glb->smlx.mlx, 1920, 1080, "cub3d!");
	return (true);
}
