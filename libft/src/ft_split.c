/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:28:09 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/15 13:06:18 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	word_count(char *s, char c);
static size_t	word_len(char *s, char c);
static char		*fill_tab(char *split, char *s, char c);
static void		free_tab(char **split, size_t i);

char	**ft_split(char *s, char c)
{
	size_t	w_count;
	size_t	i;
	char	**split;

	if (!s)
		return (NULL);
	i = 0;
	w_count = word_count((char *)s, c);
	split = malloc((w_count + 1) * (sizeof (char *)));
	if (!split)
		return (NULL);
	while (i < w_count)
	{
		split[i] = malloc((word_len((char *)s, c) + 1) * (sizeof (char)));
		if (!(split[i]))
		{
			free_tab(split, i);
			return (NULL);
		}
		s = fill_tab(split[i], (char *)s, c);
		i++;
	}
	split[i] = NULL;
	return (split);
}

static size_t	word_count(char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static size_t	word_len(char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] == c && s[len] != '\0')
		s++;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

static char	*fill_tab(char *split, char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s == c && *s != '\0')
		s++;
	while (s[i] != c && s[i] != '\0')
	{
		split[i] = s[i];
		i++;
	}
	split[i] = '\0';
	s = s + i;
	while (*s == c && *s != '\0')
		s++;
	return (s);
}

static void	free_tab(char **split, size_t i)
{
	while (i != 0)
	{
		free(split[i]);
		i--;
	}
	free(split[i]);
	free(split);
}
