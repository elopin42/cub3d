/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:57:48 by elopin            #+#    #+#             */
/*   Updated: 2025/08/26 15:19:23 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_square(t_global *glb, int x, int y, int d)
{
	int	color;
	int	size;

	if (d == 1 || d == 2 || d == 4 || d == 5)
	{
		size = glb->square_size;
		if (d == 2)
			color = 0x222222;
		else if (d == 4)
			color = 0x800080;
		else if (d == 5)
			color = 0x80FF80;
		else
			color = 0x888888;
	}
	else if (d == 3)
	{
		size = glb->square_size / 2;
		color = 0xFF0000;
	}
	else
		return ;
	int (dy) = -1;
	while (++dy < size)
	{
		int (dx) = -1;
		while (++dx < size)
			put_pixel(&glb->img, x + dx, y + dy, color);
	}
}

void	draw_minimap(t_global *glb)
{
	int	screen_x;
	int	screen_y;
	int	x;

	int (y) = -1;
	while (++y < glb->m_h)
	{
		x = -1;
		while (++x < glb->m_w)
		{
      screen_x = MINIMAP_START_X + x * glb->square_size;
      screen_y = MINIMAP_START_Y + y * glb->square_size;
			if (glb->map_clone[y][x] == '1')
				draw_square(glb, screen_x, screen_y, 1);
			else if (glb->map_clone[y][x] == 'D' || glb->map_clone[y][x] == '3')
				draw_square(glb, screen_x, screen_y, 4);
			else if (glb->map_clone[y][x] == 'Q')
				draw_square(glb, screen_x, screen_y, 5);
			else
				draw_square(glb, screen_x, screen_y, 2);
		}
	}
  int (px) = MINIMAP_START_X + glb->player.x * glb->square_size;
  int (py) = MINIMAP_START_Y + glb->player.y * glb->square_size;
	draw_square(glb, px, py, 3);
}

void	set_map_dimensions(t_global *glb)
{
	int	i;
	int	max_width;
	int	len;

	i = -1;
	max_width = 0;
	while (glb->map[++i])
	{
		len = ft_strlen(glb->map[i]);
		if (len > max_width)
			max_width = len;
	}
	glb->m_h = i;
	glb->m_w = max_width;
	if (glb->m_w * glb->m_h > 10000)
	{
		glb->square_size = 0;
		printf("Minimap disabled: map too big (%dx%d)\n",
			glb->m_w, glb->m_h);
		return;
	}
	int size_x = MINIMAP_MAX_WIDTH / glb->m_w;
	int size_y = MINIMAP_MAX_HEIGHT / glb->m_h;
  if (size_x < size_y)
  	glb->square_size = size_x;
  else
	  glb->square_size = size_y;
	if (glb->square_size < 2)
		glb->square_size = 2;
}

