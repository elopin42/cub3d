/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:17:19 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/04 17:28:10 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

typedef struct s_rgb
{
	unsigned char					r;
	unsigned char					g;
	unsigned char					b;
}									t_rgb;

typedef struct s_parsing
{
	struct s_player					*player;
	char							**file_content;
	char							**config;
	char							**map;
	char							**map_copy;
	char							*no_path;
	char							*so_path;
	char							*we_path;
	char							*ea_path;
	bool							floor_set;
	struct s_rgb					floor;
	bool							ceiling_set;
	struct s_rgb					ceiling;
}									t_parsing;

typedef struct s_map_info
{
	size_t							i;
	size_t							width;
	size_t							height;
}									t_map_info;

typedef struct s_ff
{
	ssize_t							width;
	ssize_t							height;
	bool							map_is_open;
}									t_ff;

typedef struct s_torch_data
{
	int								screen_w;
	int								screen_h;
	int								target_height;
	double							scale;
	int								scaled_width;
	int								scaled_height;
	int								x_offset;
	int								y_offset;
	unsigned int					color;
}									t_torch_data;

typedef struct s_ray
{
	double							camera_x;
	double							ray_dir_x;
	double							ray_dir_y;
	int								map_x;
	int								map_y;
	double							side_dist_x;
	double							side_dist_y;
	double							delta_dist_x;
	double							delta_dist_y;
	double							perp_wall_dist;
	int								step_x;
	int								step_y;
	int								side;
	int								line_height;
	int								draw_start;
	int								draw_end;
}									t_ray;

typedef struct s_mlx
{
	void							*mlx;
	void							*mlx_win;
}									t_mlx;

typedef struct s_img
{
	bool							is_rgb;
	void							*img;
	char							*addr;
	int								bpp;
	int								line_length;
	int								endian;
	int								width;
	int								height;
	struct s_rgb					rgb;
}									t_img;

typedef struct s_door_params
{
	struct s_ray					tmp_ray;
	double							tmp_dist;
	struct s_img					*tmp_tex;
	int								tmp_line_height;
	int								tmp_draw_start;
	int								tmp_draw_end;
	bool							ray_calculated;
}									t_door_params;

typedef struct s_player
{
	double							x;
	double							y;
	double							dir_x;
	double							dir_y;
	double							plane_x;
	double							plane_y;
}									t_player;

typedef struct s_fps
{
	struct timeval	last_time;
	int				frame_count;
	int				fps;
}									t_fps;

typedef struct s_texture
{
	struct s_img					nord;
	struct s_img					sud;
	struct s_img					est;
	struct s_img					door;
	struct s_img					ouest;
	struct s_img					sol;
	struct s_img					sky;
	struct s_img					torche;
	struct s_img					overlay; // fond noir cercle transparent
	struct s_img					hand[10];
}									t_texture;

typedef struct s_circle
{
	int		top;
	int		bottom;
	int		dy;
	float	dx;
	int		left;
	int		right;
	int		y;
	int		x;
	int		cy;
	int		cx;
}	t_circle;

typedef struct s_global
{
	struct s_mlx					smlx;
	struct s_player					player;
	struct s_img					img;
	struct s_img					overlay;
	struct s_texture				texture;
	struct s_door_params			door_params;
	struct s_ray					ray;
	char							**map;
	char							**map_clone;
	bool							key_left;
	bool							key_right;
	bool							key_w;
	bool							key_s;
	bool							key_a;
	bool							key_d;
	bool							key_tab;
	bool							mouse_locked;
	int								w;
	int								h;
	int								m_w;
	int								m_h;
	int								d_x;
	int								d_y;
	int								anim_door;
	int								door_start_y;
	int								door_height;
	int								el_muros_invisible;
	int								square_size;
	long							door_timing;
}									t_global;

#endif
