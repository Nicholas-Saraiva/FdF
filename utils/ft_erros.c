/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_erros.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:27:06 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/09 14:27:08 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error_map(const char *msg, t_map *map)
{
	free_map(map);
	perror(msg);
	exit(-1);
}

void	ft_error_data(const char *msg, t_data *data)
{
	free_data(data);
	perror(msg);
	exit(-1);
}
