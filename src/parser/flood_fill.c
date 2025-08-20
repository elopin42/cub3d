/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:55:35 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/20 18:01:14 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	is_map_closed(t_parsing *parsing, char **map, char **map_copy)
{
	t_ff		ff;
	size_t		x;
	size_t		y;

	ft_bzero(&ff, sizeof (t_ff));
	ff.width = ft_strlen(map[0]) - 1;
	ff.height = ft_arraylen((void **)map) - 1;
	x = (int)parsing->player->x;
	y = (int)parsing->player->y;
	flood_fill(&ff, map_copy, x, y);
	if (ff.map_is_open == true)
	{
		ft_printf(STDERR_FILENO, MAPOPENERR);
		ft_free_array(map);
		ft_free_array(map_copy);
		ft_free_array(parsing->config);
		exit(EXIT_FAILURE);
	}
	unfill_map(map, map_copy);
}

void	flood_fill(t_ff *ff, char **map, int x, int y)
{
	if (ff->map_is_open == true)
		return ;
	else if (x < 0 || y < 0 || x > ff->width || y > ff->height)
		return ;
	else if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	else if ((map[y][x] == '0' || map[y][x] == 'D') &&
			(y == 0 || x == 0 || y == ff->height || x == ff->width))
	{
		ff->map_is_open = true;
		return ;
	}
	map[y][x] = 'V';
	flood_fill(ff, map, x + 1, y);
	flood_fill(ff, map, x - 1, y);
	flood_fill(ff, map, x, y + 1);
	flood_fill(ff, map, x, y - 1);
}

void	unfill_map(char **map, char **copy)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (copy[i][j])
		{
			copy[i][j] = map[i][j];
			j++;
		}
		i++;
	}
}
