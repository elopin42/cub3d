/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:11:50 by lle-cout          #+#    #+#             */
/*   Updated: 2025/03/07 03:16:37 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	get_str_size(long int *nbr)
{
	size_t			i;
	long int		nb;

	i = 1;
	nb = *nbr;
	if (*nbr < 0)
	{
		*nbr = -(*nbr);
		nb = -nb;
		i++;
	}
	while (nb / 10 > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t		i;
	long int	nbr;
	char		*str;

	nbr = n;
	i = get_str_size(&nbr);
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (nbr / 10 > 0)
	{
		i--;
		str[i] = nbr % 10 + '0';
		nbr /= 10;
	}
	str[--i] = nbr % 10 + '0';
	if (i == 1)
		str[--i] = '-';
	return (str);
}
