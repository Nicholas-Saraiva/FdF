/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:59:32 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/04 18:29:24 by nsaraiva         ###   ########.fr       */
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
	if (data->map->rotation.z)
		return (ft_apply_rotation(data, point3d, data->map->rotation.z, rotate_z));
	if (data->map->rotation.x)
		return (ft_apply_rotation(data, point3d, data->map->rotation.x, rotate_x));
	if (data->map->rotation.y)
		return (ft_apply_rotation(data, point3d, data->map->rotation.y, rotate_y));
	return (point3d);
}

t_3d	scale_transform(t_3d point3d, t_map *map)
{
	t_3d	result;
	t_3d	translated;

	translated = subtrate_3d_points(point3d, 
				map->center); 
	translated.x = translated.x * map->sx * map->zoom;
	translated.y = translated.y * map->sy * map->zoom;
	translated = sum_3d_points(translated, map->center);
	result.x = (translated.x + map->offset_x);
	result.y = (translated.y + map->offset_y  + HEIGHT  * 0.3);
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

static void fill_lines(t_map *map, t_data *data)
{
    int     i;
    int     j;
    t_3d	p;
	t_3d	p2;

    i = -1;
    while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			p = scale_transform(map->matrix[i][j], map);
			if (j < map->width - 1)
			{
				p2 = scale_transform(map->matrix[i][j + 1], map);
				draw_line(p, p2, data);
			}
			if (i < map->height - 1)
			{
				p2 = scale_transform(map->matrix[i + 1][j], map);
				draw_line(p, p2, data);
			}
		}
	}
}

void	display_image(t_map *map, t_data *data)
{
	int	i;

	i = -1;
	while (++i < WIDTH * HEIGHT)
		data->zbuffer[i] = -DBL_MAX;
	ft_bzero(data->addr, 1 + WIDTH * HEIGHT * sizeof(int));
	if (map->rotation.x || map->rotation.y || map->rotation.z)
		apply_rotation(data);
	fill_lines(map, data);
	mlx_put_image_to_window(data->init, data->display, data->img, 0, 0);
}
