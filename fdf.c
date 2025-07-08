/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:19:00 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/06 22:14:21 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
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

int	main(int argc, char *argv[])
{
	t_data		data;
	t_matrix	*map;

	map = malloc(sizeof(t_matrix));
	map->width = 0;
	map->height = 0;
	map->matrix = 0;
	map->min_x = DBL_MIN;
	map->min_y = DBL_MIN;
	if (!fill_map(argv[argc - 1], map))
		return (0);
	data.init = mlx_init();
	if (!data.init)
		return (1);
	data.display = mlx_new_window(data.init, 900, 600, "FdF");
	data.img = mlx_new_image(data.init, 900, 600);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	
    t_2d p_raw;
    int j = 0;
    int i = 0;
	int offset_x = -map->min_x * 20 + 50;
    int offset_y = -map->min_y * 20 + 50;
	i = 0;
	j = 0;
	while (j < map->height)
	{
		i = 0;
		while (i < map->width)
		{
			p_raw = ft_transformation(i, j, map->matrix[j][i]);
		
		            // Apply scale and offset
            int pixel_x = (int)(p_raw.x * 10 + offset_x);
            int pixel_y = (int)(p_raw.y * 10 + offset_y);

            // Draw the point
            my_mlx_pixel_put(&data, pixel_x, pixel_y, 0x000FFFF); // Use your desired color
            i++;
		}
		j++;
	}
	
	mlx_put_image_to_window(data.init, data.display, data.img, 0, 0);
	mlx_hook(data.display, 2, 1L<<0, my_close, &data);
	mlx_loop(data.init);
	return (0);
}
