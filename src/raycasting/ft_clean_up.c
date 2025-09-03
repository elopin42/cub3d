/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 00:34:36 by elopin            #+#    #+#             */
/*   Updated: 2025/09/03 16:05:32 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_free_map(char **map)
{
	int	i;

	i = -1;
	if (!map)
		return ;
	while (map[++i])
		free(map[i]);
	free(map);
}

void	ft_clean_imagouille(void *mlx, t_img *tex)
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
		destroy_all_textures_imgs(glb->smlx.mlx, glb);
		mlx_destroy_display(glb->smlx.mlx);
		free(glb->smlx.mlx);
	}
	ft_free_map(glb->map);
	ft_free_map(glb->map_clone);
	exit(exit_code);
}
