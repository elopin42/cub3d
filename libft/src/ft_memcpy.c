/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:25:56 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/15 13:05:55 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned char	*tmpdest;
	unsigned char	*tmpsrc;

	if (!dest && !src)
		return (dest);
	tmpdest = dest;
	tmpsrc = src;
	while (n--)
		*tmpdest++ = *tmpsrc++;
	return (dest);
}
