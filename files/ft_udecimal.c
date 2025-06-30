/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_udecimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:34:50 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/06/24 18:10:49 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_display_number(int n)
{
	char	nbr;

	nbr = '0' + n;
	return (write(1, &nbr, 1));
}

static int	ft_uputnbr(unsigned int n)
{
	int	size;

	size = 0;
	if (n > 9)
		size += ft_uputnbr(n / 10);
	size += ft_display_number(n % 10);
	return (size);
}

int	condition_for_udecimal(va_list args)
{
	unsigned int	n;

	n = va_arg(args, unsigned int);
	return (ft_uputnbr(n));
}
