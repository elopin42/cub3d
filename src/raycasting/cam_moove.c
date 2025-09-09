/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_moove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:29:20 by elopin            #+#    #+#             */
/*   Updated: 2025/09/04 22:55:23 by lle-cout         ###   ########.fr       */
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
	double (speed) = 0.08;
	if (direction == 1)
	{
		*new_x = glb->player.x + glb->player.dir_x * speed;
		*new_y = glb->player.y + glb->player.dir_y * speed;
	}
	else if (direction == 2)
	{
		*new_x = glb->player.x - glb->player.dir_x * speed;
		*new_y = glb->player.y - glb->player.dir_y * speed;
	}
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

void	move_player(t_global *glb, int direction)
{
	int		map_h;
	int		map_w;
	double	new_x;
	double	new_y;

	if (!set_xy_for_move(glb, &new_x, &new_y, direction))
		return ;
	int (mx) = (int)new_x;
	int (my) = (int)new_y;
	int (px) = (int)glb->player.x;
	int (py) = (int)glb->player.y;
	map_h = 0;
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
