/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:03:41 by elopin            #+#    #+#             */
/*   Updated: 2025/08/26 23:26:36 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	mouse_moved_advanced(int x, int y, void *param)
{
	t_global	*glb;
	double		sensitivity;
	int			center_x;
	int			center_y;
	static int	mouse_locked = 1;

	(void)y;
	glb = (t_global *)param;
	sensitivity = 0.003;
	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	if (glb->key_tab)
	{
		mouse_locked = 0;
		glb->key_tab = false;
	}
	if (!mouse_locked)
		return (0);
	int (delta_x) = x - center_x;
	if (abs(delta_x) < 3)
		return (0);
	rotate_camera(glb, -delta_x * sensitivity);
	mlx_mouse_move(glb->smlx.mlx, glb->smlx.mlx_win, center_x, center_y);
	return (0);
}

int	key_press(int keycode, t_global *glb)
{
	if (keycode == 65307)
		return (printf("echape!\n"), ft_clean_all(glb, 0), 0);
	if (keycode == KEY_E)
		return (ft_door(glb), 0);
	if (keycode == KEY_LEFT)
		glb->key_left = true;
	if (keycode == KEY_RIGHT)
		glb->key_right = true;
	if (keycode == KEY_W)
		glb->key_w = true;
	if (keycode == KEY_S)
		glb->key_s = true;
	if (keycode == KEY_A)
		glb->key_a = true;
	if (keycode == KEY_D)
		glb->key_d = true;
	return (0);
}

int	key_release(int keycode, t_global *glb)
{
	if (keycode == KEY_LEFT)
		glb->key_left = false;
	if (keycode == KEY_RIGHT)
		glb->key_right = false;
	if (keycode == KEY_W)
		glb->key_w = false;
	if (keycode == KEY_S)
		glb->key_s = false;
	if (keycode == KEY_A)
		glb->key_a = false;
	if (keycode == KEY_D)
		glb->key_d = false;
	return (0);
}

int	update(t_global *glb)
{
	lunch_frame(glb);
	if (glb->key_w)
		move_player(glb, 1);
	if (glb->key_s)
		move_player(glb, 2);
	if (glb->key_a)
		move_player(glb, 3);
	if (glb->key_d)
		move_player(glb, 4);
	if (glb->key_left)
		rotate_camera(glb, -0.08);
	if (glb->key_right)
		rotate_camera(glb, 0.08);
	draw_scene(glb);
	if (glb->anim_door > 0)
	{
		glb->anim_door += 10;
		if (get_current_time_ms() - glb->door_timing >= 1500)
		{
			glb->anim_door = 0;
			glb->map[glb->d_y][glb->d_x] = '0';
		}
	}
	return (0);
}

void	load_texture(void *mlx, t_img *tex, char *path)
{
	if (tex->img)
		mlx_destroy_image(mlx, tex->img);
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Erreur chargement texture : %s\n", path);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length,
			&tex->endian);
}

int	main(int ac, char **av)
{
	t_global	glb;
	t_parsing	parsing;

	ft_bzero(&glb, sizeof (t_global));
	parsing = parser(ac, av, &glb.player);
	ft_print_strarray(parsing.config);
	ft_print_strarray(parsing.map);
	init_glb_values(&glb, &parsing);
	// init_mlx(&glb.smlx, &parsing);
	ft_free_array(parsing.config);
	ft_free_array(parsing.map);
	ft_free_array(parsing.map_copy);
	return (0);
}
