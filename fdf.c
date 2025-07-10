/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:19:00 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/10 17:38:14 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

# define COLOR 0x00FF00FF

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


void	drawLineH(t_2d p1, t_2d p2, t_data *data)
{
	int		dir;
	int		p;
	int		y;
	int		i;
	t_2d	diff;
	t_2d	p3;

	i = 0;
	p3 = p1;
	p = 0;
	y = 0;
	if (p1.x > p2.x)
	{
		p1 = p2;
		p2 = p3;
	}
	diff.x = p2.x - p1.x;
	diff.y = p2.y - p1.y;
	dir = 1;
	if (diff.y < 0)
		dir = -1;
	if (diff.x != 0)
	{
		y = p1.y;
		p = 2*diff.y - diff.x;
		while (i < diff.x)
		{
			my_mlx_pixel_put(data, p1.x + i, y, COLOR);
			if (p > 0)
			{
				y += dir;
				p -= 2*diff.x;
			}
			p += 2*diff.y;
			i++;
		}
	}
}

void	drawLineV(t_2d p1, t_2d p2, t_data *data)
{
	int		dir;
	int		p;
	int		x;
	int		i;
	t_2d	diff;
	t_2d	p3;

	p3 = p1;
	p = 0;
	x = 0;
	i = 0;
	if (p1.y > p2.y)
	{
		p1 = p2;
		p2 = p3;
	}
	diff.x = p2.x - p1.x;
	diff.y = p2.y - p1.y;
	dir = 1;
	if (diff.x < 0)
		dir = -1;
	if (diff.x != 0)
	{
		x = p1.x;
		p = 2*diff.x - diff.y;
		while (i < diff.y)
		{
			my_mlx_pixel_put(data, x, p1.y + i, COLOR);
			if (p > 0)
			{
				x += dir;
				p = p - 2*diff.y;
			}
			p = p + 2*diff.x;
			i++;
		}
	}
}

void	drawLine(t_2d p1, t_2d p2, t_data *data)
{
	if (fabs(p2.x - p1.x) > fabs(p2.y - p1.y))
		drawLineH(p1, p2, data);
	else
		drawLineV(p1, p2, data);
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

	if (!map_init(&map, argv) || argc != 2)
		return (0);
	data.init = mlx_init();
	if (!screen_init(&data, map))
		return (0);

	t_2d	p0;
	t_2d	p1;
	t_2d	p2;
	t_2d	p3;
	t_2d	p4;
	t_2d	p5;
	t_2d	p6;
	t_2d	p7;
	t_2d	p8;

	p0.x = WIDTH / 2;
	p0.y = HEIGHT / 2;
	p1.x = p0.x + 200;
	p1.y = p0.y + 50;

	drawLine(p0, p1, &data);
	p2.x = p0.x + 50;
	p2.y = p0.y + 200;

	drawLine(p0, p2, &data);
	p3.x = p0.x - 50;
	p3.y = p0.y + 200;

	drawLine(p0, p3, &data);
	p4.x = p0.x - 200;
	p4.y = p0.y + 50;

	drawLine(p0, p4, &data);
	p5.x = p0.x - 200;
	p5.y = p0.y - 50;

	drawLine(p0, p5, &data);
	p6.x = p0.x - 50;
	p6.y = p0.y - 200;

	drawLine(p0, p6, &data);
	p7.x = p0.x + 50;
	p7.y = p0.y - 200;
	
	drawLine(p0, p7, &data);
	p8.x = p0.x + 200;
	p8.y = p0.y - 50;

	drawLine(p0, p8, &data);
	mlx_put_image_to_window(data.init, data.display, data.img, 0, 0);
	mlx_hook(data.display, 2, 1L<<0, my_close, &data);
	mlx_loop(data.init);
	return (0);
}
