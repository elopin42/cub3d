/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:58:04 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/25 12:42:20 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

size_t	count_skips(char **array, size_t delim)
{
	size_t	i;
	size_t	skip;

	i = 0;
	skip = 0;
	while (i < delim && array[i])
	{
		if (ft_is_only_space(array[i]) == true)
			skip++;
		i++;
	}
	return (skip);
}

bool	is_map_line(char *line)
{
	size_t	i;

	i = 0;
	if (line[i] == '\0')
		return (false);
	while (line[i])
	{
		if (ft_isspace(line[i]) == true
			|| line[i] == '0'
			|| line[i] == '1'
			|| line[i] == 'D'
			|| line[i] == 'N'
			|| line[i] == 'S'
			|| line[i] == 'E'
			|| line[i] == 'W')
			i++;
		else
			return (false);
	}
	return (true);
}

bool	is_valid_map_char(char c)
{
	return (ft_isspace(c) == true
		|| c == '0'
		|| c == '1'
		|| c == 'D'
		|| c == 'N'
		|| c == 'S'
		|| c == 'W'
		|| c == 'E');
}

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

bool	is_invalid_identifier(char *key)
{
	if (!ft_strncmp("NO", key, 2))
		return (false);
	if (!ft_strncmp("SO", key, 2))
		return (false);
	if (!ft_strncmp("WE", key, 2))
		return (false);
	if (!ft_strncmp("EA", key, 2))
		return (false);
	if (key[0] == 'F')
		return (false);
	if (key[0] == 'C')
		return (false);
	return (true);
}
