/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:57:57 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/12 12:06:18 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_parsing	parser(int argc, char **argv, t_player *player)
{
	int			fd;
	t_parsing	parsing;

	ft_bzero(&parsing, sizeof(t_parsing));
	parsing.player = player;
	fd = handle_arguments(argc, argv);
	parsing.file_content = load_file(fd, argv[1]);
	parsing.config = get_config(parsing.file_content);
	parse_config_errors(&parsing, parsing.config);
	parsing.map = get_map(&parsing, parsing.file_content);
	ft_free_array(parsing.file_content);
	return (parsing);
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
		ft_printf(STDERR_FILENO, XPMERROR, argv[1], strerror(errno));
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
		ft_printf(STDERR_FILENO, TOOSHORTERR);
		exit(EXIT_FAILURE);
	}
	else if (ft_strncmp(filename + len - 4, ".cub", 4))
	{
		ft_printf(STDERR_FILENO, FTYPEERR);
		exit(EXIT_FAILURE);
	}
}
