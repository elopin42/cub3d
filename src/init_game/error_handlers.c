/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:24:52 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/26 23:25:44 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_mlx_error(t_mlx *smlx, t_parsing *parser, char *error)
{
	ft_printf(STDERR_FILENO, ERR);
	ft_printf(STDERR_FILENO, error);
	parser->config = ft_free_array(parser->config);
	parser->map = ft_free_array(parser->map);
	parser->map_copy = ft_free_array(parser->map_copy);
	exit(EXIT_FAILURE);
}
