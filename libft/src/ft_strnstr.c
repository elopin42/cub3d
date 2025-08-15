/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:30:20 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/15 13:09:49 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(char *s1, char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	char	*tmp1;

	i = 0;
	j = 0;
	tmp1 = (char *)s1;
	if (s2[i] == '\0')
		return ((char *)tmp1);
	while (i < n && tmp1[i] != 0)
	{
		j = 0;
		while (i < n && tmp1[i + j] == s2[j])
		{
			if (i + j < n && s2[j + 1] == 0)
				return ((char *)&tmp1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
