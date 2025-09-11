/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:06:55 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/12 14:43:58 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void		put_help_line(t_global *glb, int *y, int cl, char *str);
static inline void	put_timer_hud(t_global *glb, long minutes, long secondes);

void	put_fps_counter(t_global *glb)
{
	static t_fps	fps;
	long			elapsed;
	char			*fps_str;

	fps.frame_count++;
	if (fps.last_time == 0)
		fps.last_time = glb->now;
	elapsed = glb->now - fps.last_time;
	if (elapsed >= 1000)
	{
		fps.fps = fps.frame_count;
		fps.frame_count = 0;
		fps.last_time = glb->now;
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
	int		y;

	mlx_ptr = glb->smlx.mlx;
	mlx_win = glb->smlx.mlx_win;
	if (glb->texture.cur_hand->light_pwr == 0)
		cl = 0xFFFFFFFF;
	else
		cl = darken_pxl(0xFFFFFFFF, glb->texture.cur_hand->light_pwr);
	if (glb->showhelp == false)
		return ;
	y = WIN_HEIGHT - 10;
	put_help_line(glb, &y, cl, HELPSH);
	put_help_line(glb, &y, cl, HELPDR);
	if (glb->showmap == false)
		put_help_line(glb, &y, cl, HELPM);
	if (glb->lightoff == true)
		put_help_line(glb, &y, cl, HELPL);
	if (glb->key_tabu == false)
		put_help_line(glb, &y, cl, HELPT);
}

static void	put_help_line(t_global *glb, int *y, int cl, char *str)
{
	mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win, 10, *y, cl, str);
	*y -= 15;
}

static inline void	put_timer_hud(t_global *glb, long minutes, long secondes)
{
	char				*min;
	char				*sec;
	unsigned int		color;

	min = ft_itoa(minutes);
	sec = ft_itoa(secondes);
	if (glb->texture.cur_hand->light_pwr == 0)
		color = 0xFFFFFFFF;
	else
		color = darken_pxl(0xFFFFFFFF, glb->texture.cur_hand->light_pwr);
	if (min)
	{
		mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win,
			CENTER_X + 10, 10, color, min);
		free(min);
	}
	mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win,
		CENTER_X, 9, color, ":");
	if (sec)
	{
		mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win,
			CENTER_X - 10, 10, color, sec);
		free(sec);
	}
}
