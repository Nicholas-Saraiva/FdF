/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:22:38 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/11 22:22:40 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d	ft_isometric(t_3d matrix1d)
{
	const float	cos_z = 0.707;
	const float	sin_z = 0.707;
	const float	cos_x = 0.816;
	const float	sin_x = 0.577;
	t_3d		result;

	result.x = matrix1d.x * cos_z - matrix1d.y * sin_z;
	result.y = (matrix1d.x * sin_z * cos_x + matrix1d.y * cos_z * cos_x
			) - (matrix1d.z * sin_x);
	result.z = (matrix1d.x * sin_z * sin_x + matrix1d.y * cos_z * sin_x
			) + (matrix1d.z * cos_x);
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
