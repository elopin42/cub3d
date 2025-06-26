#include "../inc/cub3d.h"

void	rotate_camera(t_global *glb, double angle)
{
	double	old_dir_x = glb->player.dir_x;
	glb->player.dir_x = glb->player.dir_x * cos(angle) - glb->player.dir_y * sin(angle);
	glb->player.dir_y = old_dir_x * sin(angle) + glb->player.dir_y * cos(angle);

	double	old_plane_x = glb->player.plane_x;
	glb->player.plane_x = glb->player.plane_x * cos(angle) - glb->player.plane_y * sin(angle);
	glb->player.plane_y = old_plane_x * sin(angle) + glb->player.plane_y * cos(angle);
}

void	move_player(t_global *glb, int direction)
{
	double	speed = 0.05;
	double	new_x, new_y;

	if (direction == 1) // Avancer
	{
		new_x = glb->player.x + glb->player.dir_x * speed;
		new_y = glb->player.y + glb->player.dir_y * speed;
	}
	else if (direction == 2) // Reculer
	{
		new_x = glb->player.x - glb->player.dir_x * speed;
		new_y = glb->player.y - glb->player.dir_y * speed;
	}
	else if (direction == 3) // Gauche (strafe)
	{
		new_x = glb->player.x - glb->player.plane_x * speed;
		new_y = glb->player.y - glb->player.plane_y * speed;
	}
	else if (direction == 4) // Droite (strafe)
	{
		new_x = glb->player.x + glb->player.plane_x * speed;
		new_y = glb->player.y + glb->player.plane_y * speed;
	}
	else
		return;

	int mx = (int)new_x;
	int my = (int)new_y;
	int px = (int)glb->player.x;
	int py = (int)glb->player.y;

	// calcul map_h et map_w à la volée
	int map_h = 0;
	while (glb->map[map_h])
		map_h++;

	int map_w = 0;
	if (map_h > 0)
		map_w = ft_strlen(glb->map[0]);

	// bornes de sécurité
	if (py >= 0 && py < map_h && mx >= 0 && mx < map_w)
	{
		if (glb->map[py][mx] != '1')
			glb->player.x = new_x;
	}
	if (my >= 0 && my < map_h && px >= 0 && px < map_w)
	{
		if (glb->map[my][px] != '1')
			glb->player.y = new_y;
	}

/*
	if (glb->map[(int)glb->player.y][(int)new_x] != '1')
		glb->player.x = new_x;
	if (glb->map[(int)new_y][(int)glb->player.x] != '1')
		glb->player.y = new_y;*/
}

