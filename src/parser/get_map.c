/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:12:13 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/20 13:20:05 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**get_map(t_parsing *parsing, char **file_content)
{
	char	**map;
	size_t	start;

	start = 0;
	while (file_content[start] && is_map_line(file_content[start]) == false)
		start++;
	map = file_content + start;
	check_invalid_chars(parsing, map);
	check_empty_lines(parsing, map);
	set_player_start(parsing, map, &parsing->glb->player);
	map = create_formatted_map(parsing, map);
	parsing->file_content = ft_free_array(parsing->file_content);
	is_map_closed(parsing, map, parsing->glb->map_clone);
	return (map);
}

void	check_invalid_chars(t_parsing *parsing, char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_valid_map_char(map[i][j]) == true)
				j++;
			else
				map_error(parsing, INVCHARMAP, map[i][j]);
		}
		i++;
	}
}

void	check_empty_lines(t_parsing *parsing, char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		if (ft_is_only_space(map[i]) == true)
		{
			i++;
			while (map[i])
			{
				if (ft_is_only_space(map[i]) == false)
					map_error(parsing, EMPTYLINEMAP, -1);
				i++;
			}
			return ;
		}
		i++;
	}
}

void	set_player_start(t_parsing *parsing, char **map, t_player *player)
{
	size_t	i;
	size_t	j;
	bool	player_found;

	i = 0;
	player_found = false;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]) == true && player_found == false)
			{
				set_player_info(player, map[i][j], i, j);
				map[i][j] = '0';
				player_found = true;
			}
			else if (is_player(map[i][j]) == true && player_found == true)
				map_error(parsing, STARTPOSERR, -1);
			j++;
		}
		i++;
	}
	if (player_found == false)
		map_error(parsing, NOPLAYER, -1);
}

void	set_player_info(t_player *player, char dir, size_t y, size_t x)
{
	player->x = (double)(x + 0.5);
	player->y = (double)(y + 0.5);
	if (dir == 'N')
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
}
