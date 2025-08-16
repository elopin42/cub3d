/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:15:55 by elopin            #+#    #+#             */
/*   Updated: 2025/08/16 17:56:59 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_parsing(int argc, char **argv, t_global *glb)
{
	int			fd;
	t_parsing	parsing;

	ft_bzero(&parsing, sizeof (t_parsing));
	fd = handle_arguments(argc, argv);
	parsing.file_content = load_file(fd, argv[1], &parsing);
/* 	ft_print_strarray(parsing.file_content);
	ft_free_map(parsing.file_content); */
}

char	**load_file(int fd, char *filename, t_parsing *parsing)
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
	{
		perror("Error: read()");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	content[total_size] = '\0';
	ret = ft_split(content, '\n');
	free(content);
	if (ret == NULL)
	{
		perror("Error: ft_split()");
		exit(EXIT_FAILURE);
	}
	return(ret);
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

ssize_t	get_file_size(int fd)
{
	ssize_t	read_ret;
	ssize_t	total_size;
	char	buf[1000];

	read_ret = read(fd, buf, 1000);
	if (read_ret == -1)
	{
		perror("Error: read()");
		close(fd);
		exit(EXIT_FAILURE);
	}
	total_size = read_ret;
	while (read_ret == 1000)
	{
		read_ret = read(fd, buf, 1000);
		if (read_ret == -1)
		{
			perror("Error: read()");
			close(fd);
			exit(EXIT_FAILURE);
		}
		total_size += read_ret;
	}
	close(fd);
	return(total_size);
}

int	handle_arguments(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		ft_printf(STDERR_FILENO, ARGERR);
		exit(EXIT_FAILURE);
	}
	check_filename(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error: open()");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	check_filename(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
	{
		ft_printf(STDERR_FILENO, "Error: File name too short\n");
		exit(EXIT_FAILURE);
	}
	else if (ft_strncmp(filename + len - 4, ".cub", 4))
	{
		ft_printf(STDERR_FILENO, "Error: Wrong file type\n");
		exit(EXIT_FAILURE);
	}
}
