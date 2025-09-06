/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:25:47 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/06 14:56:03 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	destroy_texture(void *mlx, t_img *img);

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
	ft_free_array(glb->map);
	ft_free_array(glb->map_clone);
	exit(exit_code);
}

void	destroy_all_textures_imgs(void *mlx, t_global *glb)
{
	int	i;

	i = 0;
	destroy_texture(mlx, &glb->texture.sud);
	destroy_texture(mlx, &glb->texture.nord);
	destroy_texture(mlx, &glb->texture.est);
	destroy_texture(mlx, &glb->texture.ouest);
	destroy_texture(mlx, &glb->texture.sol);
	destroy_texture(mlx, &glb->texture.sky);
	destroy_texture(mlx, &glb->texture.overlay);
	destroy_texture(mlx, &glb->texture.door);
	destroy_texture(mlx, &glb->texture.exit);
	destroy_texture(mlx, &glb->overlay);
	destroy_texture(mlx, &glb->img);
	while (i < 10)
	{
		destroy_texture(mlx, &glb->texture.hand[i]);
		i++;
	}
}

static void	destroy_texture(void *mlx, t_img *img)
{
	if (img->img != NULL)
		mlx_destroy_image(mlx, img->img);
}
