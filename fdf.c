/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:19:00 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/18 16:29:36 by nsaraiva         ###   ########.fr       */
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
	return (1);
}

void displayImage(t_map *map, t_data data)
{
	int	i = -1;
	int j = -1;
	t_2d p1;
	t_2d p2;

	while (++i < map->height)
	{
		j = 0;
		while (++j < map->width)
		{
			p1 = ft_transformation(map->matrix[i][j]);
			p1.x = p1.x * data.sx + data.offset_x;
			p1.y = p1.y * data.sy + data.offset_y;
			if (j != map->width - 1)
			{
				p2 = ft_transformation(map->matrix[i][j + 1]);
				p2.x = p2.x * data.sx + data.offset_x;
				p2.y = p2.y * data.sy + data.offset_y;
				draw_line(p1, p2, &data);
			}
			if (i != map->height - 1)
			{
				p2 = ft_transformation(map->matrix[i + 1][j]);
				p2.x = p2.x * data.sx + data.offset_x;
				p2.y = p2.y * data.sy + data.offset_y;
				draw_line(p1, p2, &data);
			}
		}
	}
	mlx_put_image_to_window(data.init, data.display, data.img, 0, 0);
}

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	if (keycode == 4 || x == 1 || y == 2)
	{
		
		data->sx *= 1.1;
		data->sy *= 1.1;
		ft_bzero(data->addr, 1 + WIDTH * HEIGHT * sizeof(int));
		displayImage(data->map, *data);
	}
	if (keycode == 5 || x == 1 || y == 2)
	{
		data->sx *= 0.9;
		data->sy *= 0.9;
		ft_bzero(data->addr, 1 + WIDTH * HEIGHT * sizeof(int));
		displayImage(data->map, *data);
	}
		printf("Hello from key_hook!{%d} - \n", keycode);
	return (0);
}

int	my_close(int keycode, t_data *data)
{
	if (keycode == 65307)
		mlx_loop_end(data->init);
	if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		data->offset_x -= 20;
		ft_bzero(data->addr, WIDTH * HEIGHT * sizeof(int));
		displayImage(data->map, *data);
	}
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		data->offset_y -= 20;
		ft_bzero(data->addr, WIDTH * HEIGHT * sizeof(int));
		displayImage(data->map, *data);
	}
	if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		data->offset_x += 20;
		ft_bzero(data->addr, WIDTH * HEIGHT * sizeof(int));
		displayImage(data->map, *data);
	}
	if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		data->offset_y += 20;
		ft_bzero(data->addr, WIDTH * HEIGHT * sizeof(int));
		displayImage(data->map, *data);
	}
	if (keycode == 113)
	{
		ft_rotate(data, rotate_z, -2.0 * M_PI / 180);
		ft_bzero(data->addr, WIDTH * HEIGHT * sizeof(int));
		displayImage(data->map, *data);
	}
	if (keycode == 101)
	{
		ft_rotate(data, rotate_z, +2.0 * M_PI / 180);
		ft_bzero(data->addr, WIDTH * HEIGHT * sizeof(int));
		displayImage(data->map, *data);
	}
	printf("%d \n", keycode);
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


	displayImage(map, data);
	mlx_hook(data.display, 2, 1L<<0, my_close, &data);
	mlx_mouse_hook(data.display, mouse_hook, &data);
	mlx_loop(data.init);
	mlx_destroy_image(data.init, data.img);
	mlx_destroy_window(data.init, data.display);
	free_map(map);
	mlx_destroy_display(data.init);
	free(data.init);
	return (0);
}
