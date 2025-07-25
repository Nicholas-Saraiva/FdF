/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:45:43 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/24 17:27:02 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_translation(t_data *data, double *direction, int move)
{
	*direction += move;
	display_image(data->map, *data);
}

static void ft_translation_events(int keycode, t_data *data)
{
	if (keycode == 65307)
		mlx_loop_end(data->init);
	if (keycode == KEY_A || keycode == KEY_LEFT)
		ft_translation(data, &data->offset_x, -20);
	if (keycode == KEY_W || keycode == KEY_UP)
		ft_translation(data, &data->offset_y, -20);
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		ft_translation(data, &data->offset_x, 20);
	if (keycode == KEY_S || keycode == KEY_DOWN)
		ft_translation(data, &data->offset_y, 20);
}

static void	ft_rotation_events(int keycode, t_data *data)
{
	if (keycode == 113)
		data->map->rotation.z = -1;
	if (keycode == 101)
		data->map->rotation.z = 1;
	if (keycode == 49)
		data->map->rotation.y = 1;
	if (keycode == 50)
		data->map->rotation.y = -1;
	if (keycode == 51)
		data->map->rotation.x = 1;
	if (keycode == 52)
		data->map->rotation.x = -1;
}

int	key_hook(int keycode, t_data *data)
{
	static int	type;

	if (!type)
		type = 0;
	ft_translation_events(keycode, data);
	ft_rotation_events(keycode, data);
	printf("%d \n", keycode);
	return (0);
}
