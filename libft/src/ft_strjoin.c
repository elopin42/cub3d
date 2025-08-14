/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:28:57 by lle-cout          #+#    #+#             */
/*   Updated: 2025/06/18 16:52:42 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	i;

	i = 0;
	new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
			* sizeof (char));
	if (!new)
		return (NULL);
	while (*s1)
		new[i++] = *s1++;
	while (*s2)
		new[i++] = *s2++;
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	char	*new;
	size_t	i;

	i = 0;
	new = malloc((ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1)
			* sizeof (char));
	if (!new)
		return (NULL);
	while (*s1)
		new[i++] = *s1++;
	while (*s2)
		new[i++] = *s2++;
	while (*s3)
		new[i++] = *s3++;
	new[i] = '\0';
	return (new);
}

/* strjoin but free s1 and s2 */
char	*ft_fstrjoin(char const *s1, char const *s2, short fs1, short fs2)
{
	char		*new;
	size_t		i;
	void		*ptr1;
	void		*ptr2;

	ptr1 = (void *)s1;
	ptr2 = (void *)s2;
	i = 0;
	new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
			* sizeof (char));
	if (!new)
		return (NULL);
	while (*s1)
		new[i++] = *s1++;
	while (*s2)
		new[i++] = *s2++;
	new[i] = '\0';
	if (fs1 == 1 && ptr1)
		free((void *)ptr1);
	if (fs2 == 1 && ptr2)
		free((void *)ptr2);
	return (new);
}
