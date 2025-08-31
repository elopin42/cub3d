/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:26:15 by lle-cout          #+#    #+#             */
/*   Updated: 2025/03/07 03:16:37 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	if (!dest && !src)
		return (NULL);
	i = 0;
	tmp = (unsigned char *)src;
	if (src < dest)
	{
		while (n--)
			((unsigned char *)dest)[n] = tmp[n];
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = tmp[i];
			i++;
		}
	}
	return (dest);
}
