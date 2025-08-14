/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:34:28 by lle-cout          #+#    #+#             */
/*   Updated: 2025/07/05 13:35:33 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long long	ft_atoll(char *str)
{
	long long	nbr;
	int			signe;
	int			i;

	nbr = 0;
	signe = 1;
	i = 0;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * signe);
}
