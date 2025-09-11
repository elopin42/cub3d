/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_moove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:29:20 by elopin            #+#    #+#             */
/*   Updated: 2025/09/11 15:08:42 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rotate_camera(t_global *glb, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = glb->player.dir_x;
	glb->player.dir_x = glb->player.dir_x * cos(angle) - glb->player.dir_y
		* sin(angle);
	glb->player.dir_y = old_dir_x * sin(angle) + glb->player.dir_y * cos(angle);
	old_plane_x = glb->player.plane_x;
	glb->player.plane_x = glb->player.plane_x * cos(angle) - glb->player.plane_y
		* sin(angle);
	glb->player.plane_y = old_plane_x * sin(angle) + glb->player.plane_y
		* cos(angle);
}

bool	set_xy_for_move(t_global *glb, double *new_x, double *new_y,
		int direction)
{
	double	speed;

	speed = 0.08;
	if (direction == 1)
		return (*new_x = glb->player.x + glb->player.dir_x * speed,
			*new_y = glb->player.y + glb->player.dir_y * speed, true);
	else if (direction == 2)
		return (*new_x = glb->player.x - glb->player.dir_x * speed,
			*new_y = glb->player.y - glb->player.dir_y * speed, true);
	else if (direction == 3)
	{
		*new_x = glb->player.x - glb->player.plane_x * speed;
		*new_y = glb->player.y - glb->player.plane_y * speed;
	}
	else if (direction == 4)
	{
		*new_x = glb->player.x + glb->player.plane_x * speed;
		*new_y = glb->player.y + glb->player.plane_y * speed;
	}
	else
		return (false);
	return (true);
}

static void	update_player_position(t_global *glb, double new_x, double new_y)
{
	int	map_w;
	int	mx;
	int	my;
	int	px;
	int	py;

	mx = (int)new_x;
	my = (int)new_y;
	px = (int)glb->player.x;
	py = (int)glb->player.y;
	int (map_h) = 0;
	while (glb->map && glb->map[map_h])
		map_h++;
	map_w = 0;
	if (map_h > 0)
		map_w = ft_strlen(glb->map[0]);
	if (glb->map[py][mx] == 'Q')
		show_congratulations(glb);
	if (py >= 0 && py < map_h && mx >= 0 && mx < map_w)
		if (glb->map[py][mx] != '1' && glb->map[py][mx] != 'D')
			glb->player.x = new_x;
	if (my >= 0 && my < map_h && px >= 0 && px < map_w)
		if (glb->map[my][px] != '1' && glb->map[my][px] != 'D')
			glb->player.y = new_y;
}

void	move_player(t_global *glb, int direction)
{
	double	new_x;
	double	new_y;

	if (!set_xy_for_move(glb, &new_x, &new_y, direction))
		return ;
	update_player_position(glb, new_x, new_y);
}

void	put_fps_counter(t_global *glb)
{
	static t_fps	fps;
	struct timeval	cur_time;
	long			elapsed;
	char			*fps_str;

	gettimeofday(&cur_time, NULL);
	fps.frame_count++;
	if (fps.last_time.tv_sec == 0 && fps.last_time.tv_usec == 0)
		fps.last_time = cur_time;
	elapsed = (cur_time.tv_sec - fps.last_time.tv_sec) * 1000000
		+ (cur_time.tv_usec - fps.last_time.tv_usec);
	if (elapsed >= 1000000)
	{
		fps.fps = fps.frame_count;
		fps.frame_count = 0;
		fps.last_time = cur_time;
	}
	if (fps.fps == 0)
		return ;
	fps_str = ft_itoa(fps.fps);
	if (fps_str == NULL)
		return ;
	mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win, 1255, 10, 0xFFFFFFFF,
		fps_str);
	free(fps_str);
}
