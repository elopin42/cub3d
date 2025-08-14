/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:28:34 by lle-cout          #+#    #+#             */
/*   Updated: 2025/03/07 03:16:37 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(char *s)
{
	size_t	i;
	char	*str;

	i = ft_strlen(s);
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i++;
	ft_strlcpy(str, s, i);
	return (str);
}
