/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:37:58 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/06/24 19:18:24 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_condition(const char **c, va_list args)
{
	if (**c == 'c')
		return (condition_for_c(args));
	if (**c == 's')
		return (condition_for_s(args));
	if (**c == 'p')
		return (condition_for_p(args));
	if (**c == 'd' || **c == 'i')
		return (condition_for_decimal(args));
	if (**c == 'u')
		return (condition_for_udecimal(args));
	if (**c == 'x' || **c == 'X')
		return (condition_for_hex(args, **c));
	if (**c == '%')
		return (ft_putchar(**c));
	return (0);
}

int	ft_printf(const char *fstring, ...)
{
	const char	*c;
	va_list		args;
	int			size;

	va_start(args, fstring);
	c = fstring;
	size = 0;
	while (*c)
	{
		if(*c != '%')
		{
			ft_putchar(*c);
			size++;
		}
		else
		{
			c++;
			size += check_condition(&c, args);
		}
		c++;
	}
	va_end(args);
	return (size);
}
