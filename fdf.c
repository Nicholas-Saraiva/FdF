/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:19:00 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/05 17:02:32 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	map_init(t_map *map, char *argv[]);
static int	screen_init(t_data *data, t_map *map);
static int	render(t_data *data);

int	main(int argc, char *argv[])
{
	t_data	data;
	t_map	map;

	if (argc != 2)
		return (0);
	if (!map_init(&map, argv) || argc != 2)
		return (free_map(&map), 0);
	if (!screen_init(&data, &map))
		return (free_data(&data), 0);
	mlx_loop_hook(data.init, render, &data);
	ft_hooks(&data);
	mlx_loop(data.init);
	free_data(&data);
	return (0);
}

static int	map_init(t_map *map, char *argv[])
{
	map->width = 0;
	map->height = 0;
	map->matrix = 0;
	map->matrix_cpy = 0;
	map->max_x = DBL_MIN;
	map->min_x = DBL_MAX;
	map->min_y = DBL_MAX;
	map->max_y = DBL_MIN;
	map->rotation.x = 0;
	map->rotation.y = 0;
	map->rotation.z = 0;
	map->projection = ft_isometric;
	map->zoom = 1;
	if (!fill_map(argv[1], map))
		return (0);
	map->center = (map->matrix[map->height / 2][map->width / 2]);
	map->matrix_cpy = ft_matrix_cpy(map, map->matrix);
	if (!map->matrix_cpy)
		return (0);
	return (1);
}

static int	screen_init(t_data *data, t_map *map)
{
	data->init = mlx_init();
	if (!data->init)
		ft_error_data("mlx_init failed", data);
	data->display = mlx_new_window(data->init, WIDTH, HEIGHT, "FdF");
	if (!data->display)
		ft_error_data("mlx display failed", data);
	data->img = mlx_new_image(data->init, WIDTH, HEIGHT);
	if (!data->img)
		ft_error_data("mlx new image failed", data);
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	data->map = map;
	data->map->sx = (float)((WIDTH * 2 / 3) / map->width);
	data->map->sy = (float)((HEIGHT * 2 / 3) / (map->max_y - map->min_y));
	data->map->offset_x = (float)(WIDTH * 1 / 2);
	data->map->offset_y = (float)(HEIGHT * 1 / 2 - ((map->max_y + map->min_y) / 2));
	data->zbuffer = malloc(WIDTH * HEIGHT * sizeof(float));
	if (!data->zbuffer)
		ft_error_data("Z-buffer allocation failed", data);
	return (1);
}

static int	render(t_data *data)
{
	display_image(data->map, data);
	return (0);
}
