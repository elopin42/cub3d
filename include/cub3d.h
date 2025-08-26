/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:06:00 by elopin            #+#    #+#             */
/*   Updated: 2025/08/26 23:23:01 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <X11/Xlib.h>
# include "structs.h"
# include "macros.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"

/* --------------- PARSER --------------- */

// check_config.c
void			parse_config_errors(t_parsing *parsing, char **config);
void			validate_xpm_files(t_parsing *parsing, char **config);
void			test_xpm(t_parsing *parsing, char *texture);
void			check_duplicate(t_parsing *p, char **config, char *key, size_t len);
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
char			**init_map_info(t_map_info *info, t_parsing *parsing, char **map_file);
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
void			set_player_start(t_parsing *parsing, char **map, t_player *player);
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
void			init_mlx(t_mlx *smlx, t_parsing *parser);
void			init_glb_values(t_global *glb, t_parsing *parser);

// error_handlers.c
void			init_mlx_error(t_mlx *smlx, t_parsing *parser, char *error);


/* --------------- RAYCASTER --------------- */

// calcul_for_draw.c
void			calculate_wall_distance(t_global *glb);
void			perform_dda(t_global *glb);
void			calculate_step_and_side_dist(t_global *glb);
void			init_ray(t_global *glb, int x);
void			perform_dda_ignoring_doors(t_global *glb, t_ray *ray);

// draw_wall_tex.c
void			draw_wall_texture(t_global *glb, int x, t_img *tex);
unsigned int	get_normal_wall_color(t_global *glb, t_img *tex, int tex_x,
					int tex_y);
unsigned int	apply_distance_effect(unsigned int color, double dist);
unsigned int	handle_door_opening(t_global *glb, int x, int y);
void			calculate_texture_params(t_global *glb, t_img *tex,
					int *tex_x, double *step);

// torch and effects
void			draw_torch(t_global *glb);
void			calculate_secondary_ray(t_global *glb);
unsigned int	draw_wall_behind_door(t_global *glb, int y);
unsigned int	handle_sky_part(t_global *glb, int x, int y);
unsigned int	handle_floor_part(t_global *glb, int y);
unsigned int	effet_noir(unsigned int color, double factor);

// texture selection
t_img			*select_wall_texture_from_ray(t_global *glb, t_ray *ray);
t_img			*select_wall_texture(t_global *glb);

// utils and validation
bool			is_valid_map_position(t_global *glb, int x, int y);
long			get_current_time_ms(void);
bool			check_door_acces(t_global *glb, int y, int x, char c);

// core functions
void			ft_free_map(char **map);
void			ft_door(t_global *glb);
void			ft_clean_all(t_global *glb, int exit_code);
void			set_map_dimensions(t_global *glb);
void			frame_for_flame(t_global *glb);
void			put_pixel(t_img *img, int x, int y, int color);
void			load_texture(void *mlx, t_img *tex, char *path);
int				lunch_frame(t_global *glb);
bool			ft_init(t_global *glb, char **av);
void			draw_minimap(t_global *glb);
bool			init_texture(t_global *glb);
bool			ft_parsing(t_global *glb);
void			draw_scene(t_global *glb);
void			rotate_camera(t_global *glb, double angle);
void			move_player(t_global *glb, int direction);

#endif
