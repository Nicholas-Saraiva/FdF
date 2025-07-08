/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:58:22 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/06 21:17:33 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_2d	ft_transformation(int x, int y, int z)
{
	t_2d	p;

	p.x = (double)(x - y) * cos(RADIUS);
	p.y = (double)((x + y) * sin(RADIUS) - z);
	return (p);
}

void	find_min(t_matrix *map, int *values, int x)
{
	int		y;
	t_2d	cord;

	y = 0;
	while (y < map->width)
	{
		cord = ft_transformation(x, y, values[y]); 
		map->min_x = fmin(map->min_x, cord.x);
		map->min_y = fmin(map->min_x, cord.y);
		y++;
	}
}
