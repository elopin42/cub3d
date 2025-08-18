/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:18:24 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/18 19:33:57 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define KEY_LEFT 65363
#define KEY_RIGHT 65361
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_E 101
#define MINIMAP_START_X 10
#define MINIMAP_START_Y 10
#define SQUARE_SIZE 8
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define SPACES " \f\n\r\t\v"

#define CONFIGFMTERR "\x1b[31mError\x1b[0m: Invalid config identifier: %s\n"
#define ARGERR "\x1b[31mError\x1b[0m: Invalid number of arguments\n"
#define NOMAPERR "\x1b[31mError\x1b[0m: No map in config file\n"
#define TOOSHORTERR "\x1b[31mError\x1b[0m: File name too short\n"
#define FTYPEERR "\x1b[31mError\x1b[0m: Wrong file type\n"
