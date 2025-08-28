/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:33:10 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/18 18:47:28 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_free_array(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL)
		return (NULL);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
	return (NULL);
}
