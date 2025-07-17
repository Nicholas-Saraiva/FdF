/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:58:22 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/17 20:38:46 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_2d ft_transformation(t_3d matrix1d)
{
    t_2d	p;
    t_3d	result;

    result = RotateX(RotateZ(matrix1d, 45 * M_PI / 180), atan(sqrt(2))); 
    p.x = result.x;
    p.y = result.y;
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

t_3d	RotateX(t_3d matrix1d, const double angle)
{
	t_3d	result;

	result.x = matrix1d.x;
	result.y = matrix1d.y * cos((double) (angle))
				- matrix1d.z * sin((double) (angle));
	result.z = matrix1d.y * sin((double) (angle))
				+ matrix1d.z * cos((double) (angle));
	return result;
}

t_3d	RotateY(t_3d matrix1d, const double angle)
{
	t_3d	result;

	result.x = matrix1d.x * cos((double) (angle))
				+ matrix1d.z * sin((double) (angle));
	result.y = matrix1d.y;
	result.z = -matrix1d.x * sin((double) (angle))
				+ matrix1d.z * cos((double) (angle));
	return result;
}

t_3d	RotateZ(t_3d matrix1d, const double angle)
{
	t_3d	result;

	result.x = matrix1d.x * cos((double) (angle))
				- matrix1d.y * sin((double) (angle));
	result.y = matrix1d.x * sin((double) (angle))
				+ matrix1d.y * cos((double) (angle));
	result.z = matrix1d.z;
	return result;
}

void	find_min(t_map *map, t_3d value)
{
	t_2d	point2d;

	point2d = ft_transformation(value);
	map->max_x = fmax(map->max_x, point2d.x);
	map->min_x = fmin(map->min_x, point2d.x);
	map->min_y = fmin(map->min_y, point2d.y);
	map->max_y = fmax(map->max_y, point2d.y);
}
