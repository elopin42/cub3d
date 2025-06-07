/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:15:55 by elopin            #+#    #+#             */
/*   Updated: 2025/06/07 02:23:10 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	ft_write_file(t_global *glb, char **av)
{
	int		fd;
	char	*str;
	char	*tmp;

	tmp = NULL;
	str = NULL;
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
	if (!ft_strstr(av[1], ".cub"))
		return (printf("ton fichier n'est pas un .cub\n"), false);

	if (!ft_write_file(glb, av))
		return (printf("lecture fichier échouée\n"), false);

	// Position & direction du joueur (provisoire)
	glb->player.x = 3.5;
	glb->player.y = 2.5;
	glb->player.dir_x = -1;
	glb->player.dir_y = 0;
	glb->player.plane_x = 0;
	glb->player.plane_y = 0.66;

	// Initialisation MLX
	glb->smlx.mlx = mlx_init();
	if (!glb->smlx.mlx)
		return (printf("mlx_init() échoué\n"), false);

	glb->smlx.mlx_win = mlx_new_window(glb->smlx.mlx, 1920, 1080, "cub3d!");
	if (!glb->smlx.mlx_win)
		return (printf("mlx_new_window() échoué\n"), false);

	glb->img.img = mlx_new_image(glb->smlx.mlx, 1920, 1080);
	if (!glb->img.img)
		return (printf("mlx_new_image() échoué\n"), false);

	glb->img.addr = mlx_get_data_addr(glb->img.img,
		&glb->img.bpp, &glb->img.line_length, &glb->img.endian);
	if (!glb->img.addr)
		return (printf("mlx_get_data_addr() échoué\n"), false);

	return (true);
}
