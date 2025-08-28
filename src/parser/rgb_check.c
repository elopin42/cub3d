/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:44:25 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/25 23:48:00 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	handle_rgb_values(char **config, t_parsing *parsing)
{
	size_t	i;

	i = 0;
	if (config == NULL)
		return ;
	while (config[i])
	{
		if (!ft_strncmp(config[i], "F ", 2))
		{
			check_rgb_format(&config[i][1], parsing);
			set_rgb_values(&config[i][1], parsing, &parsing->floor);
			parsing->floor_set = true;
		}
		else if (!ft_strncmp(config[i], "C ", 2))
		{
			check_rgb_format(&config[i][1], parsing);
			set_rgb_values(&config[i][1], parsing, &parsing->ceiling);
			parsing->ceiling_set = true;
		}
		i++;
	}
}

void	check_rgb_format(char *entry, t_parsing *parsing)
{
	size_t	i;
	size_t	commas_count;

	i = 0;
	commas_count = 0;
	while (ft_isspace(entry[i]) == true)
		i++;
	while (entry[i])
	{
		if (ft_isdigit(entry[i]) == false)
			rgb_error(parsing, entry, RGBFMT);
		while (ft_isdigit(entry[i]) == true)
			i++;
		if (entry[i] == ',')
		{
			i++;
			commas_count++;
			if (ft_isdigit(entry[i]) == false)
				rgb_error(parsing, entry, RGBFMT);
		}
	}
	if (commas_count != 2)
		rgb_error(parsing, entry, RGBFMT);
}

void	set_rgb_values(char *values, t_parsing *parsing, t_rgb *rgb)
{
	long long	nbr;
	char		**split;

	while (ft_isspace(*values))
		values++;
	split = ft_split(values, ',');
	if (split == NULL)
	{
		ft_free_array(parsing->file_content);
		ft_free_array(parsing->config);
		exit(EXIT_FAILURE);
	}
	nbr = ft_atoll(split[0]);
	if (nbr > 255)
		rgb_too_big(parsing, split);
	rgb->r = (unsigned char)nbr;
	nbr = ft_atoll(split[1]);
	if (nbr > 255)
		rgb_too_big(parsing, split);
	rgb->g = (unsigned char)nbr;
	nbr = ft_atoll(split[2]);
	if (nbr > 255)
		rgb_too_big(parsing, split);
	rgb->b = (unsigned char)nbr;
	ft_free_array(split);
}

void	rgb_error(t_parsing *parsing, char *entry, char *err)
{
	size_t	i;

	i = 0;
	while (ft_isspace(entry[i]) == true)
		i++;
	ft_printf(STDERR_FILENO, err, entry + i);
	ft_free_array(parsing->file_content);
	ft_free_array(parsing->config);
	exit(EXIT_FAILURE);
}

void	rgb_too_big(t_parsing *parsing, char **array)
{
	ft_printf(STDERR_FILENO, RGBTOOBIG);
	ft_free_array(array);
	ft_free_array(parsing->file_content);
	ft_free_array(parsing->config);
	exit(EXIT_FAILURE);
}
