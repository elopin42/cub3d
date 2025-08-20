/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:57:25 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/20 11:54:14 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	handle_trim_fail(char **array, char **config, size_t fail_idx)
{
	size_t	i;

	i = 0;
	perror("Error: ft_strtrim()");
	ft_free_array(array);
	while (i < fail_idx)
	{
		free(config[i]);
		i++;
	}
	free(config);
	exit(EXIT_FAILURE);
}

void	map_error(t_parsing *parsing, char *err_msg, int c)
{
	if (c == -1)
		ft_printf(STDERR_FILENO, err_msg);
	else
		ft_printf(STDERR_FILENO, err_msg, c);
	ft_free_array(parsing->file_content);
	ft_free_array(parsing->config);
	exit(EXIT_FAILURE);
}
