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
	if (keycode == 113)
		data->map->rotation.z = 0;
	if (keycode == 101)
		data->map->rotation.z = 0;
	if (keycode == 49)
		data->map->rotation.y = 0;
	if (keycode == 50)
		data->map->rotation.y = 0;
	if (keycode == 51)
		data->map->rotation.x = 0;
	if (keycode == 52)
		data->map->rotation.x = 0;
	printf("\n%f\n", data->map->rotation.y);
}

int	key_down(int keycode, t_data *data)
{
	static int	type;

	if (!type)
		type = 0;
	ft_rotation_events(keycode, data);
	return (0);
}
