/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:07:53 by elopin            #+#    #+#             */
/*   Updated: 2025/06/06 23:46:48 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

#include "../mlx/mlx.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_mlx{
	void *mlx;
	void *mlx_win;
} t_mlx;

typedef struct s_global{
	t_mlx smlx;
} t_global;

bool	ft_init(t_global *glb);

#endif // !CUB3D
