/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:24:04 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/26 23:23:35 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
1/ mlx ptr
2/ mlx img (main frame)
3/ textures
4/ window
5/ hooks
6/ start game!
*/
void	init_mlx(t_mlx *smlx, t_parsing *parser)
{
	smlx->mlx = mlx_init();
	if (smlx->mlx == NULL)
		init_mlx_error(smlx, parser, MLXINIT);

}

void	init_glb_values(t_global *glb, t_parsing *parser)
{
	glb->w = WIN_WIDTH;
	glb->h = WIN_HEIGHT;
	glb->map = parser->map;
	glb->map = parser->map_copy;
	if (parser->ceiling_set == true)
	{
		glb->texture.sky.is_rgb = true;
		glb->texture.sky.rgb->r = parser->ceiling.r;
		glb->texture.sky.rgb->g = parser->ceiling.g;
		glb->texture.sky.rgb->b = parser->ceiling.b;
	}
	if (parser->floor_set == true)
	{
		glb->texture.sol.is_rgb = true;
		glb->texture.sol.rgb->r = parser->floor.r;
		glb->texture.sol.rgb->g = parser->floor.g;
		glb->texture.sol.rgb->b = parser->floor.b;
	}
	set_map_dimensions(glb);
}

void	init_mlx_error(t_mlx *smlx, t_parsing *parser, char *error)
{
	ft_printf(STDERR_FILENO, ERR);
	ft_printf(STDERR_FILENO, error);
	parser->config = ft_free_array(parser->config);
	parser->map = ft_free_array(parser->map);
	parser->map_copy = ft_free_array(parser->map_copy);
	return ;
}
