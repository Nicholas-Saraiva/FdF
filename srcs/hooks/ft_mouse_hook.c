/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:22:57 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/11 22:05:31 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	if (data->map->zoom < 2 && (keycode == 4 || x == 1 || y == 2))
		data->map->zoom *= 1.1;
	if (data->map->zoom > 0.4 && (keycode == 5 || x == 1 || y == 2))
		data->map->zoom *= 0.9;
	return (0);
}
