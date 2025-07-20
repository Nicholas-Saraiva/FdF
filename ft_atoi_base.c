/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:51:59 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/20 17:16:35 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static int	condition_base(char nptr)
{
	return ((nptr >= '0' && nptr <= '9') ||
			(nptr >= 'a' && nptr <= 'f') ||
			(nptr >= 'A' && nptr <= 'F'));
}

static int	new_value(char nptr)
{
	if (nptr >= '0' && nptr <= '9')
		return (0 + (nptr - '0'));
	if (nptr >= 'a' && nptr <= 'f')
		return (0 + (nptr - 'a'));
	if (nptr >= 'A' && nptr <= 'F')
		return (0 + (nptr - 'A'));
	return (0);
}

static void move_number(const char **nptr, int *sign)
{
	if (**nptr == '-')
	{
		*sign = -1;
		(*nptr)++;
	}
	else if (**nptr == '+')
		(*nptr)++;
	(*nptr)++;
	if (**nptr && (**nptr == 'x' || **nptr == 'X'))
		(*nptr)++;
	else
		(*nptr)--;
}

static unsigned int power_value(int base, int power)
{
	unsigned int	value;

	value = 1;
	if(base == 0)
		return (0);
	while (power-- > 0)
		value *= base;
	return (value);
}

unsigned int	ft_atoi_base(const char *nptr, int base)
{
	unsigned int	value;
	int				sign;
	int				size;

	sign = 1;
	value = 0;
	move_number(&nptr, &sign);
	size = ft_strlen(nptr);
	while (*nptr && size-- >= 0)
	{
		if (!condition_base(*nptr))
			return (sign * value);
		value += power_value(base, size) * new_value(*nptr);
		nptr++;
	}
	return (sign * value);
}
