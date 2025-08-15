/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:59:50 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/15 13:05:36 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	guess_flag(int fd, va_list ap, char c, int conv_len);

int	ft_printf(int fd, char *format, ...)
{
	va_list	ap;
	int		i;
	int		print_len;

	i = 0;
	print_len = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			print_len += guess_flag(fd, ap, format[i], 0);
		}
		else
		{
			write(fd, &format[i], 1);
			print_len++;
		}
		i++;
	}
	va_end(ap);
	return (print_len);
}

static int	guess_flag(int fd, va_list ap, char c, int conv_len)
{
	if (c == 'c')
		conv_len += ft_putchar_fd(va_arg(ap, int), fd);
	if (c == 's')
		conv_len += ft_putstr_fd(va_arg(ap, char *), fd);
	if (c == 'p')
		conv_len += ft_putbase_fd((unsigned long long)va_arg(ap, void *),
				"0123456789abcdef", "0x", fd);
	if (c == 'd' || c == 'i')
		conv_len += ft_putnbr_fd(va_arg(ap, int), fd);
	if (c == 'u')
		conv_len += ft_putbase_fd(va_arg(ap, unsigned int),
				"0123456789", NULL, fd);
	if (c == 'x')
		conv_len += ft_putbase_fd(va_arg(ap, unsigned int),
				"0123456789abcdef", NULL, fd);
	if (c == 'X')
		conv_len += ft_putbase_fd(va_arg(ap, unsigned int),
				"0123456789ABCDEF", NULL, fd);
	if (c == '%')
		conv_len += ft_putchar_fd('%', fd);
	return (conv_len);
}
