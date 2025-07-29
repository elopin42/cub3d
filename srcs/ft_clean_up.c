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

void ft_free_map(char **map)
{
  int i;

  i = -1;
  if (!map)
    return;
  while(map[++i])
    free(map[i]);
  free(map);
}

void ft_clean_imagouille(void *mlx, t_img *tex)
{
  if (tex->img)
    mlx_destroy_image(mlx, tex->img);
}

void	ft_clean_all(t_global *glb, int exit_code)
{
	if (!glb)
		exit(exit_code);
	if (glb->smlx.mlx)
	{
		if (glb->smlx.mlx_win)
			mlx_destroy_window(glb->smlx.mlx, glb->smlx.mlx_win);
    ft_clean_imagouille(glb->smlx.mlx, &glb->texture.sud);
    ft_clean_imagouille(glb->smlx.mlx, &glb->texture.nord);
    ft_clean_imagouille(glb->smlx.mlx, &glb->texture.est);
    ft_clean_imagouille(glb->smlx.mlx, &glb->texture.ouest);
    ft_clean_imagouille(glb->smlx.mlx, &glb->texture.sol);
    ft_clean_imagouille(glb->smlx.mlx, &glb->texture.sky);
    ft_clean_imagouille(glb->smlx.mlx, &glb->texture.torche);
    ft_clean_imagouille(glb->smlx.mlx, &glb->texture.door);
		if (glb->img.img)
			mlx_destroy_image(glb->smlx.mlx, glb->img.img);
		mlx_destroy_display(glb->smlx.mlx);
		free(glb->smlx.mlx);
	}
	ft_free_map(glb->map);
	ft_free_map(glb->map_clone);
	if (glb->door_params)
		free(glb->door_params);
	exit(exit_code);
}

