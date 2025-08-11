/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:27:02 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/08 14:27:20 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_rotation_events(int keycode, t_data *data)
{
	if (keycode == KEY_W || keycode == KEY_S)
		data->map->rotation.x = 0;
	if (keycode == KEY_A || keycode == KEY_D)
		data->map->rotation.y = 0;
	if (keycode == 113 || keycode == 101)
		data->map->rotation.z = 0;
}

int	key_down(int keycode, t_data *data)
{
	ft_rotation_events(keycode, data);
	return (0);
}
