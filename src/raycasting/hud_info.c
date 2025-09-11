/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:06:55 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/11 16:08:41 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	put_timer_hud(t_global *glb, long minutes, long secondes);

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

void	put_timer(t_global *glb)
{
	long	elapsed;
	long	remaining;
	long	minutes;
	long	secondes;

	elapsed = glb->now - glb->start;
	remaining = TOTAL_TIME - elapsed;
	minutes = (remaining / 1000) % 60;
	secondes = (remaining / 1000) / 60;
	put_timer_hud(glb, minutes, secondes);
}

void	show_help(t_global *glb)
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		cl;

	mlx_ptr = glb->smlx.mlx;
	mlx_win = glb->smlx.mlx_win;
	cl = 0xFFFFFFFF;
	if (glb->showhelp == false)
		return ;
	mlx_string_put(mlx_ptr, mlx_win, 10, WIN_HEIGHT - 10, cl, HELPSH);
	mlx_string_put(mlx_ptr, mlx_win, 10, WIN_HEIGHT - 25, cl, HELPDR);
	if (glb->showmap == false)
	{
		if (glb->lightoff == true)
		{
			mlx_string_put(mlx_ptr, mlx_win, 10, WIN_HEIGHT - 40, cl, HELPM);
			mlx_string_put(mlx_ptr, mlx_win, 10, WIN_HEIGHT - 55, cl, HELPL);
		}
		else
			mlx_string_put(mlx_ptr, mlx_win, 10, WIN_HEIGHT - 40, cl, HELPM);
	}
	else if (glb->lightoff == true)
		mlx_string_put(mlx_ptr, mlx_win, 10, WIN_HEIGHT - 40, cl, HELPL);
}

static inline void	put_timer_hud(t_global *glb, long minutes, long secondes)
{
	char	*min;
	char	*sec;

	min = ft_itoa(minutes);
	sec = ft_itoa(secondes);
	if (min)
	{
		mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win,
			CENTER_X + 10, 10, 0xFFFFFFFF, min);
		free(min);
	}
	mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win,
		CENTER_X, 9, 0xFFFFFFFF, ":");
	if (sec)
	{
		mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win,
			CENTER_X - 10, 10, 0xFFFFFFFF, sec);
		free(sec);
	}
}
