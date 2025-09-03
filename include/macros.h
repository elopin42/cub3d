/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:18:24 by lle-cout          #+#    #+#             */
/*   Updated: 2025/09/03 16:40:43 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define KEY_LEFT 65363
# define KEY_RIGHT 65361
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_E 101
# define MINIMAP_START_X 10
# define MINIMAP_START_Y 10
# define WIN_WIDTH 1280
# define WIN_HEIGHT 700
# define MINIMAP_MAX_WIDTH  300
# define MINIMAP_MAX_HEIGHT 300

# define SPACES " \f\n\r\t\v"

# define ERR "\x1b[31mError\x1b[0m: "

# define CONFIGIDERR "\x1b[31mError\x1b[0m: Invalid identifier: %s\n"
# define EMPTYCONFIGERR "\x1b[31mError\x1b[0m: Missing value for:%s\n"
# define ARGERR "\x1b[31mError\x1b[0m: Invalid number of arguments\n"
# define NOMAPERR "\x1b[31mError\x1b[0m: No map in config file\n"
# define TOOSHORTERR "\x1b[31mError\x1b[0m: File name too short\n"
# define FTYPEERR "\x1b[31mError\x1b[0m: File type must be .cub\n"
# define INVCHARMAP "\x1b[31mError\x1b[0m: Invalid char '%c' in map\n"
# define EMPTYLINEMAP "\x1b[31mError\x1b[0m: Empty line in map\n"
# define STARTPOSERR "\x1b[31mError\x1b[0m: Multiple starting positions\n"
# define NOPLAYER "\x1b[31mError\x1b[0m: No starting position found\n"
# define CALLOCERR "\x1b[31mError\x1b[0m: ft_calloc()\n"
# define MAPOPENERR "\x1b[31mError\x1b[0m: Player isn't in a closed section\n"
# define CONFIGDUP "\x1b[31mError\x1b[0m: %s: Duplicate config identifier\n"
# define RGBFMT "\x1b[31mError\x1b[0m: Invalid RGB format: %s\n"
# define RGBTOOBIG "\x1b[31mError\x1b[0m: RGB Values must be [0-255]\n"
# define NOXPM "\x1b[31mError\x1b[0m: %s: File must have .xpm extension\n"
# define XPMERROR "\x1b[31mError\x1b[0m: %s: %s\n"

# define MLXINIT "mlx_init() failed\n"
# define MLXIMGERROR "mlx_new_image() failed\n"
# define MLXIMGADDR "mlx_get_data_addr() failed\n"
# define MLXXPM "mlx_xpm_file_to_image() failed\n"

# define NORTH "textures/north.xpm"
# define SOUTH "textures/south.xpm"
# define EAST "textures/east.xpm"
# define WEST "textures/west.xpm"

#endif
