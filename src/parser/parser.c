/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:57:57 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/18 18:04:18 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_parsing(int argc, char **argv, t_global *glb)
{
	int			fd;
	t_parsing	parsing;

	ft_bzero(&parsing, sizeof (t_parsing));
	parsing.glb = glb;
	fd = handle_arguments(argc, argv);
	parsing.file_content = load_file(fd, argv[1], &parsing);
	split_config_and_map(&parsing);
}

void	split_config_and_map(t_parsing *parsing)
{
	char	**config;
	char	**map;

	// map = get_map(parsing->file_content); // check les empty lines en premier avant copy
	config = get_config(parsing->file_content);
	ft_print_strarray(config);
	ft_free_array(config);
	parsing->file_content = ft_free_array(parsing->file_content);
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
