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

static int	map_init(t_map **map, char *argv[])
{
	*map = malloc(sizeof(t_map));
	if (!*map)
		return (0);
	(*map)->width = 0;
	(*map)->height = 0;
	(*map)->matrix = 0;
	(*map)->max_x = DBL_MIN;
	(*map)->min_x = DBL_MAX;
	(*map)->min_y = DBL_MAX;
	(*map)->max_y = DBL_MIN;
	(*map)->rotation.x = 0;
	(*map)->rotation.y = 0;
	(*map)->rotation.z = 0;
	(*map)->projection = ft_isometric;
	(*map)->zoom = 1;
	if (!fill_map(argv[1], *map))
		return (0);
	(*map)->center = (*map)->matrix[(*map)->height / 2][(*map)->width / 2];
	return (1);
}

static int	screen_init(t_data *data, t_map *map)
{
	data->init = mlx_init();
	if (!data->init)
		return (0);
	data->display = mlx_new_window(data->init, WIDTH, HEIGHT, "FdF");
	if (!data->display)
		return (mlx_destroy_display(data->init), 0);
	data->img = mlx_new_image(data->init, WIDTH, HEIGHT);
	if (!data->img)
	{
        mlx_destroy_window(data->init, data->display);
		mlx_destroy_display(data->init);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->map = map;
	data->map->sx = (double) ((WIDTH *  4 / 6) / (map->max_x - map->min_x));
	data->map->sy = (double) ((HEIGHT * 4 / 6) / (map->max_y - map->min_y));
	data->map->offset_x = (double) (WIDTH * 1 / 6 - map->min_x * data->map->sx); 
	data->map->offset_y = (double) (HEIGHT * 1 / 6 - map->min_y * data->map->sy);
	data->zbuffer = malloc(WIDTH * HEIGHT * sizeof(double));
	if (!data->zbuffer)
		ft_error("Z-buffer allocation failed");
	return (1);
}

int	render(t_data *data)
{
	display_image(data->map, data);
	mlx_loop(data->init);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_map	*map;

	if (!map_init(&map, argv) || argc != 2)
		return (0);
	if (!screen_init(&data, map))
		return (0);
	mlx_loop_hook(data.init, render, &data);
	ft_hooks(&data);
	render(&data);
	free_data(&data);
	return (0);
}
