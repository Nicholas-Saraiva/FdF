/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:58:22 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/15 17:53:30 by nsaraiva         ###   ########.fr       */
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

double	*ft_multMatrix3dto1d(double *leftMatrix[], double *rightMatrix)
{
	double *result;
	int		i;
	int		j;
	int		dim;

	i = -1;
	dim = 3;
	result = (double *) ft_calloc(dim, sizeof(double));
	if (!result)
		ft_error("ERROR-ft_multMatrix3dto1d: Malloc failed in var result.");
	while (++i < dim)
	{
		j = -1;
		while (++j < dim)
		{
			result[i] += leftMatrix[i][j] * rightMatrix[j];
		}
	}
	return result;
}

double **initMatrix()
{

	const int	dim = 3;
	int			i;
	double		**matrix3d;

	i = -1;
	matrix3d = (double **) ft_calloc(dim, sizeof(double *));
	if (!matrix3d)
		ft_error("ERROR-ft_multMatrix: Malloc failed in var result.");
	while (++i < dim)
	{
		matrix3d[i] = (double *) ft_calloc(dim, sizeof(double *));
		if (!matrix3d[i])
		{
			free_matrix(&matrix3d, dim);
			ft_error("ERROR-initMatrix3d: Malloc failed in matrix3d[i]");
		}
	}
	return matrix3d;
}

double	**ft_multMatrix3d(double *leftMatrix[], double *rightMatrix[])
{
	double **result;
	int		i;
	int		j;
	int		dim;

	i = -1;
	dim = 3;
	result = initMatrix();
	while (++i < dim)
	{
		j = -1;
		while (++j < dim)
		{
			result[i][j] += leftMatrix[i][j] * rightMatrix[j][i];
		}
	}
	return result;
}

void	find_min(t_map *map, t_2d value)
{
	map->max_x = fmax(map->max_x, value.x);
	map->min_x = fmin(map->min_x, value.x);
	map->min_y = fmin(map->min_y, value.y);
	map->max_y = fmax(map->max_y, value.y);
}
