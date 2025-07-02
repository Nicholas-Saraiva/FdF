/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:34:50 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/06/24 17:59:39 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_display_number(int n)
{
	char	nbr;

	nbr = '0' + n;
	return (write(1, &nbr, 1));
}

static int	ft_putnbr(int n)
{
	int	size;

	size = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		n *= -1;
		size += write(1, "-", 1);
	}
	if (n > 9)
		size += ft_putnbr(n / 10);
	size += ft_display_number(n % 10);
	return (size);
}

int	condition_for_decimal(va_list args)
{
	int	n;

	n = va_arg(args, int);
	return (ft_putnbr(n));
}
