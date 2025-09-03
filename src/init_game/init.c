/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:24:04 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/03 15:51:51 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_game(t_global *glb, t_parsing *parser)
{
	init_glb_values(glb, parser);
	init_mlx(glb, parser);
	load_game_textures(glb, parser);
	load_parsed_textures(glb, parser);
	glb->smlx.mlx_win = mlx_new_window(glb->smlx.mlx, glb->w, glb->h, "cub3d");
	if (!glb->smlx.mlx_win)
		init_mlx_error(glb, parser, MLXIMGADDR);
	parser->config = ft_free_array(parser->config);
}

void	init_glb_values(t_global *glb, t_parsing *parser)
{
	glb->w = WIN_WIDTH;
	glb->h = WIN_HEIGHT;
	glb->map = parser->map;
	glb->map_clone = parser->map_copy;
	if (parser->ceiling_set == true)
	{
		glb->texture.sky.is_rgb = true;
		glb->texture.sky.rgb.r = parser->ceiling.r;
		glb->texture.sky.rgb.g = parser->ceiling.g;
		glb->texture.sky.rgb.b = parser->ceiling.b;
	}
	if (parser->floor_set == true)
	{
		glb->texture.sol.is_rgb = true;
		glb->texture.sol.rgb.r = parser->floor.r;
		glb->texture.sol.rgb.g = parser->floor.g;
		glb->texture.sol.rgb.b = parser->floor.b;
	}
	set_map_dimensions(glb);
}

void	init_mlx(t_global *glb, t_parsing *parsing)
{
	glb->smlx.mlx = mlx_init();
	if (glb->smlx.mlx == NULL)
		init_mlx_error(glb, parsing, MLXINIT);
	glb->img.img = mlx_new_image(glb->smlx.mlx, glb->w, glb->h);
	if (!glb->img.img)
		init_mlx_error(glb, parsing, MLXIMGERROR);
	glb->img.addr = mlx_get_data_addr(glb->img.img, &glb->img.bpp,
			&glb->img.line_length, &glb->img.endian);
	if (!glb->img.addr)
		init_mlx_error(glb, parsing, MLXIMGADDR);
}

void	init_hooks(t_global *glb, t_mlx *smlx)
{
	mlx_hook(smlx->mlx_win, 2, 1L << 0, key_press, glb);
	mlx_hook(smlx->mlx_win, 3, 1L << 1, key_release, glb);
	mlx_hook(smlx->mlx_win, 6, 1L << 6, mouse_moved_advanced, glb);
	mlx_loop_hook(smlx->mlx, update, glb);
	mlx_hook(smlx->mlx_win, 17, 0, (void *)ft_clean_all, glb);
	mlx_mouse_move(smlx->mlx, smlx->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}


// Créer load_image();
void	load_game_textures(t_global *glb, t_parsing *parser)
{
	load_xpm(glb, parser, &glb->texture.sol, "textures/sol.xpm");
	load_xpm(glb, parser, &glb->texture.sky, "textures/sky.xpm");
	load_xpm(glb, parser, &glb->texture.torche, "textures/light.xpm");
	load_xpm(glb, parser, &glb->texture.door, "textures/door.xpm");
	glb->overlay.img = mlx_new_image(glb->smlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (glb->overlay.img == NULL)
		init_mlx_error(glb, parser, MLXXPM);
	glb->overlay.addr = mlx_get_data_addr(glb->overlay.img,
			&glb->overlay.bpp, &glb->overlay.line_length,
			&glb->overlay.endian);
	if (glb->overlay.addr == NULL)
		init_mlx_error(glb, parser, MLXIMGADDR);
}
