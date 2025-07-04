/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:19:00 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/04 18:40:25 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
#include <stdio.h>

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
		mlx_destroy_window(data->init, data->display);
		mlx_destroy_display(data->init);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_matrix	*map;

	map = malloc(sizeof(t_matrix));
	map -> width = 0;
	map -> height = 0;
	map -> matrix = 0;
	if (!fill_map(argv[argc - 1], map))
		return (0);
	data.init = mlx_init();
	if (!data.init)
		return (1);
	data.display = mlx_new_window(data.init, 900, 600, "FdF");
	data.img = mlx_new_image(data.init, 900, 600);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	
	my_mlx_pixel_put(&data, 5, 5, 0x00FF0000);
	my_mlx_pixel_put(&data, 5, 10, 0x00FF0000);
	my_mlx_pixel_put(&data, 5, 15, 0x00FF0000);
	my_mlx_pixel_put(&data, 5, 20, 0x00FF0000);

	my_mlx_pixel_put(&data, 15, 5, 0x00FF0000);
	my_mlx_pixel_put(&data, 15, 10, 0x00FF0000);
	my_mlx_pixel_put(&data, 15, 15, 0x00FF0000);
	my_mlx_pixel_put(&data, 15, 20, 0x00FF0000);

	mlx_put_image_to_window(data.init, data.display, data.img, 0, 0);
	mlx_hook(data.display, 2, 1L<<0, my_close, &data);
	mlx_loop(data.init);


	mlx_destroy_window(data.init, data.display);
	mlx_destroy_display(data.init);
	free(data.init);
	return (0);
}
