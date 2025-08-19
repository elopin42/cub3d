/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:57:49 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/19 01:17:25 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**load_file(int fd, char *filename)
{
	ssize_t	total_size;
	char	*content;
	char	**ret;

	total_size = get_file_size(fd);
	content = malloc(sizeof(char) * (total_size + 1));
	fd = open(filename, O_RDONLY);
	if (fd == -1 || content == NULL)
		load_file_error(fd, content);
	if (read(fd, content, total_size) == -1)
		read_error(fd);
	close(fd);
	content[total_size] = '\0';
	ret = ft_matrix(content);
	free(content);
	if (ret == NULL)
	{
		perror("Error: ft_matrix()");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

ssize_t	get_file_size(int fd)
{
	ssize_t	read_ret;
	ssize_t	total_size;
	char	buf[1000];

	read_ret = read(fd, buf, 1000);
	if (read_ret == -1)
		read_error(fd);
	total_size = read_ret;
	while (read_ret == 1000)
	{
		read_ret = read(fd, buf, 1000);
		if (read_ret == -1)
			read_error(fd);
		total_size += read_ret;
	}
	close(fd);
	return (total_size);
}
