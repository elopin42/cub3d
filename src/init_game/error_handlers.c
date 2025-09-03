/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:24:52 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/03 15:58:36 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Tej le param de destroy_all_textures_imgs ()
void	init_mlx_error(t_global *glb, t_parsing *parser, char *error)
{
	ft_printf(STDERR_FILENO, ERR);
	ft_printf(STDERR_FILENO, error);
	destroy_all_textures_imgs(glb->smlx.mlx, glb);
	if (glb->smlx.mlx_win != NULL)
		mlx_destroy_window(glb->smlx.mlx, glb->smlx.mlx);
	if (glb->smlx.mlx != NULL)
	{
		mlx_destroy_display(glb->smlx.mlx);
		free(glb->smlx.mlx);
	}
	ft_free_array(parser->config);
	ft_free_array(parser->map);
	ft_free_array(parser->map_copy);
	exit(EXIT_FAILURE);
}

void	destroy_all_textures_imgs(void *mlx, t_global *glb)
{
	destroy_texture(mlx, &glb->texture.sud);
	destroy_texture(mlx, &glb->texture.nord);
	destroy_texture(mlx, &glb->texture.est);
	destroy_texture(mlx, &glb->texture.ouest);
	destroy_texture(mlx, &glb->texture.sol);
	destroy_texture(mlx, &glb->texture.sky);
	destroy_texture(mlx, &glb->texture.overlay);
	destroy_texture(mlx, &glb->texture.door);
	destroy_texture(mlx, &glb->texture.torche);
	destroy_texture(mlx, &glb->overlay);
	destroy_texture(mlx, &glb->img);
}

void	destroy_texture(void *mlx, t_img *img)
{
	if (img->img != NULL)
		mlx_destroy_image(mlx, img->img);
}
