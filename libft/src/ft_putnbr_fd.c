/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:27:09 by lle-cout          #+#    #+#             */
/*   Updated: 2025/04/18 23:56:35 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	long int	nb;
	int			len;

	len = 0;
	nb = n;
	if (nb < 0)
	{
		len += write(fd, "-", 1);
		nb = -nb;
	}
	if (nb < 10)
	{
		len += ft_putchar_fd(nb + '0', fd);
	}
	else
	{
		len += ft_putnbr_fd(nb / 10, fd);
		len += ft_putchar_fd(nb % 10 + '0', fd);
	}
	return (len);
}
