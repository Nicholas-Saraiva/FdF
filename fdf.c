/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:19:00 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/22 16:01:21 by nsaraiva         ###   ########.fr       */
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
	(*map)->projection = ft_isometric;
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
	data->sx = (double) ((WIDTH *  4 / 6) / (map->max_x - map->min_x));
	data->sy = (double) ((HEIGHT * 4 / 6) / (map->max_y - map->min_y));
	data->offset_x = (double) (WIDTH * 1 / 6 - map->min_x * data->sx); 
	data->offset_y = (double) (HEIGHT * 1 / 6 - map->min_y * data->sy);
	data->map = map;
	data->projection = map->projection;
	return (1);
}

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	if (keycode == 4 || x == 1 || y == 2)
	{
		
		data->sx *= 1.1;
		data->sy *= 1.1;
		ft_bzero(data->addr, 1 + WIDTH * HEIGHT * sizeof(int));
		display_image(data->map, *data);
	}
	if (keycode == 5 || x == 1 || y == 2)
	{
		data->sx *= 0.9;
		data->sy *= 0.9;
		ft_bzero(data->addr, 1 + WIDTH * HEIGHT * sizeof(int));
		display_image(data->map, *data);
	}
		printf("Hello from key_hook!{%d} - \n", keycode);
	return (0);
}

int	render(t_data *data)
{
	display_image(data->map, *data);
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
	mlx_hook(data.display, 2, 1L<<0, key_hook, &data);
	mlx_mouse_hook(data.display, mouse_hook, &data);
	render(&data);
	mlx_destroy_image(data.init, data.img);
	mlx_destroy_window(data.init, data.display);
	free_map(map);
	mlx_destroy_display(data.init);
	free(data.init);
	return (0);
}
