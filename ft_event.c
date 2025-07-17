/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:38:51 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/17 21:07:27 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d	sum3dPoints(t_3d point1, t_3d point2)
{
	t_3d result;

	result.x = point1.x + point2.x;
	result.y = point1.y + point2.y;
	result.z = point1.z + point2.z;
	return (result);
}

t_3d	subtrate3dPoints(t_3d point1, t_3d point2)
{
	t_3d result;

	result.x = point1.x - point2.x;
	result.y = point1.y - point2.y;
	result.z = point1.z - point2.z;
	return (result);
}

void	ft_rotateCenter(t_data *data, t_3d (*RotationFunc)(t_3d, double), double angle)
{
	int	i;
	int	j;
	t_3d translated;

	i = -1;
	while (++i < data->map->height)
	{
		j = -1;
		while (++j < data->map->width)
		{
			translated = RotationFunc(subtrate3dPoints(data->map->matrix[i][j], data->map->center), angle);
			translated = sum3dPoints(translated, data->map->center);
			data->map->matrix[i][j] = translated;
		}
	}

}
