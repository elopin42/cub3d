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

	if (glb->map[(int)glb->player.y][(int)new_x] != '1')
		glb->player.x = new_x;
	if (glb->map[(int)new_y][(int)glb->player.x] != '1')
		glb->player.y = new_y;
}

