/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:17:19 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/14 16:17:23 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
