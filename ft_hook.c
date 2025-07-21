/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:45:43 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/07/21 18:29:00 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_translation(t_data *data, double *direction, int move)
{
	*direction += move;
	ft_bzero(data->addr, WIDTH * HEIGHT * sizeof(int));
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
		ft_rotate(data, rotate_z, -2.0 * M_PI / 180);
	if (keycode == 101)
		ft_rotate(data, rotate_z, +2.0 * M_PI / 180);
	if (keycode == 49)
		ft_rotate(data, rotate_y, +2.0 * M_PI / 180);
	if (keycode == 50)
		ft_rotate(data, rotate_y, -2.0 * M_PI / 180);
	if (keycode == 51)
		ft_rotate(data, rotate_x, +2.0 * M_PI / 180);
	if (keycode == 52)
		ft_rotate(data, rotate_x, -2.0 * M_PI / 180);
}

int	key_hook(int keycode, t_data *data)
{
	static int	type;

	if (!type)
		type = 0;
	ft_translation_events(keycode, data);
	ft_rotation_events(keycode, data);
	if (keycode == 114)
	{
		if (type == 0)
		{
			ft_rotate(data, rotate_x, -atan(sqrt(2)));
			ft_rotate(data, rotate_z, -45 * M_PI / 180);
			ft_rotate(data, rotate_x, 45 * M_PI / 180);
			ft_rotate(data, rotate_y, -45 * M_PI / 180);
			type++;
		}
		else if (type == 1) {

			ft_rotate(data, rotate_y, 45 * M_PI / 180);
			ft_rotate(data, rotate_x, -45 * M_PI / 180);
			type++;
		}
		else
		{
			ft_rotate(data, rotate_z, 45 * M_PI / 180);
			ft_rotate(data, rotate_x, atan(sqrt(2)));
			type = 0;
		}
	}
	printf("%d \n", keycode);
	return (0);
}
