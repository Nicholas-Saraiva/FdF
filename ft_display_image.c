/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:59:32 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/31 02:34:26 by nsaraiva         ###   ########.fr       */
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
	return (rotate(point3d, angle));
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

/*static void	ft_connect(int i, int j, t_map *map, t_data *data)
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
}*/

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
typedef struct s_line {
	t_3d p1;
	t_3d p2;
	float depth; // média dos z
} t_line;

static float	get_depth(t_3d p1, t_3d p2)
{
	return ((p1.z + p2.z) / 2.0f);
}

static int	compare_lines(const void *a, const void *b)
{
	float depth_a = ((t_line *)a)->depth;
	float depth_b = ((t_line *)b)->depth;

	if (depth_a < depth_b)
		return (-1);
	if (depth_a > depth_b)
		return (1);
	return (0);
}


void	display_image(t_map *map, t_data *data)
{
	t_line	*lines;
	int		i, j, count = 0;
	int		total = (map->width - 1) * map->height + (map->height - 1) * map->width;

	lines = malloc(sizeof(t_line) * total);
	if (!lines)
		return ;

	// Gerar as linhas
	for (i = 0; i < map->height; i++)
	{
		for (j = 0; j < map->width; j++)
		{
			t_3d p = scale_transform(map->matrix[i][j], data);

			if (j < map->width - 1)
			{
				t_3d p2 = scale_transform(map->matrix[i][j + 1], data);
				lines[count++] = (t_line){p, p2, get_depth(p, p2)};
			}
			if (i < map->height - 1)
			{
				t_3d p2 = scale_transform(map->matrix[i + 1][j], data);
				lines[count++] = (t_line){p, p2, get_depth(p, p2)};
			}
		}
	}

	// Ordenar pelas profundidades
	qsort(lines, count, sizeof(t_line), compare_lines);

	// Limpar imagem
	ft_bzero(data->addr, 1 + WIDTH * HEIGHT * sizeof(int));

	// Aplicar rotação se necessário
	if (map->rotation.x || map->rotation.y || map->rotation.z)
		apply_rotation(data);

	// Desenhar as linhas ordenadas
	for (int k = 0; k < count; k++)
		draw_line(lines[k].p1, lines[k].p2, data);

	free(lines);

	// Resetar rotação
	map->rotation.x = 0;
	map->rotation.y = 0;
	map->rotation.z = 0;

	// Mostrar na janela
	mlx_put_image_to_window(data->init, data->display, data->img, 0, 0);
}

