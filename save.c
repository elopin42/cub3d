void	ft_init(t_global *glb, char **av)
{
	glb->smlx.mlx = mlx_init();
	if (!glb->smlx.mlx)
		return (printf("mlx_init() échoué\n"), false);


	glb->smlx.mlx_win = mlx_new_window(glb->smlx.mlx, glb->w, glb->h, "cub3d!");
	if (!glb->smlx.mlx_win)
		return (printf("mlx_new_window() échoué\n"), false);


	glb->img.img = mlx_new_image(glb->smlx.mlx, glb->w, glb->h);
	if (!glb->img.img)
		return (printf("mlx_new_image() échoué\n"), false);


	glb->img.addr = mlx_get_data_addr(glb->img.img, &glb->img.bpp, &glb->img.line_length, &glb->img.endian);
	if (!glb->img.addr)
		return (printf("mlx_get_data_addr() échoué\n"), false);


	glb->door_params = malloc(sizeof(t_door_params));
	if (!glb->door_params)
		return (printf("error\n"), 1);


	load_texture(glb->smlx.mlx, &glb->texture.nord, "textures/nord.xpm");
	load_texture(glb->smlx.mlx, &glb->texture.sud, "textures/sud.xpm");
	load_texture(glb->smlx.mlx, &glb->texture.est, "textures/est.xpm");
	load_texture(glb->smlx.mlx, &glb->texture.ouest, "textures/ouest.xpm");

	load_texture(glb->smlx.mlx, &glb->texture.sol, "textures/sol.xpm");
	load_texture(glb->smlx.mlx, &glb->texture.sky, "textures/sky.xpm");

	load_texture(glb->smlx.mlx, &glb->texture.torche, "textures/torche.xpm");
	load_texture(glb->smlx.mlx, &glb->texture.door, "textures/door.xpm");
}

/* 	mlx_hook(glb.smlx.mlx_win, 2, 1L << 0, key_press, &glb);
	mlx_hook(glb.smlx.mlx_win, 3, 1L << 1, key_release, &glb);
	mlx_hook(glb.smlx.mlx_win, 6, 1L << 6, mouse_moved_advanced, &glb);
	mlx_loop_hook(glb.smlx.mlx, update, &glb);
	mlx_hook(glb.smlx.mlx_win, 17, 0, (void *)ft_clean_all, &glb);
	mlx_mouse_move(glb.smlx.mlx, glb.smlx.mlx_win, WIN_WIDTH / 2, WIN_HEIGHT
		/ 2);
	return (mlx_loop(glb.smlx.mlx)); */
