/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:38:51 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/25 13:58:48 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d	rotate_x(t_3d matrix1d, const double angle)
{
	t_3d	result;

	result.x = matrix1d.x;
	result.y = matrix1d.y * cos(angle) - matrix1d.z * sin(angle);
	result.z = matrix1d.y * sin(angle) + matrix1d.z * cos(angle);
	return (result);
}

t_3d	rotate_y(t_3d matrix1d, const double angle)
{
	t_3d	result;

	result.x = matrix1d.x * cos(angle) + matrix1d.z * sin(angle);
	result.y = matrix1d.y;
	result.z = -matrix1d.x * sin(angle) + matrix1d.z * cos(angle);
	return (result);
}

t_3d	rotate_z(t_3d matrix1d, const double angle)
{
	t_3d	result;

	result.x = matrix1d.x * cos(angle) - matrix1d.y * sin(angle);
	result.y = matrix1d.x * sin(angle) + matrix1d.y * cos(angle);
	result.z = matrix1d.z;
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
			translated.color = data->map->matrix[i][j].color;
			data->map->matrix[i][j] = translated;
		}
	}
	ft_bzero(data->addr, WIDTH * HEIGHT * sizeof(int));
}
