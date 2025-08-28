/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 00:12:43 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/18 10:57:59 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	word_count(char *s);
static size_t	word_len(char *s);
static char		*fill_line(char *line, char *s);
static void		free_matrix(char **matrix, size_t i);

char	**ft_matrix(char *s)
{
	size_t	w_count;
	size_t	i;
	char	**matrix;

	if (!s)
		return (NULL);
	i = 0;
	w_count = word_count(s);
	matrix = malloc((w_count + 1) * (sizeof (char *)));
	if (!matrix)
		return (NULL);
	while (i < w_count)
	{
		matrix[i] = malloc((word_len(s) + 1) * (sizeof (char)));
		if (!(matrix[i]))
		{
			free_matrix(matrix, i);
			return (NULL);
		}
		s = fill_line(matrix[i], s);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}

static size_t	word_count(char *s)
{
	size_t	count;
	size_t	i;

	count = 1;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

static size_t	word_len(char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != '\n')
		len++;
	return (len);
}

static char	*fill_line(char *line, char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	if (s[i] == '\n')
		i++;
	s = s + i;
	return (s);
}

static void	free_matrix(char **matrix, size_t i)
{
	while (i != 0)
	{
		free(matrix[i]);
		i--;
	}
	free(matrix[i]);
	free(matrix);
}
