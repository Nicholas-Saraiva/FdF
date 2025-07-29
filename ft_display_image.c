/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:59:32 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/29 11:25:52 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_rotation(t_data *data);
static t_3d	scale_transform(t_3d point3d, t_data *data);
static t_3d ft_find_rotation(t_data *data, t_3d point3d);
static t_3d	ft_apply_rotation(t_data *data, t_3d point3d, double angle, 
		t_3d (*rotate)(t_3d, double));

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
	t_3d	result;

	result = point3d;
	if (data->map->rotation.x)
		result = ft_apply_rotation(data, result, data->map->rotation.x, rotate_x);
	if (data->map->rotation.y)
		result = ft_apply_rotation(data, result, data->map->rotation.y, rotate_y);
	if (data->map->rotation.z)
		result = ft_apply_rotation(data, result, data->map->rotation.z, rotate_z);
	return (result);
}

static t_3d	scale_transform(t_3d point3d, t_data *data)
{
	t_3d	result;

	result.x = (point3d.x * data->sx) + data->offset_x;
	result.y = (point3d.y * data->sy) + data->offset_y;
	result.z = point3d.z;
	result.color = point3d.color;
	return (result);
}

static void	ft_connect(int i, int j, t_map *map, t_data *data)
{
	t_3d	p1;
	t_3d	p2;

	p1 = ft_find_rotation(data, data->map->matrix[i][j]);
	p1 = data->map->projection(p1);
	p1 = scale_transform(p1, data);
	if (j != map->width - 1)
	{
		p2 = ft_find_rotation(data, data->map->matrix[i][j + 1]);
		p2 = data->map->projection(p2);
		p2 = scale_transform(p2, data);
		draw_line(p1, p2, data);
	}
	if (i != map->height - 1)
	{
		p2 = ft_find_rotation(data, data->map->matrix[i + 1][j]);
		p2 = data->map->projection(p2);
		p2 = scale_transform(p2, data);
		draw_line(p1, p2, data);
	}
}

void	display_image(t_map *map, t_data *data)
{
	int		i;
	int		j;

	j = -1;
	ft_bzero(data->addr, 1 + WIDTH * HEIGHT * sizeof(int));
	while (++j < map->width)
	{
		i = -1;
		while (++i < map->height)
			ft_connect(i, j, data->map, data);
	}
	mlx_put_image_to_window(data->init, data->display, data->img, 0, 0);
}
