/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 02:12:56 by elopin            #+#    #+#             */
/*   Updated: 2025/07/27 15:36:22 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_ray(t_global *glb, int x)
{
	glb->ray.camera_x = 2 * x / (double)glb->w - 1;
	glb->ray.ray_dir_x = glb->player.dir_x + glb->player.plane_x * glb->ray.camera_x;
	glb->ray.ray_dir_y = glb->player.dir_y + glb->player.plane_y * glb->ray.camera_x;
	
	glb->ray.map_x = (int)glb->player.x;
	glb->ray.map_y = (int)glb->player.y;
	
	glb->ray.delta_dist_x = fabs(1 / glb->ray.ray_dir_x);
	glb->ray.delta_dist_y = fabs(1 / glb->ray.ray_dir_y);
}

void	calculate_step_and_side_dist(t_global *glb)
{
	if (glb->ray.ray_dir_x < 0)
	{
		glb->ray.step_x = -1;
		glb->ray.side_dist_x = (glb->player.x - glb->ray.map_x) * glb->ray.delta_dist_x;
	}
	else
	{
		glb->ray.step_x = 1;
		glb->ray.side_dist_x = (glb->ray.map_x + 1.0 - glb->player.x) * glb->ray.delta_dist_x;
	}
	
	if (glb->ray.ray_dir_y < 0)
	{
		glb->ray.step_y = -1;
		glb->ray.side_dist_y = (glb->player.y - glb->ray.map_y) * glb->ray.delta_dist_y;
	}
	else
	{
		glb->ray.step_y = 1;
		glb->ray.side_dist_y = (glb->ray.map_y + 1.0 - glb->player.y) * glb->ray.delta_dist_y;
	}
}

bool	is_valid_map_position(t_global *glb, int x, int y)
{
	if ((y < 0 || x < 0) || !glb->map[y] || !glb->map[y][x])
		return (false);
	return (true);
}

void	perform_dda(t_global *glb)
{
	int (hit) = 0;
	while (hit == 0)
	{
		if (glb->ray.side_dist_x < glb->ray.side_dist_y)
		{
			glb->ray.side_dist_x += glb->ray.delta_dist_x;
			glb->ray.map_x += glb->ray.step_x;
			glb->ray.side = 0;
		}
		else
		{
			glb->ray.side_dist_y += glb->ray.delta_dist_y;
			glb->ray.map_y += glb->ray.step_y;
			glb->ray.side = 1;
		}
		if (!is_valid_map_position(glb, glb->ray.map_x, glb->ray.map_y) || glb->map[glb->ray.map_y][glb->ray.map_x] == '1')
			hit = 1;
		if ((!is_valid_map_position(glb, glb->ray.map_x, glb->ray.map_y) || glb->map[glb->ray.map_y][glb->ray.map_x] == 'D') && glb->el_muros_invisible)
			hit = 1;
	}
}

void	calculate_wall_distance(t_global *glb)
{
	if (glb->ray.side == 0)
		glb->ray.perp_wall_dist = (glb->ray.map_x - glb->player.x + (1 - glb->ray.step_x) / 2) / glb->ray.ray_dir_x;
	else
		glb->ray.perp_wall_dist = (glb->ray.map_y - glb->player.y + (1 - glb->ray.step_y) / 2) / glb->ray.ray_dir_y;
	glb->ray.line_height = (int)(glb->h / glb->ray.perp_wall_dist);
	glb->ray.draw_start = -glb->ray.line_height / 2 + glb->h / 2;
	glb->ray.draw_end = glb->ray.line_height / 2 + glb->h / 2;
	if (glb->ray.draw_start < 0)
		glb->ray.draw_start = 0;
	if (glb->ray.draw_end >= glb->h)
		glb->ray.draw_end = glb->h - 1;
}

void	draw_ceiling_and_sky(t_global *glb, int x)
{
	int (y) = -1;
	
	while (++y < glb->h / 2)
	{
		int tex_x = (x * glb->texture.sky.width) / glb->w;
		int tex_y = (y * glb->texture.sky.height) / (glb->h / 2);
		
		char *pixel = glb->texture.sky.addr + (tex_y * glb->texture.sky.line_length + tex_x * (glb->texture.sky.bpp / 8));
		unsigned int color = *(unsigned int *)pixel;
		put_pixel(&glb->img, x, y, color);
	}
}

t_img *select_wall_texture(t_global *glb)
{
    if (glb->map[glb->ray.map_y][glb->ray.map_x] == 'D')
        return (&glb->texture.door);
    if (glb->ray.side == 0 && glb->ray.ray_dir_x > 0)
        return (&glb->texture.ouest);
    if (glb->ray.side == 0 && glb->ray.ray_dir_x < 0)
        return (&glb->texture.est);
    if (glb->ray.side == 1 && glb->ray.ray_dir_y > 0)
        return (&glb->texture.nord);
    return (&glb->texture.sud);
}

unsigned int effet_noir(unsigned int color, double factor)
{
	unsigned char r = (color >> 16) & 0xFF;
	unsigned char g = (color >> 8) & 0xFF;
	unsigned char b = color & 0xFF;

	r = (unsigned char)(r * factor);
	g = (unsigned char)(g * factor);
	b = (unsigned char)(b * factor);

	return (r << 16) | (g << 8) | b;
}

void perform_dda_ignoring_doors(t_global *glb, t_ray *ray)
{
	int hit = 0;

	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}

		char tile = glb->map[ray->map_y][ray->map_x];
		if (tile == '1' || tile == 'D') // porte fermée et mur
			hit = 1;
		else if (!is_valid_map_position(glb, ray->map_x, ray->map_y))
			hit = 1;
		// case '3' est ignorée
	}
}

t_img *select_wall_texture_from_ray(t_global *glb, t_ray *ray)
{
    if (glb->map[ray->map_y][ray->map_x] == 'D')
        return (&glb->texture.door);
    if (ray->side == 0 && ray->ray_dir_x > 0)
        return (&glb->texture.ouest);
    if (ray->side == 0 && ray->ray_dir_x < 0)
        return (&glb->texture.est);
    if (ray->side == 1 && ray->ray_dir_y > 0)
        return (&glb->texture.nord);
    return (&glb->texture.sud);
}

void draw_wall_texture(t_global *glb, int x, t_img *tex)
{
	unsigned int color;
    // 1) Calcul de wall_x et tex_x
    double wall_x = (glb->ray.side == 0)
        ? glb->player.y + glb->ray.perp_wall_dist * glb->ray.ray_dir_y
        : glb->player.x + glb->ray.perp_wall_dist * glb->ray.ray_dir_x;
    wall_x -= floor(wall_x);

    int tex_x = (int)(wall_x * tex->width);
    if ((glb->ray.side == 0 && glb->ray.ray_dir_x > 0) ||
        (glb->ray.side == 1 && glb->ray.ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;

    // 2) Préparation du pas vertical dans la texture
    double step    = (double)tex->height / glb->ray.line_height;
    double tex_pos = (glb->ray.draw_start - glb->h / 2
                    + glb->ray.line_height / 2) * step;

    // 3) Paramètres de l’animation de porte
    bool  door_anim      = (glb->map_clone[glb->ray.map_y][glb->ray.map_x] == '3');
    int   clip_height    = glb->anim_door;
    if (clip_height > glb->door_height)
        clip_height = glb->door_height;
    int   white_start    = glb->door_start_y;
    int   white_end      = white_start + clip_height;
    t_img *white_tex     = &glb->texture.white;

    // 4) Boucle de dessin de la ligne verticale
    for (int y = glb->ray.draw_start; y < glb->ray.draw_end; y++)
    {
        int tex_y = ((int)tex_pos) & (tex->height - 1);
        tex_pos += step;

        char *pixel;
        if (door_anim && y >= white_start && y < white_end)
        {
            pixel = white_tex->addr
                  + tex_y * white_tex->line_length
                  + tex_x * (white_tex->bpp / 8);
			glb->el_muros_invisible = 0;
        }
		if (door_anim && y >= white_start && y < white_end)
		{
        	unsigned int color = *(unsigned int *)pixel;
	  		  // Créer une copie du ray
  		  	t_ray tmp_ray = glb->ray;
    		perform_dda_ignoring_doors(glb, &tmp_ray);

    		// Recalcule de la distance
    		double dist = (tmp_ray.side == 0)
        		? (tmp_ray.map_x - glb->player.x + (1 - tmp_ray.step_x) / 2) / tmp_ray.ray_dir_x
        		: (tmp_ray.map_y - glb->player.y + (1 - tmp_ray.step_y) / 2) / tmp_ray.ray_dir_y;

    		double wall_x = (tmp_ray.side == 0)
        		? glb->player.y + dist * tmp_ray.ray_dir_y
        		: glb->player.x + dist * tmp_ray.ray_dir_x;
    		wall_x -= floor(wall_x);

			t_img *tmp_tex = select_wall_texture_from_ray(glb, &tmp_ray);
    		int tmp_tex_x = (int)(wall_x * tex->width);
    		if ((tmp_ray.side == 0 && tmp_ray.ray_dir_x > 0) ||
        		(tmp_ray.side == 1 && tmp_ray.ray_dir_y < 0))
        		tmp_tex_x = tex->width - tmp_tex_x - 1;

    		char *pixel_tmp = tmp_tex->addr
        		+ tex_y * tmp_tex->line_length
        		+ tmp_tex_x * (tmp_tex->bpp / 8);

    		color = *(unsigned int *)pixel_tmp;
    		// if (dist > 1.0)
    		// {
    		//   		double d = dist - 1.0;
    		//   		double factor = 1.0 / (d * d * d + 1.0);
    		//   		if (factor < 0.02) factor = 0.02;
    		//   			color = effet_noir(color, factor);
    		//}
    		put_pixel(&glb->img, x, y, color);
    		continue;
		}
        else
        {
			glb->el_muros_invisible = 1;
            pixel = tex->addr
                  + tex_y * tex->line_length
                  + tex_x * (tex->bpp / 8);
        	color = *(unsigned int *)pixel;
        }

        if (glb->ray.perp_wall_dist > 1.0)
        {
            double d      = glb->ray.perp_wall_dist - 1.0;
            double factor = 1.0 / (d * d * d + 1.0);
            if (factor < 0.02) factor = 0.02;
            color = effet_noir(color, factor);
        }

        put_pixel(&glb->img, x, y, color);
    }
}

// donc c'est la que je dois faire une boucle while pour le mur;

void draw_floor(t_global *glb, int x)
{
	int y = glb->ray.draw_end + 1;
	double dist;
	double floor_x, floor_y;
	char *pix;

	while (y < glb->h)
	{
		dist = glb->h / (2.0 * y - glb->h);

		floor_x = glb->player.x + dist * glb->ray.ray_dir_x;
		floor_y = glb->player.y + dist * glb->ray.ray_dir_y;

		int tex_x = (int)(floor_x * glb->texture.sol.width) % glb->texture.sol.width;
		int tex_y = (int)(floor_y * glb->texture.sol.height) % glb->texture.sol.height;

		pix = glb->texture.sol.addr
			+ tex_y * glb->texture.sol.line_length
			+ tex_x * (glb->texture.sol.bpp / 8);

		unsigned int color = *(unsigned int *)pix;

    	if (dist > 1.0)
    	{
	    	double d = dist - 1.0;
	    	double factor = 1.0 / (d * d * d + 1.0);
	    	if (factor < 0.02)
		    	factor = 0.02;
	    	color = effet_noir(color, factor);
    	}

		put_pixel(&glb->img, x, y, color);
		y++;
	}
}



void	draw_vertical_line(t_global *glb, int x)
{
	t_img *tex;
	
	init_ray(glb, x);
	calculate_step_and_side_dist(glb);
	perform_dda(glb);
	calculate_wall_distance(glb);
	draw_ceiling_and_sky(glb, x);
	tex = select_wall_texture(glb);
	draw_wall_texture(glb, x, tex);
	draw_floor(glb, x);
	// if (!glb->el_muros_invisible)
	// 	draw_wall_texture(glb, x, tex);
}

void draw_torch(t_global *glb)
{
	if (!glb || !glb->texture.torche.img || !glb->texture.torche.addr)
		return;

	int screen_w = glb->w;
	int screen_h = glb->h;

	int target_height = (screen_h / 3) * 2;
	double scale = (double)target_height / glb->texture.torche.height;

	int scaled_width = glb->texture.torche.width * scale;
	int scaled_height = target_height;

	int x_offset = screen_w - screen_w / 2 + (screen_w / 2 - scaled_width) / 2;
	int y_offset = screen_h - scaled_height;

	for (int y = 0; y < glb->texture.torche.height; y++)
	{
		for (int x = 0; x < glb->texture.torche.width; x++)
		{
			char *pixel = glb->texture.torche.addr
				+ y * glb->texture.torche.line_length
				+ x * (glb->texture.torche.bpp / 8);
			unsigned int color = *(unsigned int *)pixel;

			if (color != 0xFF000000)
			{
				for (int dy = 0; dy < scale; dy++)
				{
					for (int dx = 0; dx < scale; dx++)
					{
						int screen_x = x_offset + x * scale + dx;
						int screen_y = y_offset + y * scale + dy;

						if (screen_x >= 0 && screen_x < screen_w && screen_y >= 0 && screen_y < screen_h)
							put_pixel(&glb->img, screen_x, screen_y, color);
					}
				}
			}
		}
	}
}

void	draw_scene(t_global *glb)
{
	int (x) = -1;
	while (++x < glb->w)
		draw_vertical_line(glb, x);
	draw_torch(glb);
  	draw_minimap(glb);
	mlx_put_image_to_window(glb->smlx.mlx, glb->smlx.mlx_win, glb->img.img, 0, 0);
}

void ft_door(t_global *glb)
{
    int mid = glb->w / 2;

    if (!glb->anim_door 
        && check_door_acces(glb, glb->player.y, glb->player.x, 'D'))
    {
        init_ray(glb, mid);
        calculate_step_and_side_dist(glb);
        perform_dda(glb);
        calculate_wall_distance(glb);
        glb->door_start_y = glb->ray.draw_start;
        glb->door_height  = glb->ray.line_height;
        glb->anim_door = 1;
        glb->map_clone[glb->d_y][glb->d_x] = '3';
        draw_scene(glb);
    }
    else if (!glb->anim_door 
             && check_door_acces(glb, glb->player.y, glb->player.x, '3'))
    {
		  glb->map[glb->d_y][glb->d_x] = 'D';
		  glb->map_clone[glb->d_y][glb->d_x] = 'D';
    }
}


