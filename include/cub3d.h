/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:06:00 by elopin            #+#    #+#             */
/*   Updated: 2025/09/04 21:45:03 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "macros.h"
# include "structs.h"
# include <X11/Xlib.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>

/* --------------- PARSER --------------- */

// check_config.c
void			parse_config_errors(t_parsing *parsing, char **config);
void			validate_xpm_files(t_parsing *parsing, char **config);
void			test_xpm(t_parsing *parsing, char *texture);
void			check_duplicate(t_parsing *p, char **config, char *key,
					size_t len);
void			validate_config_identifier(t_parsing *parsing, char **config);

// error_handlers.c
void			handle_trim_fail(char **array, char **config, size_t fail_idx);
void			map_error(t_parsing *parsing, char *err_msg, int c);
void			duplicate_found(t_parsing *parsing, char *key);
void			handle_misconfig(t_parsing *parsing, char **config, char *key);

// flood_fill.c
void			is_map_closed(t_parsing *parsing, char **map, char **map_copy);
void			flood_fill(t_ff *ff, char **map, int x, int y);
void			unfill_map(char **map, char **copy);

// format_map.c
char			**create_formatted_map(t_parsing *parsing, char **map_file);
void			fill_line(char *line, char *ref, size_t len);
char			**init_map_info(t_map_info *info, t_parsing *parsing,
					char **map_file);
size_t			get_map_height(char **map);
size_t			get_map_width(char **map);

// get_config.c
char			**get_config(char **file_content);
char			**dup_trim_config(char **array, size_t delim);
char			**fill_config_array(char **array, char **config, size_t delim);

// get_map.c
char			**get_map(t_parsing *parsing, char **file_content);
void			check_invalid_chars(t_parsing *parsing, char **map);
void			check_empty_lines(t_parsing *parsing, char **map);
void			set_player_start(t_parsing *parsing, char **map,
					t_player *player);
void			set_player_info(t_player *player, char dir, size_t y, size_t x);

// load_file.c
char			**load_file(int fd, char *filename);
ssize_t			get_file_size(int fd);
void			load_file_error(int fd, void *ptr);
void			read_error(int fd);

// parser.c
t_parsing		parser(int argc, char **argv, t_player *player);
int				handle_arguments(int argc, char **argv);
void			check_filename(char *filename);

// rgb_check.c
void			handle_rgb_values(char **config, t_parsing *parsing);
void			check_rgb_format(char *entry, t_parsing *parsing);
void			set_rgb_values(char *values, t_parsing *parsing, t_rgb *rgb);
void			rgb_error(t_parsing *parsing, char *entry, char *err);
void			rgb_too_big(t_parsing *parsing, char **array);

// utils.c
size_t			count_skips(char **array, size_t delim);
bool			is_map_line(char *line);
bool			is_valid_map_char(char c);
bool			is_player(char c);
bool			is_invalid_identifier(char *key);

/* --------------- INIT_GAME --------------- */

// init_.c
void			init_game(t_global *glb, t_parsing *parser);
void			init_glb_values(t_global *glb, t_parsing *parser);
void			init_mlx(t_global *glb, t_parsing *parsing);
void			init_hooks(t_global *glb, t_mlx *smlx);
void			load_game_textures(t_global *glb, t_parsing *parser);

// error_handlers.c
void			init_mlx_error(t_global *glb, t_parsing *parser, char *error);

// textures.c
void			load_parsed_textures(t_global *glb, t_parsing *parser);
void			set_parsed_path(t_parsing *parser, char **config);
void			load_xpm(t_global *glb, t_parsing *parser, t_img *img,
					char *xpm);

/* --------------- RAYCASTER --------------- */

// main.c
int				mouse_moved_advanced(int x, int y, void *param);
int				key_press(int keycode, t_global *glb);
int				key_release(int keycode, t_global *glb);
int				update(t_global *glb);

// calcul_for_draw.c
void			init_ray(t_global *glb, int x);
void			calculate_step_and_side_dist(t_global *glb);
void			perform_dda(t_global *glb);
void			calculate_wall_distance(t_global *glb);
void			perform_dda_ignoring_doors(t_global *glb, t_ray *ray);

// cam_moove.c
void			rotate_camera(t_global *glb, double angle);
bool			set_xy_for_move(t_global *glb, double *new_x, double *new_y,
					int direction);
void			move_player(t_global *glb, int direction);

// destroy.c
void			ft_clean_all(t_global *glb, int exit_code);
void			destroy_all_textures_imgs(void *mlx, t_global *glb);

// door.c
bool			set_xy(t_global *glb, int y, int x);
bool			check_door_acces(t_global *glb, int y, int x, char c);
void			ft_door(t_global *glb);

// draw.c
void			draw_ceiling_and_sky(t_global *glb, int x);
void			draw_floor(t_global *glb, int x);
void			draw_vertical_line(t_global *glb, int x);
void			draw_scene(t_global *glb);

// draw_wall_tex2.c
unsigned int	apply_distance_effect(unsigned int color, double dist);
unsigned int	get_normal_wall_color(t_global *glb, t_img *tex, int tex_x,
					int tex_y);
unsigned int	handle_door_opening(t_global *glb, int x, int y);
void			calculate_texture_params(t_global *glb, t_img *tex, int *tex_x,
					double *step);

// draw_wall_tex.c
void			calculate_secondary_ray(t_global *glb);
unsigned int	draw_wall_behind_door(t_global *glb, int y);
unsigned int	handle_sky_part(t_global *glb, int x, int y);
unsigned int	handle_floor_part(t_global *glb, int y);
void			draw_wall_texture(t_global *glb, int x, t_img *tex);

// flashlight.c
void			draw_flashlight(t_global *glb);

// minimap.c
void			draw_square(t_global *glb, int x, int y, int d);
void			draw_minimap(t_global *glb);
void			set_map_dimensions(t_global *glb);

// overlay.c
void			make_overlay(t_img *img, t_img *overlay);
void			draw_faded_circle(t_circle *circle, t_img *overlay, t_img *img);

// pixel_draw_utils.c
void			put_transparency(t_img *img, int y, int x);
void			draw_xpm_to_img(t_img *dst, t_img *img, int y, int x);
void			put_pixel_to_img(t_img *img, int color, int y, int x);
unsigned int	get_pixel_color(t_img *img, int y, int x);

// put_texture.c
void			put_pixel(t_img *img, int x, int y, int color);
t_img			*select_wall_texture(t_global *glb);
t_img			*select_wall_texture_from_ray(t_global *glb, t_ray *ray);

// small_function.c
unsigned int	effet_noir(unsigned int color, double factor);
bool			is_valid_map_position(t_global *glb, int x, int y);
long			get_current_time_ms(void);
unsigned int	ft_uni(t_rgb rgb);
void			put_fps_counter(t_global *glb);

#endif
