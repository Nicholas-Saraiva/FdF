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
	free_matrix_3d(map->matrix, map);
	free_matrix_3d(map->matrix_cpy, map);
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

void	free_matrix_3d(t_3d **matrix, t_map *map)
{
	int	i;

	i = -1;
	if (!matrix)
		return ;
	while (++i < map->height)
	{
		if (matrix[i])
			free(matrix[i]);
	}
	free(matrix);
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

t_3d	**ft_matrix_cpy(t_map *map, t_3d **matrix)
{
	int		i;
	int		j;
	t_3d	**new_matrix;

	i = -1;
	new_matrix = ft_calloc((map->height), sizeof(t_3d *));
	if (!new_matrix)
		return ((t_3d **){0});
	while (++i < map->height)
	{
		new_matrix[i] = malloc(sizeof(t_3d) * map->width);
		if (!new_matrix[i])
			return (free_matrix_3d(new_matrix, map), (t_3d **){0});
	}
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			new_matrix[i][j] = map->projection(matrix[i][j]);
			find_limits(map, new_matrix[i][j]);
		}
	}
	return (new_matrix);
}
