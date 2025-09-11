/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:44:34 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/11 01:20:07 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char		*lightxpm(int i);
static double	lightpwr(int i);

void	init_light(t_global *glb, t_parsing *parser)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		load_xpm(glb, parser, &glb->texture.hand[i], lightxpm(i));
		glb->texture.hand[i].light_pwr = lightpwr(i);
		i++;
	}
}

static char	*lightxpm(int i)
{
	char	*files[10];

	files[0] = "textures/lightoff.xpm";
	files[1] = "textures/light40.xpm";
	files[2] = "textures/light75.xpm";
	files[3] = "textures/light100.xpm";
	files[4] = "textures/light125.xpm";
	files[5] = "textures/light150.xpm";
	files[6] = "textures/light175.xpm";
	files[7] = "textures/light200.xpm";
	files[8] = "textures/light225.xpm";
	files[9] = "textures/light255.xpm";
	return (files[i]);
}

static double	lightpwr(int i)
{
	double	power[10];

	power[0] = 0.0;
	power[1] = 40.0 / 255.0;
	power[2] = 75.0 / 255.0;
	power[3] = 100.0 / 255.0;
	power[4] = 125.0 / 255.0;
	power[5] = 150.0 / 255.0;
	power[6] = 175.0 / 255.0;
	power[7] = 200.0 / 255.0;
	power[8] = 225.0 / 255.0;
	power[9] = 1.0;
	return (power[i]);
}
