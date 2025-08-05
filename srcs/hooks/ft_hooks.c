/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:49:46 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/05 18:23:46 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_hooks(t_data *data)
{
	mlx_hook(data->display, 2, 1L << 0, key_hook, data);
	mlx_hook(data->display, 17, 1L << 17, free_data, data);
	mlx_mouse_hook(data->display, mouse_hook, data);
}
