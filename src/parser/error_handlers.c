/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:57:25 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/19 00:08:20 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	read_error(int fd)
{
	perror("Error: read()");
	close(fd);
	exit(EXIT_FAILURE);
}

void	load_file_error(int fd, void *ptr)
{
	if (fd == -1 || ptr == NULL)
	{
		if (fd == -1)
			perror("Error: open()");
		else
		{
			perror("Error: malloc()");
			close(fd);
		}
		exit(EXIT_FAILURE);
	}
}

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
