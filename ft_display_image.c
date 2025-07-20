/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:59:32 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/20 17:40:43 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_2d	scale_transform(t_3d point2d, t_data data)
{
	t_2d	result;

	result = ft_transformation(point2d);
	result.x = result.x * data.sx + data.offset_x;
	result.y = result.y * data.sy + data.offset_y;
	result.color = point2d.color;
	return (result);
}

static void	ft_connect(int i, int j, t_map *map, t_data data)
{
	t_2d	p1;
	t_2d	p2;

	p1 = scale_transform(map->matrix[i][j], data);
	if (j != map->width - 1)
	{
		p2 = scale_transform(map->matrix[i][j + 1], data);
		draw_line(p1, p2, &data);
	}
	if (i != map->height - 1)
	{
		p2 = scale_transform(map->matrix[i + 1][j], data);
		draw_line(p1, p2, &data);
	}
}

void	display_image(t_map *map, t_data data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
			ft_connect(i, j, map, data);
	}
	mlx_put_image_to_window(data.init, data.display, data.img, 0, 0);
}
