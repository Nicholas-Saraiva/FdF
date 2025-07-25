/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:31:17 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/25 13:06:36 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->height)
		free(map->matrix[i]);
	free(map->matrix);
	free(map);
}

void	free_matrix(double ***matrix, const int dim)
{
	int	i;

	i = -1;
	while (++i < dim)
		free((*matrix)[i]);
	free(*matrix);
}

void	ft_error(const char *msg)
{
	perror(msg);
	exit(-1);
}

void	my_mlx_pixel_put(t_data *data, double x, double y, unsigned int color)
{
	char	*dst;
	int		val;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	val = (int) round(y) * data->line_length +  (int) round(x) * (data->bits_per_pixel / 8);
	dst = data->addr + val;
	*(unsigned int *) dst = color;
}
