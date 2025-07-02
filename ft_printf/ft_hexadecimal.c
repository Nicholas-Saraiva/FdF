/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:34:50 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/06/24 19:12:16 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int ft_puthex(unsigned int n, const char fmt)
{
    int size;

    size = 0;
    if (n >= 16)
		size += ft_puthex(n / 16, fmt);
	if ((n % 16) < 10)
		 size += ft_putchar((n % 16) + '0');
    else
    {
        if (fmt == 'x')
            size += ft_putchar((n % 16) - 10 + 'a');
        else if (fmt == 'X') 
			size += ft_putchar((n % 16) - 10 + 'A');
    }
    return (size);
}

int	condition_for_hex(va_list arg, const char fmt)
{
	unsigned int	n;
	
	n = va_arg(arg, unsigned int);
	return (ft_puthex(n, fmt));
}

