/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:15:55 by elopin            #+#    #+#             */
/*   Updated: 2025/06/30 20:22:03 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	ft_write_file(t_global *glb, char **av)
{
	int		fd;
	char	*str;
	char	*tmp;
	char	**map;
	int		i = 0;

	tmp = NULL;
	str = NULL;

	fd = open(av[1], O_RDONLY);
	if (fd < 0 || fd > 1024)
		return (false);

	tmp = get_next_line(fd);
	while (tmp)
	{
		str = ft_strjoin(str, tmp); // accumule le contenu
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);

	map = ft_split(str, '\n');  // découpe
	free(str);                  // ici c’est OK de free

	int lines = 0;
	while (map[lines])
		lines++;

	glb->map = malloc((lines + 1) * sizeof(char *));
	if (!glb->map)
		return (false);

	for (i = 0; i < lines; i++)
		glb->map[i] = ft_strdup(map[i]);
	glb->map[i] = NULL;

	// libère l'ancien tableau temporaire
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);

	return (true);
}


void load_texture(void *mlx, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Erreur chargement texture : %s\n", path);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length, &tex->endian);
}

bool	ft_init(t_global *glb, char **av)
{
	if (!ft_strstr(av[1], ".cub"))
		return (printf("ton fichier n'est pas un .cub\n"), false);

	if (!ft_write_file(glb, av))
		return (printf("lecture fichier échouée\n"), false);

	glb->player.x = 3.5;
	glb->player.y = 2.5;
	glb->player.dir_x = -1;
	glb->player.dir_y = 0;
	glb->player.plane_x = 0;
	glb->player.plane_y = 0.66;
	glb->w = 1366;
	glb->h = 768;

	glb->smlx.mlx = mlx_init();
	if (!glb->smlx.mlx)
		return (printf("mlx_init() échoué\n"), false);

	glb->smlx.mlx_win = mlx_new_window(glb->smlx.mlx, glb->w, glb->h, "cub3d!");
	if (!glb->smlx.mlx_win)
		return (printf("mlx_new_window() échoué\n"), false);

	glb->img.img = mlx_new_image(glb->smlx.mlx, glb->w, glb->h);
	if (!glb->img.img)
		return (printf("mlx_new_image() échoué\n"), false);

	glb->img.addr = mlx_get_data_addr(glb->img.img,
		&glb->img.bpp, &glb->img.line_length, &glb->img.endian);
	if (!glb->img.addr)
		return (printf("mlx_get_data_addr() échoué\n"), false);

	load_texture(glb->smlx.mlx, &glb->texture.nord, "textures/nord.xpm");
	load_texture(glb->smlx.mlx, &glb->texture.sud,  "textures/sud.xpm");
	load_texture(glb->smlx.mlx, &glb->texture.est,  "textures/est.xpm");
	load_texture(glb->smlx.mlx, &glb->texture.ouest,"textures/ouest.xpm");
	load_texture(glb->smlx.mlx, &glb->texture.sol,  "textures/sol.xpm");
	load_texture(glb->smlx.mlx, &glb->texture.sky, "textures/sky.xpm");
	load_texture(glb->smlx.mlx, &glb->texture.torche, "textures/torche.xpm");
  set_map_dimensions(glb);
	return (true);
}
