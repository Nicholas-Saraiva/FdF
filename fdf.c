/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:19:00 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/09 15:07:20 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	const int	val = y * data->line_length + x * (data->bits_per_pixel / 8);
	if (val < 0 || x > WIDTH || y > HEIGHT)
		return ;
	dst = data->addr + val;
	*(unsigned int*)dst = color;
}

int	my_close(int keycode, t_data *data)
{
	if (keycode == 65307)
	{

        mlx_destroy_image(data->init, data->img);
        mlx_destroy_window(data->init, data->display);
		mlx_destroy_display(data->init);	
		exit(0);
	}
	return (0);
}

static int	map_init(t_map **map, char *argv[])
{
	*map = malloc(sizeof(t_map));
	(*map)->width = 0;
	(*map)->height = 0;
	(*map)->matrix = 0;
	(*map)->max_x = DBL_MAX;
	(*map)->min_x = DBL_MIN;
	(*map)->min_y = DBL_MIN;
	(*map)->max_y = DBL_MAX;
	if (!fill_map(argv[1], *map))
		return (0);
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
	data->sx = (double) (WIDTH / 3 / map->width);
	data->sy = (double) (HEIGHT / 3 / map->height);
	data->offset_x = (double) (WIDTH / 6 - map->min_x * data->sx);
	data->offset_y = (double) (HEIGHT / 6 - map->min_y * data->sy);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_map	*map;
    int		j;
    int		i;

	if (!map_init(&map, argv) || argc != 2)
		return (0);
	data.init = mlx_init();
	if (!screen_init(&data, map))
		return (0);
    i = 0;
	j = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
		
            int pixel_x = (int) (map->matrix[i][j].x * data.sx + data.offset_x);
            int pixel_y = (int) (map->matrix[i][j].y * data.sy + data.offset_y);

            my_mlx_pixel_put(&data, pixel_x, pixel_y, 0x000FFFF); 
            j++;
		}
		i++;
	}
	mlx_put_image_to_window(data.init, data.display, data.img, 0, 0);
	mlx_hook(data.display, 2, 1L<<0, my_close, &data);
	mlx_loop(data.init);
	return (0);
}
