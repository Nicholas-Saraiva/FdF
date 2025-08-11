/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:45:43 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/11 22:05:20 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_translation_events(int keycode, t_data *data)
{
	if (keycode == 65307)
		free_data(data);
	if (keycode == KEY_LEFT)
		data->map->offset_x += -20;
	if (keycode == KEY_UP)
		data->map->offset_y += -20;
	if (keycode == KEY_RIGHT)
		data->map->offset_x += 20;
	if (keycode == KEY_DOWN)
		data->map->offset_y += 20;
}

static void	ft_rotation_events(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->map->rotation.x += -0.01;
	if (keycode == KEY_S)
		data->map->rotation.x += +0.01;
	if (keycode == KEY_A)
		data->map->rotation.y += +0.01;
	if (keycode == KEY_D)
		data->map->rotation.y += -0.01;
	if (keycode == KEY_Q)
		data->map->rotation.z += +0.01;
	if (keycode == KEY_E)
		data->map->rotation.z += -0.01;
}

int	key_up(int keycode, t_data *data)
{
	ft_translation_events(keycode, data);
	ft_rotation_events(keycode, data);
	if (keycode == 65289)
	{
		if (data->map->projection == ft_isometric)
		{
			data->map->projection = ft_plane;
			data->map->offset_x = (float)(WIDTH * 1 / 2 - data
					->map->width / 2);
			data->map->offset_y = (float)(HEIGHT * 1 / 2 - data
					->map->height / 2);
		}
		else if (data->map->projection == ft_plane)
		{
			data->map->projection = ft_isometric;
			data->map->offset_x = (float)(WIDTH * 1 / 2);
			data->map->offset_y = (float)(HEIGHT * 1 / 2 - (
						(data->map->max_y + data->map->min_y) / 2));
		}
		free_matrix_3d(data->map->matrix_cpy, data->map);
		data->map->matrix_cpy = ft_matrix_cpy(data->map, data->map->matrix);
	}
	return (0);
}
