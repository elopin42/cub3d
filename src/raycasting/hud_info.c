/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:06:55 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/11 16:05:26 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	put_timer_hud(t_global *glb, long minutes, long secondes);

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
