/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:51:59 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/08 15:13:42 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	condition_base(char nptr)
{
	return ((nptr >= '0' && nptr <= '9'
		) || (nptr >= 'a' && nptr <= 'f'
		) || (nptr >= 'A' && nptr <= 'F'));
}

static int	new_value(char nptr)
{
	if (nptr >= '0' && nptr <= '9')
		return ((nptr - '0'));
	if (nptr >= 'a' && nptr <= 'f')
		return ((nptr - 'a' + 10));
	if (nptr >= 'A' && nptr <= 'F')
		return ((nptr - 'A' + 10));
	return (0);
}

static void	move_number(const char **nptr, int *sign)
{
	if (**nptr == '-')
	{
		*sign = -1;
		(*nptr)++;
	}
	else if (**nptr == '+')
		(*nptr)++;
	if (**nptr && **nptr == '0' && (*(*nptr + 1)
			== 'x' || *(*nptr + 1) == 'X'))
	{
		*nptr += 2;
	}
}

unsigned int	ft_atoi_base(const char *nptr, int base)
{
	unsigned int	value;
	int				sign;

	sign = 1;
	value = 0;
	move_number(&nptr, &sign);
	while (*nptr && condition_base(*nptr))
	{
		value = value * base + new_value(*nptr);
		nptr++;
	}
	return (sign * value);
}
