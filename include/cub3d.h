/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:06:00 by elopin            #+#    #+#             */
/*   Updated: 2025/08/16 17:54:23 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <sys/time.h>
# include <time.h>
# include <X11/Xlib.h>
# include "structs.h"
# include "macros.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"


// ----- TMP -----------

void				init_parsing(int argc, char **argv, t_global *glb);
char				**load_file(int fd, char *filename, t_parsing *parsing);
void				load_file_error(int fd, void *ptr);
ssize_t				get_file_size(int fd);
int					handle_arguments(int argc, char **argv);
void				check_filename(char *filename);

// ----- TMP -----------

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
void				ft_free_map(char **map);
void				ft_door(t_global *glb);
void				ft_clean_all(t_global *glb, int exit_code);
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

#endif
