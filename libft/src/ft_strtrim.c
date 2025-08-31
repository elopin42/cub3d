/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:30:52 by lle-cout          #+#    #+#             */
/*   Updated: 2025/03/07 03:16:37 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	is_set(char c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	left;
	size_t	right;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	left = 0;
	right = ft_strlen(s1) - 1;
	while (is_set(s1[left], (char *)set))
		left++;
	while (right > 0 && is_set(s1[right], (char *)set))
		right--;
	if (left > right)
		return (ft_strdup(""));
	str = malloc(right - left + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + left, right - left + 2);
	return (str);
}
