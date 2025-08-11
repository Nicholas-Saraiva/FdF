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

t_3d ft_isometric(t_3d matrix1d)
{
    const float cos_z = 0.70710678118;
    const float sin_z = 0.70710678118;
    const float cos_x = 0.81649658092;
    const float sin_x = 0.57735026919;
    t_3d    result;

    result.x = matrix1d.x * cos_z - matrix1d.y * sin_z;
    result.y = matrix1d.x * sin_z * cos_x + matrix1d.y * cos_z * cos_x - matrix1d.z * sin_x;
    result.z = matrix1d.x * sin_z * sin_x + matrix1d.y * cos_z * sin_x + matrix1d.z * cos_x;
    result.color = matrix1d.color;
    return (result);
}

t_3d	ft_plane(t_3d matrix1d)
{
	t_3d	result;

	result.x = matrix1d.x;
	result.y = matrix1d.y;
	result.z = 0;
	result.color = matrix1d.color;
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