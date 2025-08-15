/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:31:04 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/15 12:53:18 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char **s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!*s)
		return (NULL);
	if (start >= ((unsigned int)ft_strlen(*s)))
	{
		new_str = (char *)malloc(1);
		if (!new_str)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	if (len > ((unsigned int)ft_strlen(*s)) - start)
		len = ((unsigned int)ft_strlen(*s)) - start;
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = start;
	j = 0;
	while (i < ((unsigned int)ft_strlen(*s)) && j < len)
		new_str[j++] = (*s)[i++];
	new_str[j] = '\0';
	return (new_str);
}
