/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:43:39 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/25 12:55:21 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_config_errors(t_parsing *parsing, char **config)
{
	if (config == NULL)
		return ;
	validate_config_identifier(parsing, config);
	check_duplicate(parsing, config, "NO", 2);
	check_duplicate(parsing, config, "SO", 2);
	check_duplicate(parsing, config, "WE", 2);
	check_duplicate(parsing, config, "EA", 2);
	check_duplicate(parsing, config, "F", 1);
	check_duplicate(parsing, config, "C", 1);
}

void	validate_config_identifier(t_parsing *parsing, char **config)
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
			handle_misconfig(parsing, config, config[i]);
		i++;
	}
}

void	check_duplicate(t_parsing *p, char **config, char *key, size_t len)
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
				duplicate_found(p, key);
			key_found = true;
		}
		i++;
	}
}
