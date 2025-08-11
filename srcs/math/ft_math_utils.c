/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:58:22 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/08 15:15:27 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d	sum_3d_points(t_3d point1, t_3d point2)
{
	t_3d	result;

	result.x = point1.x + point2.x;
	result.y = point1.y + point2.y;
	result.z = point1.z + point2.z;
	return (result);
}

t_3d	subtrate_3d_points(t_3d point1, t_3d point2)
{
	t_3d	result;

	result.x = point1.x - point2.x;
	result.y = point1.y - point2.y;
	result.z = point1.z - point2.z;
	return (result);
}

t_3d	new_point3d(int x, int y, int z)
{
	t_3d	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

void	find_limits(t_map *map, t_3d value)
{
	map->max_x = fmax(map->max_x, value.x);
	map->min_x = fmin(map->min_x, value.x);
	map->min_y = fmin(map->min_y, value.y);
	map->max_y = fmax(map->max_y, value.y);
}
