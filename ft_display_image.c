/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:59:32 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/29 23:11:41 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_rotation(t_data *data);
static t_3d	scale_transform(t_3d point3d, t_data *data);
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

	p1 = scale_transform(data->map->matrix[i][j], data);
	if (j != map->width - 1)
	{
		p2 = scale_transform(data->map->matrix[i][j + 1], data);
		draw_line(p1, p2, data);
	}
	if (i != map->height - 1)
	{
		p2 = scale_transform(data->map->matrix[i + 1][j], data);
		draw_line(p1, p2, data);
	}
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

void	display_image(t_map *map, t_data *data)
{
	int		i;
	int		j;


	ft_bzero(data->addr, 1 + WIDTH * HEIGHT * sizeof(int));
	if (data->map->rotation.x || data->map->rotation.y || data->map->rotation.z)
	{
		apply_rotation(data);
		printf("x: %f, %f \n" ,data->map->matrix[0][0].x, data->map->matrix[map->height - 1][0].x );
		printf("y: %f, %f \n" ,data->map->matrix[0][0].y, data->map->matrix[map->height - 1][0].y );
		printf("z: %f, %f \n" ,data->map->matrix[0][0].z, data->map->matrix[map->height - 1][0].z );
		printf("-----------------=\n");
		printf("x: %f, %f \n" ,data->map->matrix[0][map->width - 1].x, data->map->matrix[map->height - 1][map->width - 1].x );
		printf("y: %f, %f \n" ,data->map->matrix[0][map->width - 1].y, data->map->matrix[map->height - 1][map->width - 1].y );
		printf("z: %f, %f \n" ,data->map->matrix[0][map->width - 1].z, data->map->matrix[map->height - 1][map->width - 1].z );
	}

	if (data->map->matrix[0][0].x  - data->map->matrix[0][0].y <= data->map->matrix[0][0].y + data->map->matrix[0][0].z)
	{
		j = -1;
		while (++j < map->width)
		{
			i = -1;
			while (++i < map->height)
				ft_connect(i, j, data->map, data);
		}
	}
	else
	{
		j = map->width;
		while (--j >= 0)
		{
			i = map->height;
			while (--i >= 0)
				ft_connect(i, j, data->map, data);
		}
	}
	data->map->rotation.x = 0;
	data->map->rotation.y = 0;
	data->map->rotation.z = 0;
	mlx_put_image_to_window(data->init, data->display, data->img, 0, 0);
}
