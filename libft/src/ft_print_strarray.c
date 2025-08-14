/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_strarray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:36:02 by lle-cout          #+#    #+#             */
/*   Updated: 2025/05/05 19:27:57 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_strarray(char **ptr)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_arraylen((void **)ptr);
	while (i < len)
	{
		ft_printf(STDOUT_FILENO, "%s\n", ptr[i]);
		i++;
	}
}
