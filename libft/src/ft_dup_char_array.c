/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_char_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 02:45:08 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/20 02:53:23 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	*array_dup_error(char **ret, size_t i);

char	**ft_dup_char_array(char **array)
{
	size_t	i;
	size_t	len;
	char	**ret;

	i = 0;
	len = ft_arraylen((void **)array);
	if (len == 0)
		return (NULL);
	ret = ft_calloc(sizeof (char *), len + 1);
	if (ret == NULL)
		return (NULL);
	while (array[i])
	{
		ret[i] = ft_strdup(array[i]);
		if (ret[i] == NULL)
			return (array_dup_error(ret, i));
		i++;
	}
	return (ret);
}

static void	*array_dup_error(char **ret, size_t i)
{
	while (i > 0)
	{
		i--;
		free(ret[i]);
	}
	free(ret);
	return (NULL);
}
