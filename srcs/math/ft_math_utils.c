/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:58:22 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/29 22:54:43 by nsaraiva         ###   ########.fr       */
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

t_3d	ft_isometric(t_3d matrix1d)
{
	return (rotate_x(rotate_z(matrix1d, 45 * M_PI / 180), 
				atan(1/sqrt(2))));
}

double	**init_matrix(void)
{
	int			i;
	double		**matrix3d;

	i = -1;
	matrix3d = (double **) ft_calloc(DIMENSIONAL, sizeof(double *));
	if (!matrix3d)
		ft_error("ERROR-ft_multMatrix: Malloc failed in var result.");
	while (++i < DIMENSIONAL)
	{
		matrix3d[i] = (double *) ft_calloc(DIMENSIONAL, sizeof(double *));
		if (!matrix3d[i])
		{
			free_matrix(&matrix3d, DIMENSIONAL);
			ft_error("ERROR-initMatrix3d: Malloc failed in matrix3d[i]");
		}
	}
	return (matrix3d);
}

void	find_min(t_map *map, t_3d value)
{
	map->max_x = fmax(map->max_x, value.x);
	map->min_x = fmin(map->min_x, value.x);
	map->min_y = fmin(map->min_y, value.y);
	map->max_y = fmax(map->max_y, value.y);
}
