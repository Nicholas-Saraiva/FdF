/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:23:12 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/08/06 11:23:14 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int			get_rgb(int color, int scaler);
static unsigned int	create_rgb(int r, int g, int b);

unsigned int	interpolate_color(int color1, int color2,
	int step, float steps)
{
	t_color	c1;
	t_color	c2;
	float	t;

	t = (float) step / (float) steps;
	c1.r = get_rgb(color1, 16);
	c1.g = get_rgb(color1, 8);
	c1.b = get_rgb(color1, 0);
	c2.r = get_rgb(color2, 16);
	c2.g = get_rgb(color2, 8);
	c2.b = get_rgb(color2, 0);
	return (create_rgb(c1.r + (c2.r - c1.r) * t,
			c1.g + (c2.g - c1.g) * t, c1.b + (c2.b - c1.b) * t));
}

static int	get_rgb(int color, int scaler)
{
	return ((color >> scaler) & 0xFF);
}

static unsigned int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
