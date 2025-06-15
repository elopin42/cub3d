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

