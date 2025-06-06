/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopin <elopin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:42:17 by elopin            #+#    #+#             */
/*   Updated: 2025/06/07 01:19:58 by elopin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stddef.h>

char		*ft_substr_split(char const *s, unsigned int start, size_t len);
//#include <stdio.h>

static int	ft_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	if (!s || !*s)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static char	**ft_free(char **tab, int i)
{
	while (i >= 0)
		free(tab[i--]);
	free(tab);
	return (NULL);
}

static int	ft_s2(char const *s, char c)
{
	int	b;

	b = 0;
	while (s[b] && s[b] != c)
		b++;
	return (b);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		b;

	i = 0;
	b = 0;
	tab = (char **)ft_calloc((ft_count(s, c) + 1), sizeof(char *));
	if (!tab || !s)
		return (NULL);
	while (*s && tab != NULL)
	{
		if (*s)
		{
			b = ft_s2(s, c);
			tab[i] = ft_substr_split(s, 0, b);
			if (!tab[i] || *s == c)
				return (ft_free(tab, i));
			s += b;
			i++;
		}
		if (*s == c && *s)
			s++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*ft_substr_split(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (start >= (unsigned long)ft_strlen((char *)s))
	{
		new_str = (char *)malloc(1);
		if (!new_str)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	if (len > ft_strlen((char *)s) - start)
		len = ft_strlen((char *)s) - start;
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = start;
	j = 0;
	while (i < (unsigned long)ft_strlen((char *)s) && j < len)
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}

/*int	main(void)
{
	char	str[29] = " bon jour lle coyote";
	char	c = ' ';
	char	**tab = ft_split(str, c);
	int		i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	free(tab);
	return (0);
}*/
