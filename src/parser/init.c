/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:24:04 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/23 12:41:15 by lle-cout         ###   ########.fr       */
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
		init_mlx_error(smlx, parser);

}

void	init_glb_values(t_global *glb, t_parsing *parser)
{
	glb->w = WIN_WIDTH;
	glb->h = WIN_HEIGHT;
	glb->map = parser->map;
	glb->map = parser->map_copy;
	set_map_dimensions(glb);
}

void	init_mlx_error(t_mlx *smlx, t_parsing *parser)
{
	return ;
}
