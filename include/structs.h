/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:17:19 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/25 15:36:10 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

typedef struct s_parsing
{
	struct s_player	*player;
	char			**file_content;
	char			**config;
	char			**map;
	char			**map_copy;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	bool			floor_set;
	struct s_rgb	floor;
	bool			ceiling_set;
	struct s_rgb	ceiling;
}	t_parsing;

typedef struct s_map_info
{
	size_t	i;
	size_t	width;
	size_t	height;
}	t_map_info;

typedef struct s_ff
{
	ssize_t	width;
	ssize_t	height;
	bool	map_is_open;
}	t_ff;

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
}	t_torch_data;

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
}	t_ray;

typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win;
}	t_mlx;

typedef struct s_img
{
	bool			is_rgb;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	struct s_rgb	*rgb;
}	t_img;

typedef struct s_door_params
{
	struct s_ray	tmp_ray;
	double			tmp_dist;
	struct s_img	*tmp_tex;
	int				tmp_line_height;
	int				tmp_draw_start;
	int				tmp_draw_end;
	bool			ray_calculated;
}	t_door_params;

typedef struct s_player
{
	double	x;		// Position X du joueur dans la map (coordonnée flottante)
	double	y;		// Position Y du joueur dans la map
	double	dir_x;	// Direction du joueur sur l'axe X (vers où il regarde)
	double	dir_y;	// Direction du joueur sur l'axe Y
	double	plane_x; // Plan de la caméra X (détermine le champ de vision horizontal)
	double	plane_y; // Plan de la caméra Y (détermine le champ de vision horizontal)
}	t_player;

typedef struct s_texture
{
	struct s_img	nord;
	struct s_img	sud;
	struct s_img	est;
	struct s_img	door;
	struct s_img	ouest;
	struct s_img	sol;
	struct s_img	sky;
	struct s_img	torche;
	struct s_img	white;
}	t_texture;

typedef struct s_global
{
	struct s_mlx			smlx; //pointer mlx
	struct s_player			player; //struct info joueurs
	struct s_img			img; //struct pour la window
	struct s_texture		texture; //struct  pour les texture
	struct s_door_params	*door_params; //strucut pour gerer l'ouverture de porte
	struct s_ray			ray; //pour le calcul de rayon
	char					**map; //la map sous forme de char **
	char					**map_clone; //clone de la map pour toujours retrouver ou son les portes quand elle son ouverte
// -------- ce que permet de rester appuyer sur la touche pour avancer
	bool					key_left;
	bool					key_right;
	bool					key_w;
	bool					key_s;
	bool					key_a;
	bool					key_d;
  //-------------
	bool					key_tab;// je crois on peut suprimer sa a reverifier quand sa marche
	bool					mouse_locked; //sa aussi a reverifier j'ai un doute car de memoir je me souviens pourquoi il y a sa mais la dans le code sa a l'air de pas servir
	int						w; //size de la fenetre
	int						h; //same
	int						m_w; //taille max du char** utiliser pour la mini map
	int						m_h; //same
	int						d_x; //pour l'animation de la door en gros sa save l'emplacement de la porte que on a voulu ouvrir
	int						d_y; // comme sa toute les porte n'on pas de animation seulement celle select
	int						anim_door; // pour savoir si une animation es en cours
	int						door_start_y; //calcule pour savoir ou on en es dans l'animation de la porte, ce qui permet le degrader
	int						door_height; // de memoir c'est ce qui permet de garder le rendu en gros si on seloigne ou autre mais j'ai un doute
	int						el_muros_invisible; // je crois cette variables ne sert pu a rien car quand je regarde dans le code elle es dans aucune condition
	long					door_timing;// pour gerer le temps ou on en es pour l'ouverture mais dailleur le temps de ouverture ou on peut traverser la porte es fixe.
}	t_global;

#endif
