/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:19:00 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/09 19:28:47 by nsaraiva         ###   ########.fr       */
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


void	drawLineH(t_2d p1, t_2d diff, int dir, t_data *data)
{
	double	y;
	double	p;
	int		i;

	i = 0;
	y = p1.y;
	p = 2*diff.y - diff.x;
	if (diff.x != 0)
	{
		while (i < diff.x)
		{
			my_mlx_pixel_put(data, p1.x + i, y, 0x000FFFFF);
		if (p >= 0)
			{
				y += dir;
				p -= 2*diff.x;
			}
			p += 2*diff.y;
			i++;
		}
	}
}

void	drawLineV(t_2d p1, t_2d diff, int dir, t_data *data)
{
	double	x;
	double	p;
	int		i;

	i = 0;
	x = p1.x;
	p = 2*diff.x - diff.y;
	if (diff.y != 0)
	{
		while (i < diff.y)
		{
			my_mlx_pixel_put(data, x, p1.y + i, 0x000FFFF);
			if (p >= 0)
			{
				x += dir;
				p -= 2*diff.y;
			}
			p += 2*diff.x;
			i++;
		}
	}
}

void	drawLine(t_2d p1, t_2d p2, t_data *data)
{
	int		dir;
	int		cond;
	t_2d	diff;
	t_2d	p3;

	p3 = p1;
	cond = fabs(p2.x - p1.x) > fabs(p2.y - p1.y);
	if ((p1.x > p2.x && cond)|| 
			(p1.y > p2.y && !cond))
	{
		p1 = p2;
		p2 = p3;
	}
	diff.x = p2.x - p1.x;
	diff.y = p2.y - p1.y;
	if ((diff.y < 0 && cond) || (diff.x < 0 && !cond))
		dir = -1;
	else
		dir = 1;
	p1.x = p1.x * data->sx + data->offset_x;
	p1.y = p1.y * data->sy + data->offset_y;
	if (fabs(p2.x - p1.x) > fabs(p2.y - p1.y))
		drawLineH(p1, diff, dir, data);
	else
		drawLineV(p1, diff, dir, data);
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
			if (j != map->width - 1)
				drawLine(map->matrix[i][j + 1], map->matrix[i][j], &data);
			if (i != map ->height - 1)
				drawLine(map->matrix[i + 1][j], map->matrix[i][j], &data);
            j++;
		}
		i++;
	}
	mlx_put_image_to_window(data.init, data.display, data.img, 0, 0);
	mlx_hook(data.display, 2, 1L<<0, my_close, &data);
	mlx_loop(data.init);
	return (0);
}
