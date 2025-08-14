/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:23:57 by lle-cout          #+#    #+#             */
/*   Updated: 2025/04/19 18:29:44 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char		*loop(int fd, char *line, t_gnl *gnl, ssize_t newl_index);
static char		*update_line(char *line, size_t newl_index, t_gnl *gnl);
static ssize_t	get_new_index(t_gnl *gnl);
static char		*ft_strjoin_gnl(char *s1, char *s2, ssize_t len);

char	*get_next_line(int fd)
{
	static t_gnl	gnl;
	char			*line;
	ssize_t			newl_index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	newl_index = 0;
	line = loop(fd, line, &gnl, newl_index);
	return (line);
}

static char	*loop(int fd, char *line, t_gnl *gnl, ssize_t newl_index)
{
	while (42)
	{
		if (gnl->next_index >= gnl->b_read)
		{
			gnl->b_read = read(fd, gnl->read_buffer, BUFFER_SIZE);
			if (gnl->b_read <= 0 && !line)
				return (NULL);
			else if (gnl->b_read == -1 && line)
			{
				free(line);
				return (NULL);
			}
			gnl->next_index = 0;
		}
		newl_index = get_new_index(gnl);
		if (newl_index >= 0 || gnl->b_read < BUFFER_SIZE)
		{
			if (gnl->b_read != 0)
				line = update_line(line, newl_index, gnl);
			gnl->next_index = newl_index + 1;
			return (line);
		}
		line = update_line(line, gnl->b_read, gnl);
		gnl->next_index = gnl->b_read;
	}
}

static char	*update_line(char *line, size_t newl_index, t_gnl *gnl)
{
	char	*cpy_start;
	ssize_t	cpy_len;
	ssize_t	i;

	i = 0;
	cpy_start = gnl->read_buffer + gnl->next_index;
	cpy_len = newl_index - gnl->next_index + 1;
	if (line != NULL)
	{
		line = ft_strjoin_gnl(line, gnl->read_buffer, newl_index);
		return (line);
	}
	line = malloc((newl_index - gnl->next_index + 2) * sizeof(char));
	if (!line)
		return (NULL);
	while (cpy_start[i] && i < cpy_len)
	{
		line[i] = cpy_start[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static ssize_t	get_new_index(t_gnl *gnl)
{
	char	*buffer;
	ssize_t	index;
	ssize_t	len;

	buffer = gnl->read_buffer + gnl->next_index;
	len = gnl->b_read - gnl->next_index;
	index = 0;
	while (index < len && buffer[index] != '\0')
	{
		if (buffer[index] == '\n')
			return (index + gnl->next_index);
		index++;
	}
	if (gnl->b_read < BUFFER_SIZE)
		return (index + gnl->next_index - 1);
	return (-1);
}

static char	*ft_strjoin_gnl(char *s1, char *s2, ssize_t len)
{
	char		*line;
	ssize_t		s1_len;
	ssize_t		i;

	i = 0;
	s1_len = (size_t)ft_strlen(s1);
	line = malloc((s1_len + len + 2) * sizeof (char));
	if (!line)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		line[i] = s1[i];
		i++;
	}
	while (i <= s1_len + len)
	{
		line[i] = s2[i - s1_len];
		i++;
	}
	line[i] = '\0';
	free(s1);
	return (line);
}
