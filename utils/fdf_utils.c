/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:31:17 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/02 19:07:31 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	free_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->height)
	{
		if (map->matrix[i])
			free(map->matrix[i]);
	}
	free(map->matrix);
	free(map);
	return (0);
}

int	free_data(t_data *data)
{
	if (*data->map->matrix)
		free_map(data->map);
	if (data->img)
		mlx_destroy_image(data->init, data->img);
	if (data->display)
		mlx_destroy_window(data->init, data->display);
	if (data->init)
		mlx_destroy_display(data->init);
	if (data->zbuffer)
		free(data->zbuffer);
	free(data->init);
	exit (0);
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

void	my_mlx_pixel_put(t_data *data, t_3d point)
{
	int		index;
	char	*dst;

	if ((int) point.x > WIDTH - 1 || (int) point.y > HEIGHT - 1
		|| (int) point.x < 0 || (int) point.y < 0)
		return ;
	index = point.y * WIDTH + point.x;
	if (point.z > data->zbuffer[index])
	{
		data->zbuffer[index] = point.z;
		dst = data->addr + ((int) point.y * data->line_length
				+ (int) point.x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = point.color;
	}
}
