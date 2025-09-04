/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:48:39 by elopin            #+#    #+#             */
/*   Updated: 2025/09/04 18:00:33 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned int	effet_noir(unsigned int color, double factor)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (unsigned char)(r * factor);
	g = (unsigned char)(g * factor);
	b = (unsigned char)(b * factor);
	return ((r << 16) | (g << 8) | b);
}

bool	is_valid_map_position(t_global *glb, int x, int y)
{
	if ((y < 0 || x < 0) || !glb->map[y] || !glb->map[y][x])
		return (false);
	return (true);
}

long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

unsigned int	ft_uni(t_rgb rgb)
{
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

void	put_fps_counter(t_global *glb)
{
	static t_fps			fps;
	struct timeval			cur_time;
	long					elapsed;
	char					*fps_str;

	gettimeofday(&cur_time, NULL);
	fps.frame_count++;
	if (fps.last_time.tv_sec == 0 && fps.last_time.tv_usec == 0)
		fps.last_time = cur_time;
	elapsed = (cur_time.tv_sec - fps.last_time.tv_sec)
		* 1000000 + (cur_time.tv_usec - fps.last_time.tv_usec);
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
	mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win,
		1255, 10, 0xFFFFFFFF, fps_str);
	free(fps_str);
}
