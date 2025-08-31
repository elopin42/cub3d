/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 01:42:24 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/31 21:40:38 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*get_path(char *line);

void	load_parsed_textures(t_global *glb, t_parsing *parser)
{
	set_parsed_path(parser, parser->config);
	if (parser->no_path == NULL)
		load_xpm(glb, parser, &glb->texture.nord, NORTH);
	else
		load_xpm(glb, parser, &glb->texture.nord, parser->no_path);
	if (parser->so_path == NULL)
		load_xpm(glb, parser, &glb->texture.sud, SOUTH);
	else
		load_xpm(glb, parser, &glb->texture.sud, parser->so_path);
	if (parser->ea_path == NULL)
		load_xpm(glb, parser, &glb->texture.est, EAST);
	else
		load_xpm(glb, parser, &glb->texture.est, parser->ea_path);
	if (parser->we_path == NULL)
		load_xpm(glb, parser, &glb->texture.ouest, WEST);
	else
		load_xpm(glb, parser, &glb->texture.ouest, parser->we_path);
}

void	set_parsed_path(t_parsing *parser, char **config)
{
	int	i;

	i = 0;
	if (config == NULL)
		return ;
	while (config[i])
	{
		if (!ft_strncmp(config[i], "NO", 2))
			parser->no_path = get_path(config[i] + 2);
		else if (!ft_strncmp(config[i], "SO", 2))
			parser->so_path = get_path(config[i] + 2);
		else if (!ft_strncmp(config[i], "WE", 2))
			parser->we_path = get_path(config[i] + 2);
		else if (!ft_strncmp(config[i], "EA", 2))
			parser->ea_path = get_path(config[i] + 2);
		i++;
	}
}

static char	*get_path(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (line);
}

void	load_xpm(t_global *glb, t_parsing *parser, t_img *img, char *xpm)
{
	if (img->img != NULL)
		mlx_destroy_image(glb->smlx.mlx, img->img);
	img->img = mlx_xpm_file_to_image(glb->smlx.mlx, xpm, &img->width,
			&img->height);
	if (img->img == NULL)
		init_mlx_error(glb, parser, MLXXPM);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length,
			&img->endian);
	if (img->addr == NULL)
		init_mlx_error(glb, parser, MLXXPM);
}
