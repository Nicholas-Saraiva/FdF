/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:59:32 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/25 13:58:24 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_3d	ft_apply_rotation(t_data data, t_3d point3d, double angle, 
		t_3d (*rotate)(t_3d, double))
{
	t_3d	translated;

	translated = rotate(subtrate_3d_points(point3d, 
				data.map->center), angle);
	translated = sum_3d_points(translated, data.map->center);
	translated.color = point3d.color;
	return (translated);
}

static t_3d ft_find_rotation(t_map *map, t_data data, t_3d point3d)
{
	if (map->rotation.x)
	{
		if (map->rotation.x == 1)
			return (ft_apply_rotation(data, point3d, (double) +2.0 * M_PI / 180.0, rotate_x));
		else
			return (ft_apply_rotation(data, point3d, (double) -2.0 * M_PI / 180.0, rotate_x));
	}
	if (map->rotation.y)
	{
		if (map->rotation.y == 1)
			return (ft_apply_rotation(data, point3d, (double) +2.0 * M_PI / 180.0, rotate_y));
		else
			return (ft_apply_rotation(data, point3d, (double) -2.0 * M_PI / 180.0, rotate_y));
	}
	if (map->rotation.z)
	{
		if (map->rotation.z == 1)
			return (ft_apply_rotation(data, point3d, (double) +2.0 * M_PI / 180.0, rotate_z));
		else 
			return (ft_apply_rotation(data, point3d, (double) -2.0 * M_PI / 180.0, rotate_z));
	}
	return (point3d);
}

static t_2d	scale_transform(t_3d point3d, t_data data)
{
	t_2d	result;

	result.x = round(point3d.x * data.sx + data.offset_x);
	result.y = round(point3d.y * data.sy + data.offset_y);
	result.color = point3d.color;
	return (result);
}

static void	ft_connect(int i, int j, t_map *map, t_data data)
{
	t_2d	p1;
	t_2d	p2;

	p1 =  scale_transform(map->matrix[i][j], data);
	if (j != map->width - 1)
	{
		p2 = scale_transform(map->matrix[i][j + 1], data);
		draw_line(p1, p2, &data);
	}
	if (i != map->height - 1)
	{
		map->matrix[i + 1][j] = ft_find_rotation(data.map, data, map->matrix[i + 1][j]);
		p2 = scale_transform(map->matrix[i + 1][j], data);
		draw_line(p1, p2, &data);
	}
}

void	display_image(t_map *map, t_data data)
{
	int		i;
	int		j;

	j = -1;
	ft_bzero(data.addr, 1 + WIDTH * HEIGHT * sizeof(int));
	while (++j < map->width)
		map->matrix[0][j] = ft_find_rotation(data.map, data, map->matrix[0][j]);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			ft_connect(i, j, map, data);
		}
	}
	data.map->rotation.x = 0;
	data.map->rotation.y = 0;
	data.map->rotation.z = 0;
	mlx_put_image_to_window(data.init, data.display, data.img, 0, 0);
}
