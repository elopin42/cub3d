/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:24:52 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/27 00:58:41 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_mlx_error(t_global *glb, t_parsing *parser, char *error)
{
	ft_printf(STDERR_FILENO, ERR);
	ft_printf(STDERR_FILENO, error);
	destroy_all_textures(glb->smlx.mlx, &glb->texture);
	if (glb->smlx.mlx_win != NULL)
		mlx_destroy_window(glb->smlx.mlx, glb->smlx.mlx);
	if (glb->img.img != NULL)
		mlx_destroy_image(glb->smlx.mlx, glb->img.img);
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

void	destroy_all_textures(void *mlx, t_texture *text)
{
	destroy_texture(mlx, &text->sud);
	destroy_texture(mlx, &text->exit);
	destroy_texture(mlx, &text->nord);
	destroy_texture(mlx, &text->est);
	destroy_texture(mlx, &text->ouest);
	destroy_texture(mlx, &text->sol);
	destroy_texture(mlx, &text->sky);
	destroy_texture(mlx, &text->torche);
	destroy_texture(mlx, &text->door);
}

void	destroy_texture(void *mlx, t_img *img)
{
	if (img->img != NULL)
		mlx_destroy_image(mlx, img->img);
}
