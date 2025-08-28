/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:33:15 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/18 11:37:43 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_is_only_space(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (ft_isspace(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
