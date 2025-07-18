/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:38:51 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/18 16:13:45 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_3d	sum_3d_points(t_3d point1, t_3d point2)
{
	t_3d	result;

	result.x = point1.x + point2.x;
	result.y = point1.y + point2.y;
	result.z = point1.z + point2.z;
	return (result);
}

static t_3d	subtrate_3d_points(t_3d point1, t_3d point2)
{
	t_3d	result;

	result.x = point1.x - point2.x;
	result.y = point1.y - point2.y;
	result.z = point1.z - point2.z;
	return (result);
}

void	ft_rotate(t_data *data, t_3d (*rotate)(t_3d, double), double angle)
{
	int		i;
	int		j;
	t_3d	translated;

	i = -1;
	while (++i < data->map->height)
	{
		j = -1;
		while (++j < data->map->width)
		{
			translated = rotate(subtrate_3d_points(data->map->matrix[i][j],
						data->map->center), angle);
			translated = sum_3d_points(translated, data->map->center);
			data->map->matrix[i][j] = translated;
		}
	}
}
