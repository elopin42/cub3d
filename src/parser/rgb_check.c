/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:44:25 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/23 14:40:18 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_rgb_values(char **config, t_parsing *parsing)
{
	return ;
	size_t	i;

	i = 0;
	if (config == NULL)
		return ;
	while (config[i])
	{
		if (!ft_strncmp(config[i], "F ", 2))
		{
			check_rgb_entry(&config[i][1], parsing->floor, parsing);
			parsing->floor_set = true;
		}
		else if (!ft_strncmp(config[i], "F ", 2))
		{
			check_rgb_entry(&config[i][1], parsing->ceiling, parsing);
			parsing->ceiling_set = true;
		}
		i++;
	}
}

void	check_rgb_entry(char *entry, t_rgb *rgb, t_parsing *parsing)
{
	size_t	i;

	i = 0;
	while (ft_isspace(entry[i]) == true)
		i++;

}
