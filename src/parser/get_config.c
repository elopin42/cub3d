/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:57:43 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/23 14:40:14 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**get_config(char **file_content)
{
	char	**config;
	size_t	delim;

	delim = 0;
	while (file_content[delim] && is_map_line(file_content[delim]) == false)
		delim++;
	if (delim == ft_arraylen((void **)file_content))
	{
		ft_free_array(file_content);
		ft_printf(STDERR_FILENO, NOMAPERR);
		exit(EXIT_FAILURE);
	}
	config = dup_trim_config(file_content, delim);
	return (config);
}

char	**dup_trim_config(char **array, size_t delim)
{
	size_t	array_size;
	char	**config;

	array_size = delim - count_skips(array, delim);
	if (array_size == 0)
		return (NULL);
	config = ft_calloc(sizeof (char *), array_size + 1);
	if (config == NULL)
	{
		ft_free_array(array);
		perror("Error: ft_calloc()");
		exit(EXIT_FAILURE);
	}
	config = fill_config_array(array, config, delim);
	return (config);
}

char	**fill_config_array(char **array, char **config, size_t delim)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < delim)
	{
		if (ft_is_only_space(array[i]) == false)
		{
			config[j] = ft_strtrim(array[i], SPACES);
			if (config[j] == NULL)
				handle_trim_fail(array, config, i);
			j++;
		}
		i++;
	}
	return (config);
}

bool	validate_config_identifier(char **config)
{
	size_t	i;

	i = 0;
	while (config[i])
	{
		if (!ft_strncmp("NO", config[i], 2) && ft_isspace(config[i][2]))
			;
		else if (!ft_strncmp("SO", config[i], 2) && ft_isspace(config[i][2]))
			;
		else if (!ft_strncmp("WE", config[i], 2) && ft_isspace(config[i][2]))
			;
		else if (!ft_strncmp("EA", config[i], 2) && ft_isspace(config[i][2]))
			;
		else if (config[i][0] == 'F' && ft_isspace(config[i][1]))
			;
		else if (config[i][0] == 'C' && ft_isspace(config[i][1]))
			;
		else
		{
			ft_printf(STDERR_FILENO, CONFIGFMTERR, config[i]);
			return (false);
		}
		i++;
	}
	return (true);
}
