/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:24:52 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/04 22:37:50 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
