/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:43:39 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/23 14:40:15 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_config_errors(t_parsing *parsing, char **config)
{
	if (config == NULL)
		return ;
	if (validate_config_identifier(config) == false)
	{
		ft_free_array(parsing->file_content);
		ft_free_array(config);
		exit(EXIT_FAILURE);
	}
	check_duplicate(parsing, config, "NO", 2);
	check_duplicate(parsing, config, "SO", 2);
	check_duplicate(parsing, config, "WE", 2);
	check_duplicate(parsing, config, "EA", 2);
	check_duplicate(parsing, config, "F", 1);
	check_duplicate(parsing, config, "C", 1);
}

void	check_duplicate(t_parsing *parsing, char **config, char *key, size_t len)
{
	size_t	i;
	bool	key_found;

	i = 0;
	key_found = false;
	while (config[i])
	{
		if (ft_strncmp(config[i], key, len) == 0)
		{
			if (key_found == true)
				duplicate_found(parsing, key);
			key_found = true;
		}
		i++;
	}
}
