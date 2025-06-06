/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:15:55 by elopin            #+#    #+#             */
/*   Updated: 2025/06/07 01:52:48 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	ft_write_file(t_global *glb, char **av)
{
	int		fd;
	char	*str;
	char	*tmp;

	tmp = NULL;
	fd = open(av[1], O_RDONLY);
	if (fd < 0 || fd > 1024)
		return (false);
	tmp = get_next_line(fd);
	while (tmp)
	{
		str = ft_strjoin(str, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	glb->map = ft_split(str, '\n');
	if (!glb->map)
		return (false);
	return (true);
}

bool	ft_init(t_global *glb, char **av)
{
	if (!(ft_strstr(av[1], ".cub")))
		return (printf("ton fichier n'est pas un .cub\n"), false);
	ft_write_file(glb, av);
	glb->smlx.mlx = mlx_init();
	glb->smlx.mlx_win = mlx_new_window(glb->smlx.mlx, 1920, 1080, "cub3d!");
	return (true);
}
