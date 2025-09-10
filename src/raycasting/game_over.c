//header

#include "../../include/cub3d.h"

void	game_over(t_global *glb)
{
    int x, y;
    int step_x = 200;  // espacement horizontal entre les textes
    int step_y = 50;   // hauteur d'une ligne de texte
    int color = 0xFF0000; // rouge

    // Parcours de l'écran verticalement
    for (y = 0; y < WIN_HEIGHT; y += step_y)
    {
        // On écrit "GAME OVER" plusieurs fois sur la ligne
        for (x = 0; x < WIN_WIDTH; x += step_x)
        {
            mlx_string_put(glb->smlx.mlx, glb->smlx.mlx_win, x, y, color, "GAME OVER");
        }
        mlx_do_sync(glb->smlx.mlx);
        // Mettre à jour la fenêtre progressivement
        usleep(300000); // 0.1 seconde par ligne pour effet progressif
    }
}
