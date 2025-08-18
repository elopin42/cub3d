/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:57:43 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/18 18:04:53 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**get_config(char **file_content)
{
	char	**config;
	size_t	i;

	i = 0;
	while (file_content[i] && is_map_line(file_content[i]) == false)
		i++;
	if (i == ft_arraylen((void **)file_content))
	{
		ft_free_array(file_content);
		ft_printf(STDERR_FILENO, "Error: No map in config file.\n");
		exit(EXIT_FAILURE);
	}
	config = dup_trim_config(file_content, i);
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
		perror("Error: malloc()");
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
