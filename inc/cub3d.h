/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:06:00 by elopin            #+#    #+#             */
/*   Updated: 2025/06/07 02:18:05 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB3D
# define CUB3D

#include "../mlx/mlx.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <math.h>

typedef struct s_mlx{
	void *mlx;
	void *mlx_win;
} t_mlx;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_player {
	double x;      // position
	double y;
	double dir_x;  // direction
	double dir_y;
	double plane_x; // "caméra" à gauche/droite
	double plane_y;
} t_player;

typedef struct s_global{
	t_mlx smlx;
	t_player player;
	t_img	img;
	char **map;
} t_global;

void	ft_clean_all(t_global *glb);
bool	ft_init(t_global *glb, char **av);
bool	ft_parsing(t_global *glb);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t ec, size_t es);
int		ft_strstr(const char *b, const char *li);
void	*ft_memset(void *dest, int c, size_t count);
void draw_scene(t_global *glb);

#endif // !CUB3D
