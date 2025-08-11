/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:38:51 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/08 15:10:26 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d	rotate_x(t_3d matrix1d, const float angle)
{
	t_3d	result;

	result.x = matrix1d.x;
	result.y = matrix1d.y * cos(angle) - matrix1d.z * sin(angle);
	result.z = matrix1d.y * sin(angle) + matrix1d.z * cos(angle);
	result.color = matrix1d.color;
	return (result);
}

t_3d	rotate_y(t_3d matrix1d, const float angle)
{
	t_3d	result;

	result.x = matrix1d.x * cos(angle) + matrix1d.z * sin(angle);
	result.y = matrix1d.y;
	result.z = -matrix1d.x * sin(angle) + matrix1d.z * cos(angle);
	result.color = matrix1d.color;
	return (result);
}

t_3d	rotate_z(t_3d matrix1d, const float angle)
{
	t_3d	result;

	result.x = matrix1d.x * cos(angle) - matrix1d.y * sin(angle);
	result.y = matrix1d.x * sin(angle) + matrix1d.y * cos(angle);
	result.z = matrix1d.z;
	result.color = matrix1d.color;
	return (result);
}

t_3d	ft_apply_rotation(t_map *map, t_3d point3d, float angle,
		t_3d (*rotate)(t_3d, float))
{
	t_3d	translated;

	translated = rotate(subtrate_3d_points(point3d,
				map->projection(map->center)), angle);
	translated = sum_3d_points(translated, map->projection(map->center));
	translated.color = point3d.color;
	return (translated);
}