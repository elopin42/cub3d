/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 00:07:21 by lle-cout          #+#    #+#             */
/*   Updated: 2025/04/24 15:38:48 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_putbase_print_fd(unsigned long long nbr, char *base,
	int base_len, int fd)
{
	int	len;

	len = 0;
	if (nbr / base_len > 0)
		len += ft_putbase_print_fd(nbr / base_len, base, base_len, fd);
	len += ft_putchar_fd(base[nbr % base_len], fd);
	return (len);
}

int	ft_putbase_fd(unsigned long long nbr, char *base, char *prefix, int fd)
{
	int	len;
	int	base_len;

	len = 0;
	base_len = ft_strlen(base);
	if (prefix && nbr == 0)
		return (write(fd, "(nil)", 5));
	else if (prefix)
		len += write(fd, &prefix[0], ft_strlen(prefix));
	len += ft_putbase_print_fd(nbr, base, base_len, fd);
	return (len);
}
