/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:06:00 by elopin            #+#    #+#             */
/*   Updated: 2025/07/08 20:25:41 by elopin           ###   ########.fr       */
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
#include <time.h>

#define KEY_LEFT 65363
#define KEY_RIGHT 65361
#define KEY_W 119        // W
#define KEY_S 115        // S
#define KEY_A 97         // A
#define KEY_D 100        // D
#define KEY_E 101        // D
#define MINIMAP_START_X 10
#define MINIMAP_START_Y 10
#define SQUARE_SIZE     8


typedef struct s_ray {
	double camera_x;
	double ray_dir_x, ray_dir_y;
	int map_x, map_y;
	double side_dist_x, side_dist_y;
	double delta_dist_x, delta_dist_y;
	double perp_wall_dist;
	int step_x, step_y;
	int side;
	int line_height, draw_start, draw_end;
} t_ray;


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
	int		width;
	int		height;
}	t_img;

typedef struct s_player {
	double x;      // position
	double y;
	double dir_x;  // direction
	double dir_y;
	double plane_x; // "caméra" à gauche/droite
	double plane_y;
} t_player;

typedef struct s_texture {
	t_img nord;
	t_img sud;
	t_img est;
	t_img door;
	t_img ouest;
	t_img sol;
	t_img sky;
	t_img torche;
	t_img white;
} t_texture;

typedef struct s_global{
	t_mlx smlx;
	t_player player;
	t_img	img;
  	t_texture texture;
	t_ray ray;
	char **map;
	char **map_clone;
  	bool key_left;
  	bool key_right;
  	bool key_w;
  	bool key_s;
  	bool key_a;
  	bool key_d;
	int	w;
	int	h;
  int m_w;
  int m_h;
  int	d_x;
  int d_y;
  int anim_door;
} t_global;


void ft_door(t_global *glb);
void	ft_clean_all(t_global *glb);
void	set_map_dimensions(t_global *glb);
void	frame_for_flame(t_global *glb);
void	put_pixel(t_img *img, int x, int y, int color);
void load_texture(void *mlx, t_img *tex, char *path);
int	lunch_frame(t_global *glb);
bool	ft_init(t_global *glb, char **av);
void draw_minimap(t_global *glb);
bool	init_texture(t_global *glb);
bool	ft_parsing(t_global *glb);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t ec, size_t es);
int		ft_strstr(const char *b, const char *li);
void	*ft_memset(void *dest, int c, size_t count);
void draw_scene(t_global *glb);
void	rotate_camera(t_global *glb, double angle);
void	move_player(t_global *glb, int direction);
char	*ft_strdup(const char *src);

#endif // !CUB3D
