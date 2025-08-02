/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:59:32 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/31 18:15:16 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_rotation(t_data *data);
t_3d	scale_transform(t_3d, t_map *);
static t_3d ft_find_rotation(t_data *data, t_3d point3d);

static t_3d	ft_apply_rotation(t_data *data, t_3d point3d, double angle, 
		t_3d (*rotate)(t_3d, double))
{
	t_3d	translated;

	translated = rotate(subtrate_3d_points(point3d, 
				data->map->center), angle);
	translated = sum_3d_points(translated, data->map->center);
	translated.color = point3d.color;
	return (translated);
}

static t_3d ft_find_rotation(t_data *data, t_3d point3d)
{
	if (data->map->rotation.x)
		return (ft_apply_rotation(data, point3d, data->map->rotation.x, rotate_x));
	if (data->map->rotation.y)
		return (ft_apply_rotation(data, point3d, data->map->rotation.y, rotate_y));
	if (data->map->rotation.z)
		return (ft_apply_rotation(data, point3d, data->map->rotation.z, rotate_z));
	return (point3d);
}

t_3d	scale_transform(t_3d point3d, t_map *map)
{
	t_3d	result;

	result.x = (point3d.x * map->sx) + map->offset_x;
	result.y = (point3d.y * map->sy) + map->offset_y;
	result.z = point3d.z;
	result.color = point3d.color;
	return (result);
}

void	apply_rotation(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++j < data->map->width)
	{
		i = -1;
		while (++i < data->map->height)
			data->map->matrix[i][j] = ft_find_rotation(data, data->map->matrix[i][j]);
	}
}

static double	get_depth(t_3d p1, t_3d p2)
{
	return ((p1.z + p2.z) / 2.0f);
}

void update_line_data(t_data *data)
{
	int i;
	t_3d p1, p2;

	i = -1;
	while (++i < data->map->total_lines)
	{
		p1 = data->map->matrix[data->map->line[i].i1][data->map->line[i].j1];
		p2 = data->map->matrix[data->map->line[i].i2][data->map->line[i].j2];

		data->map->line[i].p1 = p1;
		data->map->line[i].p2 = p2;
		data->map->line[i].depth = get_depth(p1, p2);
	}
}

void	display_image(t_map *map, t_data *data)
{
	int		i;

	i = -1;
	ft_bzero(data->addr, 1 + WIDTH * HEIGHT * sizeof(int));
	if (map->rotation.x || map->rotation.y || map->rotation.z)
	{
		apply_rotation(data);
		update_line_data(data);
		qsort(data->map->line, map->total_lines, sizeof(t_line), compare_lines);
		map->rotation.x = 0;
		map->rotation.y = 0;
		map->rotation.z = 0;
	}
	i = -1;
	while (++i < data->map->total_lines)
		draw_line(scale_transform(data->map->line[i].p1, data->map), scale_transform(data->map->line[i].p2, data->map), data);
	mlx_put_image_to_window(data->init, data->display, data->img, 0, 0);
}