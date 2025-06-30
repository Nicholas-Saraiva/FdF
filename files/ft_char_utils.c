/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:26:26 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/06/24 18:02:01 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	condition_for_c(va_list args)
{
	char	my_arg;

	my_arg	= (char)va_arg(args, int);
	if (!my_arg)
		my_arg = '\0';
	return (ft_putchar(my_arg));
}
