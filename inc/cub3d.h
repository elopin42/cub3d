/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:06:00 by elopin            #+#    #+#             */
/*   Updated: 2025/07/27 21:00:54 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "get_next_line.h"
# include <X11/Xlib.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>

# define KEY_LEFT 65363
# define KEY_RIGHT 65361
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_E 101
# define MINIMAP_START_X 10
# define MINIMAP_START_Y 10
# define SQUARE_SIZE 8
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

typedef struct s_torch_data
{
	int				screen_w;
	int				screen_h;
	int				target_height;
	double			scale;
	int				scaled_width;
	int				scaled_height;
	int				x_offset;
	int				y_offset;
}					t_torch_data;

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win;
}					t_mlx;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct s_door_params
{
	t_ray			tmp_ray;
	double			tmp_dist;
	t_img			*tmp_tex;
	int				tmp_line_height;
	int				tmp_draw_start;
	int				tmp_draw_end;
	bool			ray_calculated;
}					t_door_params;

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_texture
{
	t_img			nord;
	t_img			sud;
	t_img			est;
	t_img			door;
	t_img			ouest;
	t_img			sol;
	t_img			sky;
	t_img			torche;
	t_img			white;
}					t_texture;

typedef struct s_global
{
	t_mlx			smlx;
	t_player		player;
	t_img			img;
	t_texture		texture;
	t_door_params	*door_params;
	t_ray			ray;
	char			**map;
	char			**map_clone;
	bool			key_left;
	bool			key_right;
	bool			key_w;
	bool			key_s;
	bool			key_a;
	bool			key_d;
	bool			key_tab;
	bool			mouse_locked;
	int				w;
	int				h;
	int				m_w;
	int				m_h;
	int				d_x;
	int				d_y;
	int				anim_door;
	int				door_start_y;
	int				door_height;
	int				el_muros_invisible;
	long			door_timing;
}					t_global;

// calcul_for_draw.c
void				calculate_wall_distance(t_global *glb);
void				perform_dda(t_global *glb);
void				calculate_step_and_side_dist(t_global *glb);
void				init_ray(t_global *glb, int x);
void				perform_dda_ignoring_doors(t_global *glb, t_ray *ray);

// draw_wall_tex.c
void				draw_wall_texture(t_global *glb, int x, t_img *tex);
unsigned int		get_normal_wall_color(t_global *glb, t_img *tex, int tex_x,
						int tex_y);
unsigned int		apply_distance_effect(unsigned int color, double dist);
unsigned int		handle_door_opening(t_global *glb, int x, int y);
void				calculate_texture_params(t_global *glb, t_img *tex,
						int *tex_x, double *step);

// torch and effects
void				draw_torch(t_global *glb);
void				calculate_secondary_ray(t_global *glb);
unsigned int		draw_wall_behind_door(t_global *glb, int y);
unsigned int		handle_sky_part(t_global *glb, int x, int y);
unsigned int		handle_floor_part(t_global *glb, int y);
unsigned int		effet_noir(unsigned int color, double factor);

// texture selection
t_img				*select_wall_texture_from_ray(t_global *glb, t_ray *ray);
t_img				*select_wall_texture(t_global *glb);

// utils and validation
bool				is_valid_map_position(t_global *glb, int x, int y);
long				get_current_time_ms(void);
bool				check_door_acces(t_global *glb, int y, int x, char c);

// core functions
void				ft_door(t_global *glb);
void				ft_clean_all(t_global *glb);
void				set_map_dimensions(t_global *glb);
void				frame_for_flame(t_global *glb);
void				put_pixel(t_img *img, int x, int y, int color);
void				load_texture(void *mlx, t_img *tex, char *path);
int					lunch_frame(t_global *glb);
bool				ft_init(t_global *glb, char **av);
void				draw_minimap(t_global *glb);
bool				init_texture(t_global *glb);
bool				ft_parsing(t_global *glb);
void				draw_scene(t_global *glb);
void				rotate_camera(t_global *glb, double angle);
void				move_player(t_global *glb, int direction);

// libftou functions
char				*get_next_line(int fd);
char				**ft_split(char const *s, char c);
void				*ft_calloc(size_t ec, size_t es);
int					ft_strstr(const char *b, const char *li);
void				*ft_memset(void *dest, int c, size_t count);
char				*ft_strdup(const char *src);

#endif