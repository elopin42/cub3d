/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 00:48:40 by elopin            #+#    #+#             */
/*   Updated: 2025/07/27 21:01:34 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <string.h>

void	*ft_calloc(size_t ec, size_t es)
{
	void	*ptr;
	size_t	i;
	size_t	t;

	i = 0;
	t = ec * es;
	ptr = malloc(t);
	if (!ptr)
		return (NULL);
	while (i < t)
		((unsigned char *)ptr)[i++] = 0;
	return (ptr);
}

int	ft_strstr(const char *b, const char *li)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*li)
		return (0);
	while (b[i])
	{
		j = 0;
		while (li[j] == b[i] && b[i])
		{
			i++;
			j++;
		}
		if (!li[j])
			return (1);
		i -= j;
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *src)
{
	int			i;
	char		*str;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
