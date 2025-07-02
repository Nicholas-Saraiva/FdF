/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:34:50 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/06/24 20:04:20 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int ft_puthex(unsigned int n)
{
    int size;

    size = 0;
    if (n >= 16)
		size += ft_puthex(n / 16);
	if ((n % 16) < 10)
		 size += ft_putchar((n % 16) + '0');
    else
		size += ft_putchar((n % 16) - 10 + 'a');
    return (size);
}

int	condition_for_p(va_list arg)
{
	unsigned int	n;
	
	n = va_arg(arg, unsigned long long);
	return (ft_puthex(n));
}
