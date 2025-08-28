/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:12:40 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/20 18:07:13 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**create_formatted_map(t_parsing *parsing, char **map_file)
{
	t_map_info	info;
	char		**map;

	map = init_map_info(&info, parsing, map_file);
	while (info.i < info.height)
	{
		map[info.i] = ft_calloc(sizeof(char), info.width + 1);
		if (map[info.i] == NULL)
		{
			while (info.i > 0)
			{
				info.i--;
				free(map[info.i]);
			}
			free(map);
			map_error(parsing, CALLOCERR, -1);
		}
		fill_line(map[info.i], map_file[info.i], info.width);
		info.i++;
	}
	parsing->map_copy = ft_dup_char_array(map);
	if (parsing->map_copy == NULL)
		map_error(parsing, CALLOCERR, -1);
	return (map);
}

void	fill_line(char *line, char *ref, size_t len)
{
	size_t	i;
	size_t	ref_len;

	i = 0;
	ref_len = ft_strlen(ref);
	while (i < ref_len)
	{
		if (ft_isspace(ref[i]) == true)
			line[i] = '1';
		else
			line[i] = ref[i];
		i++;
	}
	while (i < len)
	{
		line[i] = '1';
		i++;
	}
}

char	**init_map_info(t_map_info *info, t_parsing *parsing, char **map_file)
{
	char	**map;

	info->i = 0;
	info->width = get_map_width(map_file);
	info->height = get_map_height(map_file);
	map = ft_calloc(sizeof(char *), info->height + 1);
	if (!map)
	{
		perror(CALLOCERR);
		ft_free_array(parsing->file_content);
		ft_free_array(parsing->config);
		exit(EXIT_FAILURE);
	}
	return (map);
}

size_t	get_map_height(char **map)
{
	size_t	i;

	i = 0;
	while (map[i] && is_map_line(map[i]) == true)
		i++;
	return (i);
}

size_t	get_map_width(char **map)
{
	size_t	width;
	size_t	len;
	size_t	i;

	width = 0;
	i = 0;
	while (map[i] && is_map_line(map[i]) == true)
	{
		len = ft_strlen(map[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}
