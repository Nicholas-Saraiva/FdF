/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:45:43 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/05 18:22:29 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_translation_events(int keycode, t_data *data)
{
	if (keycode == 65307)
		free_data(data);
	if (keycode == KEY_A || keycode == KEY_LEFT)
		data->map->offset_x += -20;
	if (keycode == KEY_W || keycode == KEY_UP)
		data->map->offset_y += -20;
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		data->map->offset_x += 20;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		data->map->offset_y += 20;
}

static void	ft_rotation_events(int keycode, t_data *data)
{
	if (keycode == 113)
		data->map->rotation.z += -0.01;
	if (keycode == 101)
		data->map->rotation.z += +0.01;
	if (keycode == 49)
		data->map->rotation.y += +0.01;
	if (keycode == 50)
		data->map->rotation.y += -0.01;
	if (keycode == 51)
		data->map->rotation.x += +0.01;
	if (keycode == 52)
		data->map->rotation.x += -0.01;
	printf("\n%f\n", data->map->rotation.y);
}

int	key_up(int keycode, t_data *data)
{
	static int	type;

	if (!type)
		type = 0;
	ft_translation_events(keycode, data);
	ft_rotation_events(keycode, data);
	printf("%d \n", keycode);
	return (0);
}
